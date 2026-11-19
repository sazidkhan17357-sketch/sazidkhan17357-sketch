# C Programming Projects

This folder contains small C programs I've worked on while practising the basics and getting more comfortable writing programs from scratch.

## Projects

| Project | What it does | Main concepts |
|---|---|---|
| [Calculator](calculator/) | Performs basic arithmetic operations. | Functions, switch statements, input validation |
| [Number Guessing Game](number-guessing-game/) | Lets the player guess a random number from 1 to 100. | Loops, conditions, random numbers |
| [Student Grade Manager](student-grade-manager/) | Takes a student's marks and calculates the total and average. | Structures, arrays, functions |
| [Contact Management System](contact-management-system/) | Adds, lists, searches and deletes contacts saved in a text file. | Structures, strings, file handling |

## Compile a program

Open the folder for the program you want to run, then compile its C file with GCC. For example:

~~~bash
gcc -std=c11 -Wall -Wextra calculator.c -o calculator
./calculator
~~~

Each project has its own README with build instructions and a short description.
