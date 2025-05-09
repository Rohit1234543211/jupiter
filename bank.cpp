#include <string>
#include <map>
#include <stdexcept>

class Bank {
private:
    struct Account {
        std::string name;
        double balance;
    };
    std::map<std::string, Account> accounts;

public:
    void createAccount(const std::string& accountNumber, const std::string& name) {
        if (accounts.find(accountNumber) != accounts.end()) {
            throw std::runtime_error("Account already exists");
        }
        accounts[accountNumber] = {name, 0.0};
    }

    void deposit(const std::string& accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end()) {
            throw std::runtime_error("Account not found");
        }
        if (amount <= 0) {
            throw std::runtime_error("Invalid amount");
        }
        it->second.balance += amount;
    }

    void withdraw(const std::string& accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end()) {
            throw std::runtime_error("Account not found");
        }
        if (amount <= 0 || amount > it->second.balance) {
            throw std::runtime_error("Invalid amount or insufficient funds");
        }
        it->second.balance -= amount;
    }

    double getBalance(const std::string& accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end()) {
            throw std::runtime_error("Account not found");
        }
        return it->second.balance;
    }

    std::string getAccountName(const std::string& accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end()) {
            throw std::runtime_error("Account not found");
        }
        return it->second.name;
    }
};

// For WebAssembly or server-side integration
extern "C" {
    Bank* createBank() {
        return new Bank();
    }

    void createAccount(Bank* bank, const char* accountNumber, const char* name) {
        try {
            bank->createAccount(accountNumber, name);
        } catch (const std::exception& e) {
            // Handle error (e.g., log or return error code)
        }
    }

    void deposit(Bank* bank, const char* accountNumber, double amount) {
        try {
            bank->deposit(accountNumber, amount);
        } catch (const std::exception& e) {
            // Handle error
        }
    }

    void withdraw(Bank* bank, const char* accountNumber, double amount) {
        try {
            bank->withdraw(accountNumber, amount);
        } catch (const std::exception& e) {
            // Handle error
        }
    }

    double getBalance(Bank* bank, const char* accountNumber) {
        try {
            return bank->getBalance(accountNumber);
        } catch (const std::exception& e) {
            return -1.0; // Error indicator
        }
    }
}
