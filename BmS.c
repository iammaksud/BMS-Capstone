// ====================================================================================
// BANK MANAGEMENT SYSTEM
// Features: Create, Open, Deposit, Withdraw, Transfer, Balance Check, Edit, Loan
// Language: C
// ====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_ACCOUNTS 100
#define ADMIN_PASSWORD "admin123"

typedef struct
{
    int accountNumber;
    char name[50];
    float balance;
    float loan;
} Account;

Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

// ====================================================================================
// Utility Functions
// ====================================================================================

void pause()
{
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void loadingAnimation()
{
    printf("\nLoading");
    for (int i = 0; i < 3; i++)
    {
        Sleep(300);
        printf(".");
    }
    printf("\n");
}

void saveAccounts()
{
    FILE *fp = fopen("accounts.dat", "wb");
    if (fp != NULL)
    {
        fwrite(&totalAccounts, sizeof(int), 1, fp);
        fwrite(accounts, sizeof(Account), totalAccounts, fp);
        fclose(fp);
    }
}

void loadAccounts()
{
    FILE *fp = fopen("accounts.dat", "rb");
    if (fp != NULL)
    {
        fread(&totalAccounts, sizeof(int), 1, fp);
        fread(accounts, sizeof(Account), totalAccounts, fp);
        fclose(fp);
    }
}

// ====================================================================================
// Create Account
// ====================================================================================
void createAccount()
{
    printf("\n\n========================================\n");
    printf("           🔒 Create Account\n");
    printf("========================================\n");
    if (totalAccounts >= MAX_ACCOUNTS)
    {
        printf("❌ Cannot create more accounts.\n");
        return;
    }
    printf("Enter account number: ");
    scanf("%d", &accounts[totalAccounts].accountNumber);
    printf("Enter name: ");
    scanf("%s", accounts[totalAccounts].name);
    accounts[totalAccounts].balance = 0;
    accounts[totalAccounts].loan = 0;
    totalAccounts++;
    saveAccounts();
    printf("✅ Account created successfully!\n");
}

// ====================================================================================
// Open Account
// ====================================================================================
void openAccount()
{
    printf("\n\n========================================\n");
    printf("           🔓 Open Account\n");
    printf("========================================\n");
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("✅ Account found! Welcome, %s.\n", accounts[i].name);
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// Make Deposit
// ====================================================================================
void depositMoney()
{
    printf("\n\n========================================\n");
    printf("           💵 Make Deposit\n");
    printf("========================================\n");
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;
            saveAccounts();
            printf("✅ Deposit successful!\n");
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// Withdraw Money
// ====================================================================================
void withdrawMoney()
{
    printf("\n\n========================================\n");
    printf("           💲 Withdraw Money\n");
    printf("========================================\n");
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (accounts[i].balance >= amount)
            {
                accounts[i].balance -= amount;
                saveAccounts();
                printf("✅ Withdrawal successful!\n");
            }
            else
            {
                printf("❌ Insufficient balance!\n");
            }
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// Transfer Money
// ====================================================================================
void transferMoney()
{
    printf("\n\n========================================\n");
    printf("           💸 Transfer Money\n");
    printf("========================================\n");
    int fromAcc, toAcc;
    float amount;
    printf("Enter sender account number: ");
    scanf("%d", &fromAcc);
    printf("Enter receiver account number: ");
    scanf("%d", &toAcc);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    Account *sender = NULL, *receiver = NULL;
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == fromAcc)
            sender = &accounts[i];
        if (accounts[i].accountNumber == toAcc)
            receiver = &accounts[i];
    }

    if (sender && receiver)
    {
        if (sender->balance >= amount)
        {
            sender->balance -= amount;
            receiver->balance += amount;
            saveAccounts();
            printf("✅ Transfer successful!\n");
        }
        else
        {
            printf("❌ Insufficient balance!\n");
        }
    }
    else
    {
        printf("❌ Invalid account numbers!\n");
    }
}

// ====================================================================================
// Check Balance
// ====================================================================================
void checkBalance()
{
    printf("\n\n========================================\n");
    printf("           ⚖️ Check Balance\n");
    printf("========================================\n");
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("Balance: %.2f TK\n", accounts[i].balance);
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// View Account Details
// ====================================================================================
void viewAccountDetails()
{
    printf("\n\n========================================\n");
    printf("          📝 View Account Details\n");
    printf("========================================\n");
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("Account Number: %d\n", accounts[i].accountNumber);
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f TK\n", accounts[i].balance);
            printf("Loan: %.2f TK\n", accounts[i].loan);
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// Edit Account
// ====================================================================================
void editAccount()
{
    printf("\n\n========================================\n");
    printf("           ⚙️ Edit Account\n");
    printf("========================================\n");
    int accNum;
    printf("Enter account number to edit: ");
    scanf("%d", &accNum);
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("Enter new name: ");
            scanf("%s", accounts[i].name);
            saveAccounts();
            printf("✅ Account updated successfully!\n");
            return;
        }
    }
    printf("❌ Account not found!\n");
}

// ====================================================================================
// Charge Tax
// ====================================================================================
void chargeTax()
{
    printf("\n\n========================================\n");
    printf("           💰 Charge Tax\n");
    printf("========================================\n");
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    if (strcmp(password, ADMIN_PASSWORD) != 0)
    {
        printf("❌ Access denied!\n");
        return;
    }
    float taxRate;
    printf("Enter tax rate (percentage): ");
    scanf("%f", &taxRate);
    for (int i = 0; i < totalAccounts; i++)
    {
        float taxAmount = (accounts[i].balance * taxRate) / 100;
        accounts[i].balance -= taxAmount;
    }
    saveAccounts();
    printf("✅ Tax deducted successfully from all accounts.\n");
}

// ====================================================================================
// 🤝 Loan Service (with Admin Password Grant)
// ====================================================================================
void takeLoan()
{
    printf("\n\n========================================\n");
    printf("           🤝 Loan Service\n");
    printf("========================================\n");

    char password[20];
    printf("Enter admin password to grant loan: ");
    scanf("%s", password);
    if (strcmp(password, ADMIN_PASSWORD) != 0)
    {
        printf("❌ Access denied!\n");
        return;
    }

    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            if (accounts[i].loan > 0)
            {
                printf("❌ Loan already taken!\n");
                return;
            }
            printf("Enter loan amount: ");
            scanf("%f", &amount);
            if (amount <= accounts[i].balance * 2)
            { // Reasonable limit
                accounts[i].loan = amount;
                accounts[i].balance += amount;
                saveAccounts();
                printf("✅ Loan granted successfully!\n");
            }
            else
            {
                printf("❌ Loan amount too high!\n");
            }
            return;
        }
    }

    printf("❌ Account not found!\n");
}

// ====================================================================================
// Main Function
// ====================================================================================
int main()
{
    SetConsoleOutputCP(CP_UTF8); // Enable UTF-8 for Windows
    loadAccounts();
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("╔══════════════════════════════════════════════════════════════╗\n");
        printf("║                 🏦  BANK MANAGEMENT SYSTEM  🏦               ║\n");
        printf("╠══════════════════════════════════════════════════════════════╣\n");
        printf("║ 1. Create Account        🔒                                  ║\n");
        printf("║ 2. Open Account          🔓                                  ║\n");
        printf("║ 3. Make Deposit          💵                                  ║\n");
        printf("║ 4. Withdraw Money        💳                                  ║\n");
        printf("║ 5. Transfer Money        💸                                  ║\n");
        printf("║ 6. Check Balance         ⚖️                                   ║\n");
        printf("║ 7. View Account Details  📝                                  ║\n");
        printf("║ 8. Edit Account          ⚙️                                   ║\n");
        printf("║ 9. Charge Tax            💰                                  ║\n");
        printf("║10. Loan Service          🤝                                  ║\n");
        printf("║11. Exit                  👋                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n");
        printf("╔════════════════════════════════════════╗\n");
        printf("║ 👉 Please enter your choice (0-10):  \n");
        printf("║ ➤ ");
        scanf("%d", &choice);
        printf("╚════════════════════════════════════════╝\n");

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            openAccount();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            withdrawMoney();
            break;
        case 5:
            transferMoney();
            break;
        case 6:
            checkBalance();
            break;
        case 7:
            viewAccountDetails();
            break;
        case 8:
            editAccount();
            break;
        case 9:
            chargeTax();
            break;
        case 10:
            takeLoan();
            break;
        case 11:
        printf("\n\n========================================\n");
        printf("           👋 Exiting... Thank you!\n");
        printf("========================================\n");
            saveAccounts();
            return 0;
        default:
            printf("❌ Invalid choice!\n");
        }

        pause();
    }

    return 0;
}
