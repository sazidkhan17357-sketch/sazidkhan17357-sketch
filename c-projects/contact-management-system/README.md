# Contact Management System

A menu-based C program for keeping a small list of contacts. You can add a contact, view the saved list, search by name, or delete a contact.

The program saves its records in a local file called contacts.txt, so the contacts are still there when you run it again.

## Features

- Add a contact with a name, phone number and email
- View all saved contacts
- Search for an exact name
- Delete a contact by exact name
- Load saved contacts when the program starts
- Check for empty or overly long input
- Store up to 100 contacts

## Build and run

You need GCC or another C11-compatible compiler.

~~~bash
gcc -std=c11 -Wall -Wextra -Wpedantic contact_manager.c -o contact_manager
./contact_manager
~~~

The program creates contacts.txt in the directory where you run it. The fields are separated by the | character, so that character cannot be part of a name, phone number or email.

## What I practised

- Structures and arrays
- Working with strings
- Splitting a program into functions
- Reading and writing files
- Searching for and removing records

## A note about the data

This is a learning project, not a secure address book. The file stores contact details as plain text without encryption. Please use sample data rather than real sensitive information.

## Things to try

1. Add a contact and view the list.
2. Close the program, run it again and check that the contact is still saved.
3. Search for the contact by its exact name.
4. Delete it and check the list again.
5. Try entering an empty field or a very long value.
