#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

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

typedef struct {
    int reservationNumber;
    char guestName[MAX_STRING_LENGTH];
    char checkInDate[MAX_STRING_LENGTH];
    char checkOutDate[MAX_STRING_LENGTH];
    int roomNumber;
    char status[MAX_STRING_LENGTH];
} Reservation;
void displayReservationsFromFile();
void readReservationFromFile(FILE *file, Reservation *reservation);
void printReservation(const Reservation *reservation);
void displayInvalidOptionAndClearScreen();
void login(struct Account *accounts, int *numAccounts, int *loggedInUser);
void addAccount(struct Account *accounts, int *numAccounts);
void deleteAccount(struct Account *accounts, int *numAccounts);
void loadReservationsFromFile(struct Reservation *reservations, int *numReservations);
void loadAccountsFromFile(struct Account *accounts, int *numAccounts);
void displayMainMenu(struct Reservation *reservations, int *numReservations, struct Account *accounts, int *numAccounts);
void frontOfficeMenu(struct Reservation *reservations, int *numReservations);
void addReservation(struct Reservation *reservations, int *numReservations);
void pbxMenu();
void accountingMenu();
void ownersReceivableMenu();
void MassCheckout();
void backOfHouseMenu(struct Account accounts[], int *numAccounts);
void logoff(int *loggedInUser);
void logoff(int *loggedInUser) {
    *loggedInUser = 0;
    printf("Logged off successfully.\n");
}
void MassCheckout() {
    printf("Check out all guests going out today? (1,2)");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Checking out all guests going out today...\n");
        sleep(3);
        printf("All guests have been checked out.\n");
    } else if (choice == 2) {
        printf("Cancelling mass checkout...\n");
        sleep(3);
        printf("Mass checkout cancelled.\n");
    } else {
        printf("Invalid option. Please enter 1 or 2.\n");
    }
}

void frontOfficeMenu(struct Reservation reservations[], int *numReservations) {
    int subMenuChoice;

    while (1) {
        printf("\nFront Office Menu\n");
        printf("1. View Reservations\n");
        printf("2. Add Reservation\n");
        printf("3. Mass Checkout\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &subMenuChoice);

        switch (subMenuChoice) {
            case 1:
                displayReservationsFromFile();
                break;
            case 2:
                addReservation(reservations, numReservations);
                break;
            case 3:
                MassCheckout();
                break;
            case 0:
                return;
            default:
                displayInvalidOptionAndClearScreen();
        }
    }
}

void displayReservationsFromFile() {
    FILE *file = fopen("reservations.txt", "r");
    if (!file) {
        perror("Error opening reservations.txt for reading");
        return;
    }


    printf("\nDisplaying all reservations, please wait...\n");

    Reservation reservation;
    while (fscanf(file, "%d %s %s %s %d %s",
                  &reservation.reservationNumber,
                  reservation.guestName,
                  reservation.checkInDate,
                  reservation.checkOutDate,
                  &reservation.roomNumber,
                  reservation.status) == 6) {
        printReservation(&reservation);
    }

    fclose(file);
}

void readReservationFromFile(FILE *file, Reservation *reservation) {
    fscanf(file, "%d %s %s %s %d %s",
           &reservation->reservationNumber,
           reservation->guestName,
           reservation->checkInDate,
           reservation->checkOutDate,
           &reservation->roomNumber,
           reservation->status);
}

void printReservation(const Reservation *reservation) {
    printf("%d %s %s %s %d %s\n",
           reservation->reservationNumber,
           reservation->guestName,
           reservation->checkInDate,
           reservation->checkOutDate,
           reservation->roomNumber,
           reservation->status);
}
void loadReservationsFromFile(struct Reservation *reservations, int *numReservations) {
    FILE *file = fopen("Reservations.txt", "r");
    if (file == NULL) {
        perror("Error opening Reservations.txt for reading");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %s",
                  &reservations[*numReservations].reservationNumber,
                  reservations[*numReservations].guestName,
                  reservations[*numReservations].checkInDate,
                  reservations[*numReservations].checkOutDate,
                  &reservations[*numReservations].roomNumber,
                  reservations[*numReservations].status) == 6) {
        (*numReservations)++;
    }

    fclose(file);
}

void backOfHouseMenu(struct Account accounts[], int *numAccounts) {
    if (strcmp(accounts[0].username, "DJMOR333") == 0) {
        int subMenuChoice;

        for (;;) {
            printf("\nBack of House Menu\n");
            printf("1. Create Accounts\n");
            printf("2. Delete Accounts\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &subMenuChoice);

            switch (subMenuChoice) {
                case 1:
                    addAccount(accounts, numAccounts);
                    break;
                case 2:
                    deleteAccount(accounts, numAccounts);
                    break;
                case 0:
                    return;
                default:
                    printf("Invalid option. Please try again.\n");
            }
        }
    } else {
        printf("\nUnauthorized. Please make another selection.\n");
    }
}

void deleteAccount(struct Account accounts[], int *numAccounts) {
    char targetUsername[20];
    int found = 0;

    printf("Enter the number corresponding to the username to delete: \n");
    printf("List of accounts:\n");

    for (int i = 0; i < *numAccounts; ++i) {
        printf("%d. %s\n", i + 1, accounts[i].username);
    }

    int userChoice;
    scanf("%d", &userChoice);

    if (userChoice < 1 || userChoice > *numAccounts) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Deleting account: %s\n", accounts[userChoice - 1].username);

    if (strcmp(accounts[userChoice - 1].username, "DJMOR333") == 0) {
        printf("Error: Cannot delete the DJMOR333 account.\n");
        return;
    }

    for (int i = userChoice - 1; i < *numAccounts - 1; ++i) {
        strcpy(accounts[i].username, accounts[i + 1].username);
        strcpy(accounts[i].password, accounts[i + 1].password);
    }

    (*numAccounts)--;
    found = 1;
    printf("Account deleted successfully.\n");

    if (!found) {
        printf("Account not found.\n");
    }
}

void addAccount(struct Account accounts[], int *numAccounts) {
    if (*numAccounts >= MAX_ACCOUNTS) {
        printf("Error: Maximum number of accounts reached.\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", accounts[*numAccounts].username);

    if (strcmp(accounts[*numAccounts].username, "DJMOR333") == 0) {
        printf("Error: Cannot add the DJMOR333 account.\n");
        return;
    }

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

void massCheckout(struct Reservation *reservations, int *numReservations) {
    int roomToCheckout;

    printf("Enter room number to mass checkout: ");
    scanf("%d", &roomToCheckout);

    for (int i = 0; i < *numReservations; ++i) {
        if (reservations[i].roomNumber == roomToCheckout) {
            strcpy(reservations[i].status, "Checked Out");
        }
    }

    printf("Mass checkout completed for room %d.\n", roomToCheckout);
}
void displayInvalidOptionAndClearScreen() {
    printf("\nInvalid input, please select a valid option.\n");
    sleep(2);
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
            *loggedInUser = 1;
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    *loggedInUser = 0;
}

void saveAccountsToFile(struct Account *accounts, int numAccounts) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < numAccounts; ++i) {
        fprintf(file, "%s %s\n", accounts[i].username, accounts[i].password);
    }

    fclose(file);
}

void loadAccountsFromFile(struct Account *accounts, int *numAccounts) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    while (fscanf(file, "%s %s", accounts[*numAccounts].username, accounts[*numAccounts].password) == 2) {
        (*numAccounts)++;
    }

    fclose(file);
}

void saveReservationsToFile(struct Reservation *reservations, int numReservations) {
    FILE *file = fopen("Reservations.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < numReservations; ++i) {
        fprintf(file, "%d %s %s %s %d %s\n",
                reservations[i].reservationNumber,
                reservations[i].guestName,
                reservations[i].checkInDate,
                reservations[i].checkOutDate,
                reservations[i].roomNumber,
                reservations[i].status);
    }

    fclose(file);
}

void displayMainMenu(struct Reservation *reservations, int *numReservations, struct Account *accounts, int *numAccounts) {
    int selectedMenu;

    printf("\nMain Menu\n");
    printf("1. Front Office\n");

    if (strcmp(accounts[0].username, "DJMOR333") == 0) {
        printf("2. Back of House\n");
        printf("3. PBX\n");
        printf("4. Accounting\n");
        printf("5. Owners Receivable\n");
    } else {
        printf("3. PBX (Unauthorized)\n");
        printf("2. Back of House (Unauthorized)\n");
        printf("4. Accounting (Unauthorized)\n");
        printf("5. Owners Receivable (Unauthorized)\n");
    }

    printf("0. Log Off\n");
    printf("Enter your choice: ");
    scanf("%d", &selectedMenu);

    switch (selectedMenu) {
        case 1:
            frontOfficeMenu(reservations, numReservations);
            break;
        case 2:
            backOfHouseMenu(accounts, numAccounts);
            break;
        case 3:
            pbxMenu();
            break;
        case 4:
            accountingMenu();
            break;
        case 5:
            ownersReceivableMenu();
            break;
        case 0:
            logoff(&selectedMenu);
            break;
        default:
            displayInvalidOptionAndClearScreen();
    }
}

void addReservation(struct Reservation *reservations, int *numReservations) {
    if (*numReservations >= MAX_RESERVATIONS) {
        printf("Error: Maximum number of reservations reached.\n");
        return;
    }

    printf("Enter guest name: ");
    scanf("%s", reservations[*numReservations].guestName);

    printf("Enter check-in date: ");
    scanf("%s", reservations[*numReservations].checkInDate);

    printf("Enter check-out date: ");
    scanf("%s", reservations[*numReservations].checkOutDate);

    printf("Enter room number: ");
    scanf("%d", &reservations[*numReservations].roomNumber);

    // TODO: You may want to validate input and generate a unique reservation number

    reservations[*numReservations].reservationNumber = (*numReservations) + 1; // Incremental reservation number
    strcpy(reservations[*numReservations].status, "Active");

    (*numReservations)++;
    printf("Reservation added successfully.\n");
}

void displayReservations(struct Reservation *reservations, int numReservations) {
    printf("\nList of Reservations:\n");
    for (int i = 0; i < numReservations; ++i) {
        printf("Reservation Number: %d\n", reservations[i].reservationNumber);
        printf("Guest Name: %s\n", reservations[i].guestName);
        printf("Check-In Date: %s\n", reservations[i].checkInDate);
        printf("Check-Out Date: %s\n", reservations[i].checkOutDate);
        printf("Room Number: %d\n", reservations[i].roomNumber);
        printf("Status: %s\n", reservations[i].status);
        printf("\n");
    }
}

void reportMenu() {
    // TODO: Implement
    printf("Report menu (mock implementation)\n");
}

void pbxMenu() {
    int subMenuChoice;

    for (;;) {
        printf("\nPBX Menu\n");
        printf("1. Mass Message\n");
        printf("2. Create Reservations\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &subMenuChoice);

        switch (subMenuChoice) {
            case 1:
                printf("Mass Message menu (mock implementation)\n");
                break;
            case 2:
                printf("Create Reservations menu (mock implementation)\n");
                break;
            case 0:
                return;
            default:
                displayInvalidOptionAndClearScreen();
        }
    }
}
void accountingMenu(double *revenue) {
    int subMenuChoice;

    for (;;) {
        printf("\nAccounting Menu\n");
        printf("1. Pay Out\n");
        printf("2. Reset Kiosk\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &subMenuChoice);

        switch (subMenuChoice) {
            case 1:
                printf("Enter revenue amount: ");
                scanf("%lf", revenue);
                printf("Revenue of $%.2lf inserted into Owners Receivable.\n", *revenue);
                break;
            case 2:
                printf("Make sure all users are offline/logged off. Continue? (Yes/No): ");
                char resetConfirmation[5];
                scanf("%s", resetConfirmation);
                if (strcmp(resetConfirmation, "Yes") == 0) {
                    printf("Please wait...\n");
                    sleep(10);
                    printf("Completed!\n");
                } else {
                    printf("Reset canceled.\n");
                }
                break;
            case 0:
                return;
            default:
                displayInvalidOptionAndClearScreen();
        }
    }
}


void ownersReceivableMenu(double *revenue) {
    int subMenuChoice;

    while (1) {
        printf("\nOwners Receivable Menu\n");
        printf("1. Pay Out\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &subMenuChoice);

        switch (subMenuChoice) {
            case 1: {
                char confirmation[5];
                do {
                    printf("Are you sure you want to pay out? (Yes/No): ");
                    scanf("%s", confirmation);
                    if (strcmp(confirmation, "Yes") == 0) {
                        printf("Payout of $%.2lf completed.\n", *revenue);
                        *revenue = 0.0; // Reset revenue after payout
                        break;
                    } else if (strcmp(confirmation, "No") == 0) {
                        printf("Payment canceled.\n");
                        break;
                    } else {
                        printf("Invalid option. Please enter 'Yes' or 'No'.\n");
                    }
                } while (1);
                break;
            }
            case 0:
                return;
            default:
                displayInvalidOptionAndClearScreen();
        }
    }
}

int main() {
    struct Account *accounts = malloc(MAX_ACCOUNTS * sizeof(struct Account));
    struct Reservation *reservations = malloc(MAX_RESERVATIONS * sizeof(struct Reservation));

    if (accounts == NULL || reservations == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    int numAccounts = 0;
    int numReservations = 0;

    loadAccountsFromFile(accounts, &numAccounts);
    loadReservationsFromFile(reservations, &numReservations);

    int loggedInUser = 0;

    do {
        login(accounts, &numAccounts, &loggedInUser);

        if (loggedInUser) {
            displayMainMenu(reservations, &numReservations, accounts, &numAccounts);
        }

    } while (loggedInUser);

    // Free allocated memory before exiting
    free(accounts);
    free(reservations);

    return 0;
}







