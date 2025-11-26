# Library Management System (C)

This project is a simple **Library Management System** written in C. It allows you to manage books, issue and return books, and store all records in a persistent binary file.

This README matches **exactly the code files provided**, including:
- `library.h`
- `library.c`
- `main.c`
- `Makefile`

---

## 📌 Features
- Add new books
- Remove existing books
- Search books by ID, title, or author
- List all books
- Issue a book to a user
- Return an issued book
- Auto‑increment book IDs
- Data stored in `data/library.dat`

---

## 📂 Project Structure
```
library-management-c/
├── README.md
├── Makefile
├── .gitignore
├── src/
│   ├── main.c
│   ├── library.c
│   └── library.h
└── data/
    └── library.dat (created automatically)
```

---

## ⚙️ Build Instructions
Make sure you have **gcc** installed.

### Build the program
```bash
make
```
This produces the binary:
```
bin/library
```

### Run the program
```bash
./bin/library
```

### Clean build files
```bash
make clean
```

---

## 🧾 File Descriptions
### **library.h**
Contains:
- `Book` structure definition
- Function prototypes for adding, removing, searching, issuing, returning, saving, and loading books

### **library.c**
Implements all library operations such as:
- `add_book()`
- `remove_book()`
- `issue_book()`
- `return_book()`
- `load_books()` / `save_books()`
- Sorting and searching helpers

### **main.c**
Implements the user interface (menu system) and uses the library functions to perform operations.

### **Makefile**
Build automation for GCC.

---

## 💾 Data Storage
The program stores all book records in:
```
data/library.dat
```
This file is created automatically if missing.

---

## 🔖 License
MIT License


<img width="408" height="353" alt="image" src="https://github.com/user-attachments/assets/1724c976-f31a-4f12-98dd-7de7c70c0a06" />
<img width="401" height="289" alt="image" src="https://github.com/user-attachments/assets/0fd002c7-bb64-45a9-8f81-32d5852d26d1" />
<img width="426" height="285" alt="image" src="https://github.com/user-attachments/assets/448e8c66-4cc0-44f9-9716-da39381aeaf1" />
<img width="419" height="350" alt="image" src="https://github.com/user-attachments/assets/8aada797-03d8-46c4-9a82-a3bb2c786b14" />
<img width="423" height="299" alt="image" src="https://github.com/user-attachments/assets/6d8c0435-3a82-4757-83d4-9e5a7ac9f827" />





