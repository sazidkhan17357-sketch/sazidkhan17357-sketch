#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int secret, guess, attempts = 0;

    srand((unsigned int)time(NULL));
    secret = rand() % 100 + 1;

    printf("Guess the number (1 to 100)\n");

    do {
        printf("Your guess: ");
        if (scanf("%d", &guess) != 1) {
            printf("Please enter a valid integer.\n");
            return 1;
        }

        attempts++;

        if (guess < secret) {
            printf("Too low. Try again.\n");
        } else if (guess > secret) {
            printf("Too high. Try again.\n");
        } else {
            printf("Correct! You got it in %d attempt(s).\n", attempts);
        }
    } while (guess != secret);

    return 0;
}