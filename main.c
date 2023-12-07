#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 50
#define MAX_ACCOUNTS 100

struct Account {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
};

void displayInvalidOptionAndClearScreen() {
    printf("\nInvalid input, please select a valid option.\n");
    sleep(2);
}

void login(struct Account *accounts, int *numAccounts, int *loggedInUser);
void addAccount(struct Account *accounts, int *numAccounts);

int main() {
    struct Account *accounts = malloc(MAX_ACCOUNTS * sizeof(struct Account));

    if (accounts == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    int numAccounts = 0;
    int loggedInUser = 0;

    do {
        login(accounts, &numAccounts, &loggedInUser);

        if (loggedInUser) {
            // Your alpha version logic goes here
            printf("Welcome, %s!\n", accounts[loggedInUser - 1].username);

            // This is just a placeholder. You need to implement the main menu logic.
            // For now, let's break the loop.
            loggedInUser = 0;
        }

    } while (loggedInUser);

    // Free allocated memory before exiting
    free(accounts);

    return 0;
}

void login(struct Account *accounts, int *numAccounts, int *loggedInUser) {
    char inputUsername[MAX_STRING_LENGTH];
    char inputPassword[MAX_STRING_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < *numAccounts; ++i) {
        if (strcmp(inputUsername, accounts[i].username) == 0 && strcmp(inputPassword, accounts[i].password) == 0) {
            *loggedInUser = i + 1;
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    *loggedInUser = 0;
}

void addAccount(struct Account *accounts, int *numAccounts) {
    if (*numAccounts >= MAX_ACCOUNTS) {
        printf("Error: Maximum number of accounts reached.\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", accounts[*numAccounts].username);

    // Check if the username already exists
    for (int i = 0; i < *numAccounts; ++i) {
        if (strcmp(accounts[i].username, accounts[*numAccounts].username) == 0) {
            printf("Error: Username already exists.\n");
            return;
        }
    }

    printf("Enter new password: ");
    scanf("%s", accounts[*numAccounts].password);

    (*numAccounts)++;
    printf("Account created successfully.\n");
}
