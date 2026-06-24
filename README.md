# Simple Bank System (OOP)

A comprehensive, console-based Bank Management System built using C++ and advanced Object-Oriented Programming (OOP) principles. This project marks an architectural evolution from a procedural implementation to a clean, scalable, and modular object-oriented design.

---

## Key Features

* Client Management: Complete CRUD operations (Add, Find, Update, Delete) with validation.
* User & Permissions System: Secure login mechanism with a Bitwise-permission architecture managing access to different screens.
* Transaction Manager: Supports Deposits, Withdrawals, and secure Client-to-Client Transfers.
* Logging Systems: Automatically tracks and logs security events (Login Register) and financial operations (Transfer Logs) into dedicated flat-file databases.
* Currency Exchange: A built-in module for currency listing, tracking conversion rates, and a currency calculator.

---

## OOP Principles Applied

* Encapsulation & Data Hiding: Domain logic and file handling are strictly encapsulated within dedicated classes, exposing only clean public interfaces.
* Inheritance: Core entities (clsBankClient and clsUser) inherit foundational attributes from a base clsPerson class to eliminate redundancy.
* Layered Design: Clean separation between the Core Business Logic Layer and the Presentation Layer (Console UI Screens).
* Advanced Permissions: Utilizes Bitwise operators to calculate and enforce granular system access dynamically per user.

---

## First-Time Setup & Execution

The database files have been freshly initialized and cleaned for testing. 

* First Run Feature: On your very first launch, the system will automatically detect that the database is empty and prompt you via a dedicated setup screen to create the primary Admin Account with full system permissions.
* Once created, you can use those credentials to log in and explore all the features of the bank system.
