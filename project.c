#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "library.h"

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pause() {
    printf("Press Enter to continue...");
    getchar();
}

int read_int(const char *prompt) {
    int val;
    printf("%s", prompt);
    while (scanf("%d", &val) != 1) {
        printf("Invalid input. Try again: ");
        clear_input();
    }
    clear_input();
    return val;
}

void read_string(const char *prompt, char *buf, int size) {
    printf("%s", prompt);
    if (fgets(buf, size, stdin)) {
        size_t ln = strlen(buf) - 1;
        if (buf[ln] == '\n') buf[ln] = '\0';
    }
}

int main() {
    Book *books = NULL;
    int count = 0;
    load_books(&books, &count);

    int choice;
    do {
        system("clear||cls");
        printf("=== Library Management ===\n");
        printf("1. Add book\n");
        printf("2. Remove book\n");
        printf("3. List books\n");
        printf("4. Search books\n");
        printf("5. Issue book\n");
        printf("6. Return book\n");
        printf("7. Save and Exit\n");
        printf("Enter choice: ");
        choice = read_int("");

        if (choice == 1) {
            Book b = {0};
            b.id = next_book_id(books, count);
            read_string("Title: ", b.title, TITLE_LEN);
            read_string("Author: ", b.author, AUTHOR_LEN);
            b.year = read_int("Year: ");
            b.issued = false;
            b.issued_to[0] = '\0';
            if (add_book(&books, &count, b) > 0) printf("Book added with ID %d\n", b.id);
            else printf("Failed to add book.\n");
            pause();
        } else if (choice == 2) {
            int id = read_int("Book ID to remove: ");
            if (remove_book(&books, &count, id)) printf("Removed book %d\n", id);
            else printf("Book not found.\n");
            pause();
        } else if (choice == 3) {
            list_books(books, count);
            pause();
        } else if (choice == 4) {
            char q[120];
            read_string("Search (title or author): ", q, sizeof(q));
            int results[100];
            int n = search_books(books, count, q, results, 100);
            if (n == 0) printf("No matches found.\n");
            else {
                printf("Found %d result(s):\n", n);
                for (int i = 0; i < n; ++i) {
                    Book *b = find_book_by_id(books, count, results[i]);
                    if (b) printf("%d: %s by %s (%d) - %s\n", b->id, b->title, b->author, b->year, b->issued?"Issued":"Available");
                }
            }
            pause();
        } else if (choice == 5) {
            int id = read_int("Book ID to issue: ");
            Book *b = find_book_by_id(books, count, id);
            if (!b) { printf("Book not found.\n"); pause(); continue; }
            if (b->issued) { printf("Book already issued to %s\n", b->issued_to); pause(); continue; }
            char name[50];
            read_string("Borrower name: ", name, sizeof(name));
            if (issue_book(books, count, id, name)) printf("Book issued.\n"); else printf("Failed to issue.\n");
            pause();
        } else if (choice == 6) {
            int id = read_int("Book ID to return: ");
            if (return_book(books, count, id)) printf("Book returned.\n"); else printf("Failed to return (not found or not issued).\n");
            pause();
        } else if (choice == 7) {
            save_books(books, count);
            printf("Saved. Exiting...\n");
        } else {
            printf("Invalid choice.\n");
            pause();
        }
    } while (choice != 7);

    free(books);
    return 0;
}
