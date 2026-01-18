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

// ====================================================================================
// Structures
// ====================================================================================

typedef struct
{
    int accountNumber;
    char name[50];
    char phone[20];
    char email[50];
    int pin;
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
    printf("         🔒 Create New Account\n");
    printf("========================================\n");

    if (totalAccounts >= MAX_ACCOUNTS)
    {
        printf("❌ Cannot create more accounts. The bank is at full capacity.\n");
        return;
    }

    printf("\nPlease enter the following details to create an account:\n");

    printf("========================================\n");
    printf("📌 Account Number: ");
    scanf("%d", &accounts[totalAccounts].accountNumber);

    printf("📛 Name: ");
    scanf("%s", accounts[totalAccounts].name);

    printf("📱 Phone Number: ");
    scanf("%s", accounts[totalAccounts].phone);

    printf("📧 Email Address: ");
    scanf("%s", accounts[totalAccounts].email);

    printf("🔐 Set a 4-digit PIN (security purpose): ");
    scanf("%d", &accounts[totalAccounts].pin);

    if (accounts[totalAccounts].pin < 1000 || accounts[totalAccounts].pin > 9999)
    {
        printf("❌ Invalid PIN! The PIN should be a 4-digit number.\n");
        return;
    }

    accounts[totalAccounts].balance = 0;
    accounts[totalAccounts].loan = 0;
    totalAccounts++;

    saveAccounts();

    printf("\n========================================\n");
    printf("✅ Account created successfully!\n");
    printf("Welcome to the bank, %s! 🎉\n", accounts[totalAccounts - 1].name);
    printf("========================================\n");
}

int verifyPin(Account *acc)
{
    int inputPin;
    printf("Enter 4-digit PIN: ");
    scanf("%d", &inputPin);
    if (inputPin == acc->pin)
        return 1;
    printf("❌ Incorrect PIN!\n");
    return 0;
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
    printf("\n📋 Please enter your account number to open your account:\n");

    printf("========================================\n");
    printf("🔑 Account Number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("\n========================================\n");
            printf("✅ Account found! Welcome, %s.\n", accounts[i].name);
            printf("Your current balance is: %.2f TK\n", accounts[i].balance);
            printf("========================================\n");
            return;
        }
    }

    printf("\n========================================\n");
    printf("❌ Account not found! Please check the account number and try again.\n");
    printf("========================================\n");
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

    printf("\n📋 Please enter your account number to deposit money:\n");
    printf("========================================\n");
    printf("🔑 Account Number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            printf("\n========================================\n");
            printf("✅ Account found: %s\n", accounts[i].name);
            printf("Your current balance: %.2f TK\n", accounts[i].balance);
            printf("========================================\n");

            printf("💰 Enter amount to deposit: ");
            scanf("%f", &amount);

            if (amount > 0)
            {
                accounts[i].balance += amount;
                saveAccounts();
                printf("\n========================================\n");
                printf("✅ Deposit of %.2f TK successful!\n", amount);
                printf("Updated balance: %.2f TK\n", accounts[i].balance);
                printf("========================================\n");
            }
            else
            {
                printf("\n========================================\n");
                printf("❌ Invalid deposit amount! Please enter a positive value.\n");
                printf("========================================\n");
            }
            return;
        }
    }

    printf("\n========================================\n");
    printf("❌ Account not found! Please check the account number and try again.\n");
    printf("========================================\n");
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

    printf("\n📋 Please enter your account number to withdraw money:\n");
    printf("========================================\n");
    printf("🔑 Account Number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {

            if (!verifyPin(&accounts[i]))
                return;

            printf("\n========================================\n");
            printf("✅ Account found: %s\n", accounts[i].name);
            printf("Your current balance: %.2f TK\n", accounts[i].balance);
            printf("========================================\n");

            printf("💰 Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("\n========================================\n");
                printf("❌ Invalid amount! Please enter a positive value.\n");
                printf("========================================\n");
                return;
            }

            if (accounts[i].balance >= amount)
            {
                accounts[i].balance -= amount;
                saveAccounts();
                printf("\n========================================\n");
                printf("✅ Withdrawal of %.2f TK successful!\n", amount);
                printf("Updated balance: %.2f TK\n", accounts[i].balance);
                printf("========================================\n");
            }
            else
            {
                printf("\n========================================\n");
                printf("❌ Insufficient balance! Please try again with a lower amount.\n");
                printf("========================================\n");
            }
            return;
        }
    }

    printf("\n========================================\n");
    printf("❌ Account not found! Please check the account number and try again.\n");
    printf("========================================\n");
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

    printf("\n📋 Please enter the sender's account number:\n");
    printf("========================================\n");
    printf("🔑 Sender Account Number: ");
    scanf("%d", &fromAcc);

    printf("\n📋 Please enter the receiver's account number:\n");
    printf("========================================\n");
    printf("🔑 Receiver Account Number: ");
    scanf("%d", &toAcc);

    printf("\n💰 Enter the amount to transfer:\n");
    printf("========================================\n");
    printf("💸 Amount to Transfer: ");
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

        if (!verifyPin(sender))
            return;

        if (sender->balance >= amount)
        {
            sender->balance -= amount;
            receiver->balance += amount;
            saveAccounts();
            printf("\n========================================\n");
            printf("✅ Transfer of %.2f TK from Account %d to Account %d successful!\n", amount, fromAcc, toAcc);
            printf("Updated Balance - Sender: %.2f TK, Receiver: %.2f TK\n", sender->balance, receiver->balance);
            printf("========================================\n");
        }
        else
        {
            printf("\n========================================\n");
            printf("❌ Insufficient balance in the sender's account!\n");
            printf("========================================\n");
        }
    }
    else
    {
        printf("\n========================================\n");
        printf("❌ Invalid account numbers! Please check the account numbers and try again.\n");
        printf("========================================\n");
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
    printf("\n🔑 Enter account number to check balance:\n");
    printf("========================================\n");
    printf("🔑 Account Number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {

            if (!verifyPin(&accounts[i]))
                return;

            printf("\n========================================\n");
            printf("✅ Account found! Your current balance is:\n");
            printf("========================================\n");
            printf("💰 Balance: %.2f TK\n", accounts[i].balance);
            printf("========================================\n");
            return;
        }
    }

    printf("\n========================================\n");
    printf("❌ Account not found! Please check the account number and try again.\n");
    printf("========================================\n");
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
    printf("🔑 Enter account number to view details:\n");
    printf("========================================\n");
    printf("🔑 Account Number: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {

            printf("\n========================================\n");
            printf("        ✅ Account Details\n");
            printf("========================================\n");
            printf("📋 Account Number: %d\n", accounts[i].accountNumber);
            printf("🧑‍💼 Name: %s\n", accounts[i].name);
            printf("📞 Phone: %s\n", accounts[i].phone);
            printf("📧 Email: %s\n", accounts[i].email);
            printf("💰 Balance: %.2f TK\n", accounts[i].balance);
            printf("💳 Loan: %.2f TK\n", accounts[i].loan);
            printf("========================================\n");
            return;
        }
    }

    printf("\n========================================\n");
    printf("❌ Account not found! Please check the account number and try again.\n");
    printf("========================================\n");
}

// ====================================================================================
// Edit Account
// ====================================================================================

void editAccount()
{
    int choice;
    int accNum;

    printf("\n\n========================================\n");
    printf("           ⚙️ Edit Account\n");
    printf("========================================\n");

    printf("🔑 Enter account number to edit: ");
    scanf("%d", &accNum);

    int found = 0;
    int index = -1;

    // Search for account by account number
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {
            found = 1;
            index = i;
            printf("\nAccount found: %s\n", accounts[i].name);
            break;
        }
    }

    if (!found)
    {
        printf("❌ Account not found!\n");
        return;
    }

    printf("\n========================================\n");
    printf("          ✏️  Edit Account Menu\n");
    printf("========================================\n");
    printf(" 1. Edit Name\n");
    printf(" 2. Edit PIN\n");
    printf(" 3. Edit Balance\n");
    printf(" 4. Delete Account\n");
    printf(" 5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        printf("\nEnter new name: ");
        getchar(); // clear leftover newline
        fgets(accounts[index].name, sizeof(accounts[index].name), stdin);
        accounts[index].name[strcspn(accounts[index].name, "\n")] = '\0';
        saveAccounts();
        printf("✅ Name updated successfully!\n");
        break;
    }

    case 2:
    {
        printf("\nEnter new 4-digit PIN: ");
        scanf("%s", accounts[index].pin);
        saveAccounts();
        printf("✅ PIN updated successfully!\n");
        break;
    }

    case 3:
    {
        float newBalance;
        printf("\nEnter new balance: ");
        scanf("%f", &newBalance);
        accounts[index].balance = newBalance;
        saveAccounts();
        printf("✅ Balance updated successfully!\n");
        printf("💰 New Balance: %.2f\n", accounts[index].balance);
        break;
    }

    case 4:
    {
        char confirm;
        printf("\nAre you sure you want to delete this account? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y')
        {
            for (int j = index; j < totalAccounts - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            totalAccounts--;
            saveAccounts();
            printf("✅ Account deleted successfully!\n");
        }
        else
        {
            printf("❌ Account deletion cancelled.\n");
        }
        break;
    }

    case 5:
    {
        printf("👋 Exiting Edit Account Menu...\n");
        return;
    }

    default:
        printf("❌ Invalid choice! Please try again.\n");
    }
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

    printf("🔑 Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) != 0)
    {
        printf("❌ Access denied! Incorrect password.\n");
        return;
    }

    float taxRate;

    printf("\nEnter tax rate (percentage): ");
    scanf("%f", &taxRate);

    printf("\n========================================\n");
    printf("        Tax Deduction in Progress...\n");
    printf("========================================\n");

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

    printf("🔑 Enter admin password to grant loan: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) != 0)
    {
        printf("\n❌ Access Denied! Incorrect password.\n");
        return;
    }

    int accNum;
    float amount;

    printf("\nEnter account number to grant loan: ");
    scanf("%d", &accNum);

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accNum)
        {

            if (accounts[i].loan > 0)
            {
                printf("\n❌ Loan already granted! This account already has an active loan.\n");
                return;
            }

            printf("\nEnter loan amount to grant: ");
            scanf("%f", &amount);

            if (amount <= accounts[i].balance * 2)
            {
                accounts[i].loan = amount;
                accounts[i].balance += amount;
                saveAccounts();
                printf("\n✅ Loan successfully granted!\n");
                printf("📈 New Balance: %.2f TK\n", accounts[i].balance);
                return;
            }
            else
            {
                printf("\n❌ Loan amount exceeds the maximum permissible limit (2x balance).\n");
                return;
            }
        }
    }

    printf("\n❌ Account not found! Please check the account number.\n");
}

// ====================================================================================
// Display Logo
// ====================================================================================

void displayLogo()
{

    printf("\n");
    printf("    ██████╗  █████╗ ███╗   ██╗██╗  ██╗    ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗\n");
    printf("    ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝    ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║\n");
    printf("    ██████╔╝███████║██╔██╗ ██║█████╔╝     ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║\n");
    printf("    ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗     ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║\n");
    printf("    ██████╔╝██║  ██║██║ ╚████║██║  ██╗    ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║\n");
    printf("    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝    ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝\n");
    printf("\n");
}

// ====================================================================================
// Main Function
// ====================================================================================

int main()
{

    SetConsoleOutputCP(CP_UTF8);
    loadAccounts();
    int choice;
    
    displayLogo();

    while (1)
    {
        printf("\n\n");
        printf("╔══════════════════════════════════════════════════════════════════════╗\n");
        printf("║                    🏦  BANK MANAGEMENT SYSTEM  🏦                    ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════╣\n");
        printf("║ 1. Create Account        🔒                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 2. Open Account          🔓                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 3. Make Deposit          💵                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 4. Withdraw Money        💳                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 5. Transfer Money        💸                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 6. Check Balance         ⚖️                                           ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 7. View Account Details  📝                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 8. Edit Account          ⚙️                                           ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║ 9. Charge Tax            💰                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║10. Loan Service          🤝                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("║11. Exit                  👋                                          ║\n");
        printf("║ ----------------------------------------                             ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════╝\n");
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
            printf("          ✨  Goodbye from Bank System  ✨\n");
            printf("========================================\n");
            printf("           👋 Exiting... Thank you!    \n");
            printf("========================================\n");
            printf("          🏦 We hope to see you soon!   \n");
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
