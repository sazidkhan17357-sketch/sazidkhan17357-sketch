# Contact Management System (C)

A menu-driven C application that stores contact records in a local text file.

## Features
- Add contacts with a name, phone number, and email
- List all saved contacts
- Search using an exact, case-sensitive name
- Delete a contact using an exact name
- Load saved records when the program starts
- Save changes to `contacts.txt`
- Validate empty fields and overly long input
- Store up to 100 contacts

## Concepts demonstrated
- Structures and arrays
- Strings and input validation
- Functions and modular program design
- File handling with `fopen`, `fgets`, `fprintf`, and `fclose`
- Searching and deleting array elements

## Build and run
Requires GCC or another C11-compatible compiler.

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic contact_manager.c -o contact_manager
./contact_manager
```

The program creates `contacts.txt` in the current working directory. Each record uses the format `name|phone|email`; the pipe character is therefore not allowed inside a field.

## Limitations
This is an educational project, not a secure contact database. Data is stored as plain text without encryption. Search and delete use exact, case-sensitive name matching. Avoid storing sensitive personal information.

## Suggested manual checks
1. Add a contact and list contacts.
2. Exit and restart; confirm the contact is still present.
3. Search for the exact name, then try a different spelling.
4. Delete the contact and list contacts again.
5. Try empty and overly long input.
