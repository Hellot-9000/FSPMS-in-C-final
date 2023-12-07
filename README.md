# Hotel Management System

## Overview
The Hotel Management System is a console-based application that simulates the management operations of a hotel. It includes features for front office, back of house, PBX, accounting, and owners receivable functions. The system manages user accounts, reservations, and provides various functionalities for hotel staff.

## Features
- User Authentication: Secure login system for authorized users.
- Front Office: Manage reservations, check-in, check-out, and mass checkout.
- Back of House: Create and delete user accounts (restricted access).
- PBX: Send mass messages, create reservations (mock implementation).
- Accounting: Manage revenue payout and kiosk reset operations.
- Owners Receivable: Perform revenue payout with confirmation.

## File Structure
- `main.c`: Main program file containing the logic for user interface and menu navigation.
- `reservations.txt`: File storing reservation data.
- `accounts.txt`: File storing user account data.

## Getting Started
1. Compile the program using a C compiler (e.g., `gcc main.c -o hotel_management_system`).
2. Follow the on-screen prompts to navigate through different menus and functionalities.

## Important Notes
- This program is a console-based prototype and serves as a demonstration of basic hotel management features.
- The system reads and writes reservation and account data to text files (`reservations.txt` and `accounts.txt`).

