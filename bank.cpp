#include <bits/stdc++.h>
using namespace std;

int caCount = 0, saCount = 0;
class Customer
{
protected:
    string name, acNumber;

public:
    void setter(string name, string acNumber)
    {
        this->name = name;
        this->acNumber = acNumber;
    }
};

class CurAccount : public Customer
{
    float cash = 0, penaltyBalance = 0, minBalance = 500;
    int penalty = 0;
    string password;

public:
    void setter(string name, string acNumber, string password, float cash, float penaltyBalance, float minBalance, int penalty)
    {
        this->name = name;
        this->acNumber = acNumber;
        this->password = password;
        this->cash = cash;
        this->penaltyBalance = penaltyBalance;
        this->minBalance = minBalance;
        this->penalty = penalty;
        caCount++;
    }
    void add()
    {
        string name, acNumber;
        cout << "\t\tEnter your name: ";
        cin >> name;
        cout << "\t\tEnter your account number: ";
        cin >> acNumber;
        this->name = name;
        this->acNumber = acNumber;
        cout << "\t\tEnter min balance: ";
        cin >> minBalance;
        cout << "\t\tEnter account password : ";
        cin >> password;
        fstream caFile("currentAccount.txt", ios::app);
        caFile << name << endl
               << acNumber << endl
               << password << endl
               << cash << endl
               << penaltyBalance << endl
               << minBalance << endl
               << penalty << endl;
        caCount++;
        cout << "\t\tAccount successfully created\n\n\n";
        caFile.close();
    }
    void setDeposit(string _acNumber, string _password)
    {
        fstream u_caFile("u_currentAccount.txt", ios::out);
        if (_acNumber == this->acNumber && _password == this->password)
        {
            float cash;
            cout << "\t\tEnter amount: ";
            cin >> cash;
            this->cash += cash;
        }
        u_caFile << name << endl
                 << acNumber << endl
                 << password << endl
                 << cash << endl
                 << penaltyBalance << endl
                 << minBalance << endl
                 << penalty << endl;
        u_caFile.close();
    }
    void withdrawBalance(string acNumber, string password)
    {
        fstream u_caFile("u_currentAccount.txt", ios::out);
        if (acNumber == this->acNumber && password == this->password)
        {
            float amount;
            cout << "\t\tEnter amount: ";
            cin >> amount;
            if (cash - amount > 0)
            {
                if (cash - amount < minBalance)
                {
                    char c;
                    cout << "\t\tIf your withdraw " << amount << " TK then, an penalty and service charge will added in your account." << endl;
                    cout << "\t\tAre you agree? y/n" << endl;
                    cin >> c;
                    if (c == 'y')
                    {
                        penaltyBalance = amount * (1.5 / 100);
                        this->cash = cash - (amount + penaltyBalance);
                        penalty++;
                    }
                    // else
                    // {
                    //     cout << "Withdraw canceled" << endl;
                    // }
                }
                else
                {
                    this->cash -= amount;
                }
                u_caFile << name << endl
                         << acNumber << endl
                         << password << endl
                         << cash << endl
                         << penaltyBalance << endl
                         << minBalance << endl
                         << penalty << endl;
                u_caFile.close();
            }
        }
        else
        {
            cout << "Account number or password is incorrect" << endl;
        }
    }
    void displayBalance()
    {
        cout << "\t\tCustomer name - " << name << endl;
        cout << "\t\tAccount number - " << acNumber << endl;
        cout << "\t\tAccount type - Current Account" << endl;
        cout << "\t\tyour current balance is " << cash << endl;
    }
    void showInfo()
    {
        cout << "\t\tCustomer name - " << name << endl;
        cout << "\t\tAccount number - " << acNumber << endl;
        cout << "\t\tAccount type - Current Account" << endl;
        cout << "\t\tCurrent balance - " << cash << endl;
        cout << "\t\tMinimum required balance - " << minBalance << endl;
        cout << "\t\tImpose penalty - " << penalty << endl;
    }
    bool validateCustomer(string acNumber, string password)
    {
        return acNumber == this->acNumber && password == this->password;
    }
};

class SavAccount : public Customer
{
    float cash = 0, savingAmount = 0, interestRate = 0;
    int years, monthCount = 0;
    string password;

public:
    void setter(string name, string acNumber, string password, float cash, float savingAmount, float interestRate, int years, int monthCount)
    {
        this->name = name;
        this->acNumber = acNumber;
        this->password = password;
        this->cash = cash;
        this->savingAmount = savingAmount;
        this->interestRate = interestRate;
        this->years = years;
        this->monthCount = monthCount;
        saCount++;
    }
    void add()
    {
        string name, acNumber;
        cout << "\t\tEnter your name: ";
        cin >> name;
        cout << "\t\tEnter your account number: ";
        cin >> acNumber;
        this->name = name;
        this->acNumber = acNumber;
        cout << "\t\tEnter saving amount: ";
        cin >> savingAmount;
        cout << "\t\tEnter interest rate: ";
        cin >> interestRate;
        cout << "\t\tEnter years: ";
        cin >> years;
        cout << "\t\tEnter account password : ";
        cin >> password;
        fstream saFile("savingAccount.txt", ios::app);
        saFile << name << endl
               << acNumber << endl
               << password << endl
               << cash << endl
               << savingAmount << endl
               << interestRate << endl
               << years << endl
               << monthCount << endl;
        cout << "\t\tAccount successfully created\n\n\n";
        saCount++;
    }
    void setDeposit(string acNumber, string password)
    {
        if (acNumber == this->acNumber && password == this->password)
        {
            if (monthCount < years * 12)
            {
                float interest = savingAmount * pow((1 + (interestRate / 100)), years);
                cash += savingAmount + interest;
                monthCount++;
            }
            else
            {
                cout << "\t\tYour account is closed\n\n\n";
            }
        }
        fstream u_saFile("u_savingAccount.txt", ios::out);
        u_saFile << name << endl
                 << acNumber << endl
                 << password << endl
                 << cash << endl
                 << savingAmount << endl
                 << interestRate << endl
                 << years << endl
                 << monthCount << endl;
    }
    void displayBalance()
    {
        cout << "\t\tCustomer name - " << name << endl;
        cout << "\t\tAccount number - " << acNumber << endl;
        cout << "\t\tAccount type - Savings Account" << endl;
        cout << "\t\tyour current balance is " << cash << endl;
    }
    void showInfo()
    {
        cout << "\t\tCustomer name - " << name << endl;
        cout << "\t\tAccount number - " << acNumber << endl;
        cout << "\t\tAccount type - Savings Account" << endl;
        cout << "\t\tCurrent balance - " << cash << endl;
        cout << "\t\tSaving amount - " << savingAmount << endl;
        cout << "\t\tInterest rate - " << interestRate << endl;
        cout << "\t\tNumber of years - " << years << endl;
        cout << "\t\tMonths paid - " << monthCount << endl;
    }
    bool validateCustomer(string acNumber, string password)
    {
        return acNumber == this->acNumber && password == this->password;
    }
};

// ! menu
void showMenu()
{
    cout << "\t\t\t\t\t| ------------------- |" << endl;
    cout << "\t\t\t\t\t| Welcome to our bank |" << endl;
    cout << "\t\t\t\t\t| ------------------- |" << endl;
    cout << "\t1. Create new account" << endl;
    cout << "\t2. Display account information" << endl;
    cout << "\t3. Deposit money" << endl;
    cout << "\t4. Withdraw money" << endl;
    cout << "\t5. Display balance" << endl;
    cout << "\t6. Exit" << endl;
}

// ! account type
void accountType()
{
    cout << "\t\t\t| ------------------- |" << endl;
    cout << "\t\t\t| Select Account Type |" << endl;
    cout << "\t\t\t| ------------------- |" << endl;
    cout << "\t\t1. Current Account" << endl;
    cout << "\t\t2. Saving Account" << endl;
    cout << "\t\t0. Back" << endl;
}
void initializeData(CurAccount currentAccounts[], SavAccount savingAccounts[])
{
    fstream caFile("currentAccount.txt", ios::in);
    if (caFile)
        while (!caFile.eof())
        {
            string name, acNumber, password;
            float cash, penaltyBalance, minBalance;
            int penalty;
            caFile >> name >> acNumber >> password >> cash >> penaltyBalance >> minBalance >> penalty;
            currentAccounts[caCount].setter(name, acNumber, password, cash, penaltyBalance, minBalance, penalty);
        }
    caFile.close();
    fstream saFile("savingAccount.txt", ios::in);
    if (saFile)
        while (!saFile.eof())
        {
            string name, acNumber, password;
            float cash, savingAmount, interestRate;
            int years, monthCount;
            saFile >> name >> acNumber >> password >> cash >> savingAmount >> interestRate >> years >> monthCount;
            savingAccounts[saCount].setter(name, acNumber, password, cash, savingAmount, interestRate, years, monthCount);
        }
    saFile.close();
}

int main()
{
    CurAccount currentAccounts[100];
    SavAccount savingAccounts[100];

    // ! initialize data
    initializeData(currentAccounts, savingAccounts);

    int choice = 1;
    while (choice)
    {
        showMenu();
        cout << "\t";
        cin >> choice;
        if (choice == 1)
        {
            // ! create new account
            system("cls");
            int subChoice = 1;
            while (subChoice)
            {
                accountType();
                cout << "\t\t";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    // ! current account
                    currentAccounts[caCount].add();
                }
                else if (subChoice == 2)
                {
                    // ! saving account
                    savingAccounts[saCount].add();
                }
                else
                    break;
            }
        }
        else if (choice == 2)
        {
            // ! display account information
            system("cls");
            string acNumber, password;
            cout << "\t\tEnter your account number: ";
            cin >> acNumber;
            cout << "\t\tEnter your account password: ";
            cin >> password;
            system("cls");
            int count = 0;
            for (int i = 0; i < caCount; i++)
            {
                if (currentAccounts[i].validateCustomer(acNumber, password))
                {
                    count++;
                    currentAccounts[i].showInfo();
                    cout << "\t\t-----------------------------------------\n\n";
                }
            }
            for (int i = 0; i < saCount; i++)
            {
                if (savingAccounts[i].validateCustomer(acNumber, password))
                {
                    count++;
                    savingAccounts[i].showInfo();
                    cout << "\t\t-----------------------------------------\n\n";
                }
            }
            if (!count)
            {
                cout << "\t\tNo accounts founded\n\n\n";
            }
        }
        else if (choice == 3)
        {
            // ! deposit money
            system("cls");
            string acNumber, password;
            cout << "\t\tEnter your account number: ";
            cin >> acNumber;
            cout << "\t\tEnter your account password: ";
            cin >> password;
            system("cls");
            int count = 0;
            for (int i = 0; i < caCount; i++)
            {
                if (currentAccounts[i].validateCustomer(acNumber, password))
                {
                    count++;
                    currentAccounts[i].setDeposit(acNumber, password);
                    cout << "\t\t-----------------------------------------\n\n";
                }
            }
            remove("currentAccount.txt");
            rename("u_currentAccount.txt", "currentAccount.txt");
            for (int i = 0; i < saCount; i++)
            {
                if (savingAccounts[i].validateCustomer(acNumber, password))
                {
                    count++;
                    savingAccounts[i].setDeposit(acNumber, password);
                    cout << "\t\t-----------------------------------------\n\n";
                }
            }
            remove("savingAccount.txt");
            rename("u_savingAccount.txt", "savingAccount.txt");
            if (!count)
                cout << "\t\tNo accounts founded\n\n\n";
            else
                cout << "\t\tDeposit successfully\n\n\n";
        }
        else if (choice == 4)
        {
            // ! withdraw money
            system("cls");
            string acNumber, password;
            cout << "\t\tEnter your account number: ";
            cin >> acNumber;
            cout << "\t\tEnter your account password: ";
            cin >> password;
            system("cls");
            int count = 0;
            for (int i = 0; i < caCount; i++)
            {
                currentAccounts[i].withdrawBalance(acNumber, password);
            }
            remove("currentAccount.txt");
            rename("u_currentAccount.txt", "currentAccount.txt");
            if (!count)
                cout << "\t\tNo accounts founded\n\n\n";
            else
                cout << "\t\tWithdraw successfully\n\n\n";
        }
        else if (choice == 5)
        {
            // ! display balance
            system("cls");
            string acNumber, password;
            cout << "\t\tEnter your account number: ";
            cin >> acNumber;
            cout << "\t\tEnter your account password: ";
            cin >> password;
            system("cls");
            int count = 0;
            for (int i = 0; i < caCount; i++)
            {
                if (currentAccounts[i].validateCustomer(acNumber, password))
                {
                    count++;
                    currentAccounts[i].displayBalance();
                    cout << "\t\t-----------------------------------------\n\n";
                }
            }
        }
    }
}