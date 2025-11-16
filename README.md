# Address-Book-Management-System
Built a C-based Address Book Management System with features like create, search, edit, delete, and list contacts. Implemented file handling, structures, strings, validation, and a clean console UI. Includes duplicate handling .

I.PROJECT OVERVIEW:

This project is a menu-driven Address Book System developed using C, demonstrating strong understanding of:
- File Handling
- Pointers & Dynamic Access
- Structures & Arrays
- String Manipulation
- Search, Edit & Delete Operations
It allows users to store, view, search, edit, and delete contact information efficiently.

II.KEY FEATURES:
- Add new contacts
- Search contacts (by Name, Mobile, Email)
- Edit a specific contact
- Delete a specific contact
- List all saved contacts
- Prevent duplicate phone numbers & emails
- Data persistence using files

III.TECH STACK:
🧰 Programming Language: C
📁 File Handling: CSV (contacts.csv)
⚙ Concepts Used:
- Structures and Structure pointers
- File I/O
- Pointers
- Arrays
- String Functions
- Switch case, loops, conditions

III.CREATE CONTACT:
Stores Name, Mobile Number, and Email ID
Validates:
- Name (string input)
- Mobile (digits only, 10-digit check, detects duplicates)
- Email (must contain @ and .com, lowercase validation)

IV.SEARCH CONTACT:
Supports three search modes:
🔍 Search by Name
🔍 Search by Mobile Number
🔍 Search by Email ID

V.EDIT CONTACT:
If multiple contacts have the same name, user can select the exact index.
Editable fields:
- Name
- Mobile Number
- Email

VI.DELETE CONTACT:
- Search → Select → Delete
- Supports multiple contacts with the same name.

VII.LIST ALL CONTACTS:
Displays all contacts in a beautiful tabular format.

VIII.FILE HANDLING(CSV):
- Saves contacts to contacts.csv
- Loads contacts on program startup
- Ensures persistence even after exiting

IX. LEARNING OUTCOMES:
By completing this project, I strengthened my understanding of:
- File-based database systems
- Record searching algorithms
- Error handling and input validation
- Clean code structure with modularity
- Memory & string management in C

X. ACKNOWLEDGMENT:
Project implemented as part of my learning journey in Advanced C Programming.
