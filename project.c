#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LEN 100
#define AUTHOR_LEN 100

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int copies;
} Book;

typedef struct {
    Book *books;
    size_t size;
    size_t cap;
} Library;

// Initialize library
void init_library(Library *lib) {
    lib->cap = 10;
    lib->size = 0;
    lib->books = malloc(sizeof(Book) * lib->cap);
}

// Save memory
void free_library(Library *lib) {
    free(lib->books);
}

// Ensure capacity grows
void ensure_capacity(Library *lib) {
    if (lib->size >= lib->cap) {
        lib->cap *= 2;
        lib->books = realloc(lib->books, sizeof(Book) * lib->cap);
    }
}

// Generate next ID
int generate_next_id(Library *lib) {
    int max = 0;
    for (size_t i = 0; i < lib->size; i++)
        if (lib->books[i].id > max)
            max = lib->books[i].id;
    return max + 1;
}

// Add book
void add_book(Library *lib) {
    ensure_capacity(lib);
    Book b;

    b.id = generate_next_id(lib);

    printf("Enter title: ");
    fgets(b.title, TITLE_LEN, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter author: ");
    fgets(b.author, AUTHOR_LEN, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter number of copies: ");
    scanf("%d", &b.copies);
    getchar(); // consume newline

    lib->books[lib->size++] = b;

    printf("Book added with ID %d\n", b.id);
}

// List books
void list_books(Library *lib) {
    if (lib->size == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\nID   | Title                         | Author               | Copies\n");
    printf("-----------------------------------------------------------------------\n");

    for (size_t i = 0; i < lib->size; i++) {
        printf("%-4d | %-30s | %-20s | %d\n",
               lib->books[i].id,
               lib->books[i].title,
               lib->books[i].author,
               lib->books[i].copies);
    }
}

// Search book by ID
Book* find_book(Library *lib, int id) {
    for (size_t i = 0; i < lib->size; i++)
        if (lib->books[i].id == id)
            return &lib->books[i];
    return NULL;
}

// Remove book
void remove_book(Library *lib) {
    int id;
    printf("Enter ID to remove: ");
    scanf("%d", &id);
    getchar();

    int index = -1;
    for (size_t i = 0; i < lib->size; i++) {
        if (lib->books[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    for (size_t i = index; i < lib->size - 1; i++)
        lib->books[i] = lib->books[i + 1];

    lib->size--;
    printf("Book removed.\n");
}

// Borrow book
void borrow_book(Library *lib) {
    int id;
    printf("Enter ID to borrow: ");
    scanf("%d", &id);
    getchar();

    Book *b = find_book(lib, id);
    if (!b) {
        printf("Book not found.\n");
        return;
    }

    if (b->copies < 1) {
        printf("No copies available.\n");
        return;
    }

    b->copies--;
    printf("You borrowed '%s'.\n", b->title);
}

// Return book
void return_book(Library *lib) {
    int id;
    printf("Enter ID to return: ");
    scanf("%d", &id);
    getchar();

    Book *b = find_book(lib, id);
    if (!b) {
        printf("Book not found.\n");
        return;
    }

    b->copies++;
    printf("You returned '%s'.\n", b->title);
}

int main() {
    Library lib;
    init_library(&lib);

    int choice;

    while (1) {
        printf("\n=== Library Management System ===\n");
        printf("1. List books\n");
        printf("2. Add book\n");
        printf("3. Remove book\n");
        printf("4. Borrow book\n");
        printf("5. Return book\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);
        getchar(); // flush

        switch (choice) {
            case 1: list_books(&lib); break;
            case 2: add_book(&lib); break;
            case 3: remove_book(&lib); break;
            case 4: borrow_book(&lib); break;
            case 5: return_book(&lib); break;
            case 6:
                printf("Goodbye!\n");
                free_library(&lib);
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
