// Beta version includes reservation management
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void displayMainMenu(struct Reservation *reservations, int *numReservations);
void addReservation(struct Reservation *reservations, int *numReservations);

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
            displayMainMenu(reservations, &numReservations);
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

void displayMainMenu(struct Reservation *reservations, int *numReservations) {
    int selectedMenu;

    do {
        printf("\nMain Menu\n");
        printf("1. Add Reservation\n");
        printf("2. View Reservations\n");
        printf("0. Log Off\n");
        printf("Enter your choice: ");
        scanf("%d", &selectedMenu);

        switch (selectedMenu) {
            case 1:
                addReservation(reservations, numReservations);
                break;
            case 2:
                // Your logic to view reservations goes here
                break;
            case 0:
                printf("Logging off...\n");
                break;
            default:
                displayInvalidOptionAndClearScreen();
        }

    } while (selectedMenu != 0);
}

void addReservation(struct Reservation *reservations, int *numReservations) {
    if (*numReservations >= MAX_RESERVATIONS) {
        printf("Error: Maximum number of reservations reached.\n");
        return;
    }

    // Your logic to add a reservation goes here

    printf("Reservation added successfully.\n");
}
