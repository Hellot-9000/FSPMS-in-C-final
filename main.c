#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 50
#define MAX_ACCOUNTS 100
#define MAX_RESERVATIONS 100

struct Account {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
};

struct Reservation {
    int reservationNumber;
    char guestName[MAX_STRING_LENGTH];
    char checkInDate[MAX_STRING_LENGTH];
    char checkOutDate[MAX_STRING_LENGTH];
    int roomNumber;
    char status[MAX_STRING_LENGTH];
};

void displayInvalidOptionAndClearScreen() {
    printf("\nInvalid input, please select a valid option.\n");
    sleep(2);
}

void login(struct Account *accounts, int *numAccounts, int *loggedInUser);
void addAccount(struct Account *accounts, int *numAccounts);
int findAccountByUsername(const struct Account *accounts, int numAccounts, const char *username);

int main() {
    struct Account *accounts = malloc(MAX_ACCOUNTS * sizeof(struct Account));
    struct Reservation *reservations = malloc(MAX_RESERVATIONS * sizeof(struct Reservation));

    if (accounts == NULL || reservations == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    int numAccounts = 0;
    int numReservations = 0;

    int loggedInUser = 0;

    do {
        login(accounts, &numAccounts, &loggedInUser);

        if (loggedInUser) {
            // Your main menu logic goes here
            // Example: displayMainMenu(reservations, &numReservations, accounts, &numAccounts);
            printf("Successfully logged in!\n");

            // This is just a placeholder. You need to implement the main menu logic.
            // For now, let's break the loop.
            loggedInUser = 0;
        }

    } while (loggedInUser);

    // Free allocated memory before exiting
    free(accounts);
    free(reservations);

    return 0;
}

void login(struct Account *accounts, int *numAccounts, int *loggedInUser) {
    char inputUsername[MAX_STRING_LENGTH];
    char inputPassword[MAX_STRING_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    scanf("%s", inputPassword);

    int accountIndex = findAccountByUsername(accounts, *numAccounts, inputUsername);

    if (accountIndex != -1 && strcmp(inputPassword, accounts[accountIndex].password) == 0) {
        *loggedInUser = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        *loggedInUser = 0;
    }
}

void addAccount(struct Account *accounts, int *numAccounts) {
    if (*numAccounts >= MAX_ACCOUNTS) {
        printf("Error: Maximum number of accounts reached.\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", accounts[*numAccounts].username);

    // Check if the username already exists
    int existingIndex = findAccountByUsername(accounts, *numAccounts, accounts[*numAccounts].username);
    if (existingIndex != -1) {
        printf("Error: Username already exists.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", accounts[*numAccounts].password);

    (*numAccounts)++;
    printf("Account created successfully.\n");
}

int findAccountByUsername(const struct Account *accounts, int numAccounts, const char *username) {
    for (int i = 0; i < numAccounts; ++i) {
        if (strcmp(username, accounts[i].username) == 0) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}
