#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int accNo;
    char name[50];
    float balance;
} Account;

void createAccount();
void viewAccounts();
void searchAccount();
void deposit();
void withdraw();

int main() {
    int choice;

    do {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. View All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: viewAccounts(); break;
            case 3: searchAccount(); break;
            case 4: deposit(); break;
            case 5: withdraw(); break;
            case 6: printf("Thank you. Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while(choice != 6);

    return 0;
}

void createAccount() {
    FILE *fp = fopen("bank.dat", "ab");
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

void viewAccounts() {
    FILE *fp = fopen("bank.dat", "rb");
    Account acc;

    if (!fp) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- All Accounts ---\n");
    while (fread(&acc, sizeof(Account), 1, fp)) {
        printf("Acc No: %d\n", acc.accNo);
        printf("Name: %s\n", acc.name);
        printf("Balance: ₹%.2f\n\n", acc.balance);
    }

    fclose(fp);
}

void searchAccount() {
    FILE *fp = fopen("bank.dat", "rb");
    Account acc;
    int accNo, found = 0;

    printf("Enter Account Number to Search: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("\n--- Account Found ---\n");
            printf("Acc No: %d\n", acc.accNo);
            printf("Name: %s\n", acc.name);
            printf("Balance: ₹%.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(fp);
}

void deposit() {
    FILE *fp = fopen("bank.dat", "rb+");
    Account acc;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, fp);
            printf("Deposit successful. New balance: ₹%.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(fp);
}

void withdraw() {
    FILE *fp = fopen("bank.dat", "rb+");
    Account acc;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, fp);
                printf("Withdrawal successful. New balance: ₹%.2f\n", acc.balance);
            } else {
                printf("Insufficient balance.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(fp);
}
