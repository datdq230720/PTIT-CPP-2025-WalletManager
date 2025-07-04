#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class Wallet {
public:
    std::string wallet_id;                  
    int balance;                            
    std::vector<std::string> transactions;  

    // Constructor: create a wallet with a starting balance for a new user
    Wallet(const std::string& username) {
        wallet_id = "WALLET_" + username;
        balance = 100; // default balance for new accounts
    }

    Wallet() = default; // Default constructor

    // Convert Wallet object to JSON format
    json to_json() const {
        return json{
            {"wallet_id", wallet_id},
            {"balance", balance},
            {"transactions", transactions}
        };
    }

    // Load Wallet object from JSON
    void from_json(const json& j) {
        wallet_id = j.at("wallet_id").get<std::string>();
        balance = j.at("balance").get<int>();
        transactions = j.at("transactions").get<std::vector<std::string>>();
    }

    // Get current balance
    int getBalance() const {
        return balance;
    }

    // Add or subtract balance
    void addBalance(int amount) {
        balance += amount;
    }
};

#endif

