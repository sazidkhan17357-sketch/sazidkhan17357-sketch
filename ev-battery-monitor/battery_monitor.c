#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 256
#define MIN_PACK_VOLTAGE 250.0
#define MAX_PACK_VOLTAGE 420.0
#define MAX_CURRENT 200.0
#define MIN_TEMPERATURE 0.0
#define MAX_TEMPERATURE 60.0
#define LOW_SOC_LIMIT 15.0

typedef struct {
    double voltage;
    double current;
    double temperature;
    double state_of_charge;
} BatteryReading;

typedef enum {
    STATUS_NORMAL,
    STATUS_WARNING,
    STATUS_CRITICAL
} BatteryStatus;

static int parse_reading(const char *line, BatteryReading *reading) {
    char extra;
    int fields = sscanf(line, " %lf , %lf , %lf , %lf %c",
                        &reading->voltage, &reading->current,
                        &reading->temperature, &reading->state_of_charge,
                        &extra);

    if (fields != 4) {
        return 0;
    }

    return isfinite(reading->voltage) && isfinite(reading->current) &&
           isfinite(reading->temperature) && isfinite(reading->state_of_charge);
}

static int reading_is_in_range(const BatteryReading *reading) {
    return reading->voltage > 0.0 && reading->voltage <= 600.0 &&
           fabs(reading->current) <= 500.0 &&
           reading->temperature >= -40.0 && reading->temperature <= 120.0 &&
           reading->state_of_charge >= 0.0 && reading->state_of_charge <= 100.0;
}

static BatteryStatus evaluate_reading(const BatteryReading *reading) {
    int critical = reading->voltage < MIN_PACK_VOLTAGE ||
                   reading->voltage > MAX_PACK_VOLTAGE ||
                   fabs(reading->current) > MAX_CURRENT ||
                   reading->temperature < MIN_TEMPERATURE ||
                   reading->temperature > MAX_TEMPERATURE;

    if (critical) {
        return STATUS_CRITICAL;
    }

    if (reading->state_of_charge <= LOW_SOC_LIMIT) {
        return STATUS_WARNING;
    }

    return STATUS_NORMAL;
}

static const char *status_name(BatteryStatus status) {
    switch (status) {
        case STATUS_NORMAL: return "NORMAL";
        case STATUS_WARNING: return "WARNING";
        case STATUS_CRITICAL: return "CRITICAL";
    }
    return "UNKNOWN";
}

static void print_alerts(const BatteryReading *reading) {
    if (reading->voltage < MIN_PACK_VOLTAGE || reading->voltage > MAX_PACK_VOLTAGE) {
        printf("    Alert: pack voltage outside %.0f-%.0f V range.\n",
               MIN_PACK_VOLTAGE, MAX_PACK_VOLTAGE);
    }
    if (fabs(reading->current) > MAX_CURRENT) {
        printf("    Alert: current magnitude exceeds %.0f A.\n", MAX_CURRENT);
    }
    if (reading->temperature < MIN_TEMPERATURE ||
        reading->temperature > MAX_TEMPERATURE) {
        printf("    Alert: temperature outside %.0f-%.0f C range.\n",
               MIN_TEMPERATURE, MAX_TEMPERATURE);
    }
    if (reading->state_of_charge <= LOW_SOC_LIMIT) {
        printf("    Alert: low state of charge (%.1f%%).\n",
               reading->state_of_charge);
    }
}

int main(int argc, char *argv[]) {
    FILE *input;
    char line[LINE_SIZE];
    int line_number = 0;
    int valid_readings = 0;
    int invalid_readings = 0;
    int warnings = 0;
    int criticals = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <readings.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Could not open input file");
        return EXIT_FAILURE;
    }

    printf("EV Battery Monitoring Simulator\n");
    printf("--------------------------------\n");

    while (fgets(line, sizeof(line), input) != NULL) {
        BatteryReading reading;
        BatteryStatus status;

        line_number++;
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
            continue;
        }
        if (line_number == 1 && strstr(line, "voltage") != NULL) {
            continue;
        }

        if (!parse_reading(line, &reading) || !reading_is_in_range(&reading)) {
            printf("Line %d: Invalid reading - skipped.\n", line_number);
            invalid_readings++;
            continue;
        }

        status = evaluate_reading(&reading);
        valid_readings++;
        if (status == STATUS_WARNING) {
            warnings++;
        } else if (status == STATUS_CRITICAL) {
            criticals++;
        }

        printf("\nReading %d\n", valid_readings);
        printf("  Voltage: %.1f V | Current: %.1f A | Temperature: %.1f C | SOC: %.1f%%\n",
               reading.voltage, reading.current, reading.temperature,
               reading.state_of_charge);
        printf("  Status: %s\n", status_name(status));
        if (status != STATUS_NORMAL) {
            print_alerts(&reading);
        }
    }

    if (ferror(input)) {
        perror("Error while reading input file");
        fclose(input);
        return EXIT_FAILURE;
    }
    fclose(input);

    printf("\nSummary\n");
    printf("-------\n");
    printf("Valid readings:   %d\n", valid_readings);
    printf("Invalid readings: %d\n", invalid_readings);
    printf("Warnings:         %d\n", warnings);
    printf("Critical alerts:  %d\n", criticals);

    return valid_readings > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
