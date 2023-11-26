#include <iostream>
#include <iomanip>
#include <string>

class Account {
public:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    virtual void displayDetails() const {
        std::cout << "Account Details for Account (ID: " << accountNumber << "):" << std::endl
                  << "   Holder: " << accountHolder << std::endl
                  << "   Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposited $" << amount << " into the account." << std::endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from the account." << std::endl;
        } else {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
        }
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const override {
        Account::displayDetails();
        std::cout << "   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%" << std::endl;
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    void displayDetails() const override {
        Account::displayDetails();
        std::cout << "   Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << std::endl;
    }

    void withdraw(double amount) override {
        if (balance - amount >= -overdraftLimit) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from the current account." << std::endl;
        } else {
            std::cout << "Exceeded overdraft limit for withdrawal from the current account." << std::endl;
        }
    }
};

// Overload the << operator to display account details
std::ostream& operator<<(std::ostream& os, const Account& account) {
    account.displayDetails();
    return os;
}

// Overload the + operator for transferring money between accounts
CurrentAccount operator+(CurrentAccount current, SavingsAccount& savings) {
    double transferAmount = 300;
    if (savings.balance >= transferAmount) {
        savings.balance -= transferAmount;
        current.balance += transferAmount;
        std::cout << "Transferred $" << transferAmount << " from savings to current account." << std::endl;
    } else {
        std::cout << "Insufficient funds for transfer from savings account." << std::endl;
    }

    return current;
}

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    // Transfer $300 from savings to current
    current = current + savings;

    std::cout << savings << std::endl;
    std::cout << current << std::endl;

    return 0;
}
