#include <stdio.h>

#define SUBJECTS 3

struct Student {
    char name[50];
    float marks[SUBJECTS];
};

int main(void) {
    struct Student student;
    float total = 0.0f;
    int i;

    printf("Enter student name (one word): ");
    if (scanf("%49s", student.name) != 1) {
        printf("Invalid name.\n");
        return 1;
    }

    for (i = 0; i < SUBJECTS; i++) {
        printf("Enter marks for subject %d (0-100): ", i + 1);
        if (scanf("%f", &student.marks[i]) != 1 ||
            student.marks[i] < 0.0f || student.marks[i] > 100.0f) {
            printf("Invalid marks. Enter a value from 0 to 100.\n");
            return 1;
        }
        total += student.marks[i];
    }

    printf("\nStudent: %s\n", student.name);
    printf("Total: %.2f / %d\n", total, SUBJECTS * 100);
    printf("Average: %.2f\n", total / SUBJECTS);

    return 0;
}