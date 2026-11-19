# EV Battery Monitoring & Fault Detection Simulator

A command-line C project that reads sample electric-vehicle battery telemetry from a CSV file and classifies each reading as **NORMAL**, **WARNING**, or **CRITICAL**.

> **Educational simulation only:** this program processes sample data. It does not connect to a battery, read physical sensors, estimate real battery safety, or replace a certified Battery Management System (BMS).

## Features

- Reads voltage, current, temperature, and state-of-charge (SOC) values from CSV.
- Validates the input format and basic measurement ranges.
- Flags voltage, current, and temperature values outside configurable example limits.
- Warns when SOC is at or below 15%.
- Prints a per-reading status, alerts, and a summary.
- Handles missing files and malformed/out-of-range rows.

## Requirements

- GCC or another C11-compatible compiler
- Linux, macOS, or Windows with a compatible C toolchain

## Build and run

From the repository root:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror ev-battery-monitor/battery_monitor.c -lm -o battery_monitor
./battery_monitor ev-battery-monitor/sample_readings.csv
```

Or run these commands from this folder:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror battery_monitor.c -lm -o battery_monitor
./battery_monitor sample_readings.csv
```

## CSV format

The first row may be a header. Each data row must contain:

```csv
voltage,current,temperature,soc
360,45,28,78
```

Values are in volts (V), amperes (A), degrees Celsius (C), and percent (%). Current may be negative to represent regenerative charging.

## Example rules

| Measurement | Example alert condition |
|---|---|
| Pack voltage | Below 250 V or above 420 V |
| Current magnitude | Above 200 A |
| Temperature | Below 0 C or above 60 C |
| State of charge | 15% or lower (warning) |

These are illustrative thresholds for this sample program, not universal EV battery specifications. Real limits depend on battery chemistry, pack design, sensor calibration, manufacturer requirements, and operating conditions.

## Concepts demonstrated

C structures, functions, file I/O, CSV parsing, input validation, conditional logic, floating-point calculations, and basic fault classification.
