#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 24
#define EMAIL_SIZE 60
#define FILE_NAME "contacts.txt"

typedef struct {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
} Contact;

static Contact contacts[MAX_CONTACTS];
static int count = 0;

static void remove_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

static int read_text(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) return 0;
    if (strchr(buffer, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return 0;
    }
    remove_newline(buffer);
    return 1;
}

static void load_contacts(void) {
    FILE *file = fopen(FILE_NAME, "r");
    char line[NAME_SIZE + PHONE_SIZE + EMAIL_SIZE + 4];
    if (file == NULL) return;
    while (count < MAX_CONTACTS && fgets(line, sizeof(line), file) != NULL) {
        char *name, *phone, *email;
        remove_newline(line);
        name = strtok(line, "|");
        phone = strtok(NULL, "|");
        email = strtok(NULL, "|");
        if (name == NULL || phone == NULL || email == NULL) continue;
        snprintf(contacts[count].name, NAME_SIZE, "%s", name);
        snprintf(contacts[count].phone, PHONE_SIZE, "%s", phone);
        snprintf(contacts[count].email, EMAIL_SIZE, "%s", email);
        count++;
    }
    fclose(file);
}

static int save_contacts(void) {
    FILE *file = fopen(FILE_NAME, "w");
    int i;
    if (file == NULL) { perror("Unable to save contacts"); return 0; }
    for (i = 0; i < count; i++)
        fprintf(file, "%s|%s|%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    if (fclose(file) != 0) { perror("Unable to finish saving"); return 0; }
    return 1;
}

static int valid_field(const char *s) {
    return s[0] != '\0' && strchr(s, '|') == NULL;
}

static void add_contact(void) {
    Contact item;
    if (count == MAX_CONTACTS) { puts("Contact list is full."); return; }
    if (!read_text("Name: ", item.name, sizeof(item.name)) ||
        !read_text("Phone: ", item.phone, sizeof(item.phone)) ||
        !read_text("Email: ", item.email, sizeof(item.email))) {
        puts("Input too long or unavailable. Contact not added."); return;
    }
    if (!valid_field(item.name) || !valid_field(item.phone) || !valid_field(item.email)) {
        puts("Fields must be non-empty and cannot contain '|'."); return;
    }
    contacts[count++] = item;
    if (save_contacts()) puts("Contact saved.");
}

static void list_contacts(void) {
    int i;
    if (count == 0) { puts("No contacts found."); return; }
    puts("\nSaved contacts:");
    for (i = 0; i < count; i++)
        printf("%d. %s | %s | %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
}

static void search_contact(void) {
    char query[NAME_SIZE];
    int i, found = 0;
    if (!read_text("Exact name to search: ", query, sizeof(query))) { puts("Invalid input."); return; }
    for (i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, query) == 0) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
            found = 1;
        }
    }
    if (!found) puts("Contact not found.");
}

static void delete_contact(void) {
    char query[NAME_SIZE];
    int i, index = -1;
    if (!read_text("Exact name to delete: ", query, sizeof(query))) { puts("Invalid input."); return; }
    for (i = 0; i < count; i++)
        if (strcmp(contacts[i].name, query) == 0) { index = i; break; }
    if (index < 0) { puts("Contact not found."); return; }
    for (i = index; i < count - 1; i++) contacts[i] = contacts[i + 1];
    count--;
    if (save_contacts()) puts("Contact deleted.");
}

int main(void) {
    char input[16];
    int choice;
    load_contacts();
    printf("Contact Management System - %d contact(s) loaded\n", count);
    do {
        puts("\n1. Add  2. List  3. Search  4. Delete  0. Exit");
        if (!read_text("Choose: ", input, sizeof(input))) { puts("Invalid choice."); continue; }
        char *end;
        long value = strtol(input, &end, 10);
        if (input[0] == '\0' || *end != '\0' || value < 0 || value > 4) { puts("Enter 0 to 4."); continue; }
        choice = (int)value;
        switch (choice) {
            case 1: add_contact(); break;
            case 2: list_contacts(); break;
            case 3: search_contact(); break;
            case 4: delete_contact(); break;
            case 0: puts("Goodbye."); break;
        }
    } while (choice != 0);
    return 0;
}
