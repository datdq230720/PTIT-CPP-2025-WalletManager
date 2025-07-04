#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string> 
#include "User.h"
#include "OTPManager.h"
#include "Wallet.h"
#include "utils.h"

using namespace std;

class SystemManager {
private:
    vector<User> users;
    OTPManager otp_manager;
    string current_username;
    string current_role;

public:
    // Load users from file
    void load_users(const string& filename) {
        ifstream in(filename);
        if (!in.is_open()) return;

        nlohmann::json j;
        in >> j;
        for (auto& item : j) {
            User u;
            u.from_json(item);
            users.push_back(u);
        }
        in.close();
    }

    // Save users to file
    void save_users(const string& filename) {
        nlohmann::json j;
        for (const auto& u : users) {
            j.push_back(u.to_json());
        }
        ofstream out(filename);
        out << j.dump(4);
        out.close();
    }

    // Register a new user
    bool register_user() {
        string username, password, name;
        cout << "Nhap username: ";
        cin >> username;

        for (auto& u : users) {
            if (u.username == username) {
                cout << "Username da ton tai.\n";
                return false;
            }
        }

        cout << "Nhap password: ";
        cin >> password;
        cin.ignore();
        cout << "Nhap ho ten: ";
        getline(cin, name);

        if (getWalletBalance("admin") < 100) {
            cout << "Vi tong da dat den gioi han, khong the tao tai khoan moi.\n";
            return false;
        }

        string hashed = hashPassword(password, username); // Secure hashed password with salt
        User new_user(username, hashed, name, "user");
        users.push_back(new_user);

        updateWallet("admin", -100);
        

        save_users("users.json");
        backup_users();
        cout << "Dang ky thanh cong!\n";
        return true;
    }

    // Login function
    bool login() {
        string username, password;
        cout << "Nhap username: ";
        cin >> username;
        cout << "Nhap password: ";
        cin >> password;

        string hashed = hashPassword(password, username); 

        for (auto& u : users) {
            if (u.username == username && u.hashed_password == hashed) {
                cout << "Dang nhap thanh cong!\n";
                current_username = username;
                current_role = u.role;
                return true;
            }
        }
        cout << "Sai thong tin dang nhap.\n";
        return false;
    }

    // Backup user list
    void backup_users() {
        save_users("users_backup.json");
    }

    bool is_admin() {
        return current_role == "admin";
    }

    User* get_current_user() {
        for (auto& u : users) {
            if (u.username == current_username) {
                return &u;
            }
        }
        return nullptr;
    }
    
    bool is_admin() const {
	    return current_role == "admin";
	}

    User* find_user_by_username(const string& username) {
        for (auto& u : users) {
            if (u.username == username) {
                return &u;
            }
        }
        return nullptr;
    }

    // Show current user's wallet
    void show_wallet_info() {
        User* u = get_current_user();
        if (u) {
            cout << "Wallet ID: " << u->wallet.wallet_id << "\n";
            cout << "Balance: " << u->wallet.balance << " diem\n";
        }
    }

    // Transfer points to another user
    void transfer_point() {
        string to_username;
        int amount;
        cout << "Chuyen diem den (username): ";
        cin >> to_username;
        cout << "So diem can chuyen: ";
        cin >> amount;

        User* sender = get_current_user();
        User* receiver = find_user_by_username(to_username);

        if (!receiver) {
            cout << "Nguoi nhan khong ton tai!\n";
            return;
        }

        if (sender->wallet.balance < amount) {
            cout << "Khong du diem de chuyen.\n";
            return;
        }

        // OTP verification
        otp_manager.generate_otp();
        cout << "Ma OTP la: " << otp_manager.get_otp() << "\n";
        string input_otp;
        cout << "Nhap OTP de xac nhan: ";
        cin >> input_otp;

        if (!otp_manager.validate_otp(input_otp)) {
            cout << "OTP khong hop le hoac da het han.\n";
            return;
        }

        // Transfer logic
        sender->wallet.balance -= amount;
        receiver->wallet.balance += amount;
        sender->wallet.transactions.push_back("Chuyen " + to_string(amount) + " diem cho " + receiver->username);
        receiver->wallet.transactions.push_back("Nhan " + to_string(amount) + " diem tu " + sender->username);

        save_users("users.json");
        backup_users();

        cout << "Chuyen diem thanh cong!\n";
    }
    
    // change password
    void change_password() {
	    User* user = get_current_user();
	    if (!user) {
	        std::cout << "Khong tim thay nguoi dung dang nhap.\n";
	        return;
	    }
	
	    std::string old_pass, new_pass;
	    std::cout << "Nhap mat khau cu: ";
	    std::cin >> old_pass;
	
	    std::string hashed_old = hashPassword(old_pass, user->username);
	    if (hashed_old != user->hashed_password) {
	        std::cout << "Mat khau cu khong chinh xac.\n";
	        return;
	    }
	
	    std::cout << "Nhap mat khau moi: ";
	    std::cin >> new_pass;
	
	    user->hashed_password = hashPassword(new_pass, user->username);
	
	    save_users("users.json");
	    backup_users();
	
	    std::cout << "Doi mat khau thanh cong.\n";
	}
	
	// List user for admin
    void list_users() {
	    std::cout << "\n--- Danh sach nguoi dung ---\n";
	    for (const auto& u : users) {
	        std::cout << "Username: " << u.username
	                  << " | Ho ten: " << u.full_name
	                  << " | Role: " << u.role
	                  << " | So diem: " << u.wallet.balance << "\n";
	    }
	}
	
	// Delete user for admin
	void delete_user() {
	    std::string target_username;
	    std::cout << "Nhap username can xoa: ";
	    std::cin >> target_username;
	
	    auto it = std::find_if(users.begin(), users.end(),
	        [&](const User& u) { return u.username == target_username; });
	
	    if (it == users.end()) {
	        std::cout << "Khong tim thay nguoi dung.\n";
	        return;
	    }

		if (it->role == "admin") {
		    std::cout << "Khong the xoa tai khoan co quyen admin.\n";
		    return;
		}
	
	    int balance_to_return = it->wallet.balance;
	
	    for (auto& u : users) {
	        if (u.username == "admin") {
	            u.wallet.balance += balance_to_return;
	            u.wallet.transactions.push_back("Nhan " + std::to_string(balance_to_return) + " diem tu xoa user " + target_username);
	            break;
	        }
	    }
	
	    users.erase(it);
	    save_users("users.json");
	    backup_users();
	
	    std::cout << "Da xoa user va chuyen " << balance_to_return << " diem ve tai khoan admin.\n";
	}
	
	// Created user for admin
	void create_user_by_admin() {
	    std::string username, password, full_name;
	
	    std::cout << "Nhap username cho nguoi dung moi: ";
	    std::cin >> username;
	

	    for (const auto& u : users) {
	        if (u.username == username) {
	            std::cout << "Username da ton tai.\n";
	            return;
	        }
	    }
	
	    if (get_current_user()->wallet.balance < 100) {
	        std::cout << "Admin khong du diem de tao tai khoan moi.\n";
	        return;
	    }
	
	    do {
		    std::cout << "Nhap mat khau (khong duoc de trong): ";
		    std::cin >> password;
		    if (password.empty()) {
		        std::cout << "Mat khau khong duoc de trong. Vui long nhap lai.\n";
		    }
		} while (password.empty());
		
	    std::cin.ignore();
	    std::cout << "Nhap ho ten nguoi dung: ";
	    std::getline(std::cin, full_name);
	
	    std::string hashed = hashPassword(password, username);
	    User new_user(username, hashed, full_name, "user");
	    new_user.wallet.balance = 100;
	
	    users.push_back(new_user);
	
	    get_current_user()->wallet.balance -= 100;
	    get_current_user()->wallet.transactions.push_back("Tao user '" + username + "' va chuyen 100 diem");
	
	    save_users("users.json");
	    backup_users();
	
	    std::cout << "Tao tai khoan thanh cong!\n";
	}
	
	// Forgot password
	void forgot_password() {
	    std::string username;
	    std::cout << "Nhap username: ";
	    std::cin >> username;
	
	    User* u = find_user_by_username(username);
	    if (!u) {
	        std::cout << "Khong tim thay nguoi dung.\n";
	        return;
	    }
	
	    // Generate OTP
	    otp_manager.generate_otp();
	    std::cout << "Ma OTP la: " << otp_manager.get_otp() << "\n";
	
	    std::string input_otp;
	    std::cout << "Nhap OTP de xac nhan: ";
	    std::cin >> input_otp;
	
	    if (!otp_manager.validate_otp(input_otp)) {
	        std::cout << "OTP khong hop le hoac da het han.\n";
	        return;
	    }
	
	    // Nhap mat khau moi
	    std::string new_password;
	    do {
	        std::cout << "Nhap mat khau moi (khong de trong): ";
	        std::cin >> new_password;
	        if (new_password.empty()) {
	            std::cout << "Mat khau khong duoc de trong.\n";
	        }
	    } while (new_password.empty());
	
	    u->hashed_password = hashPassword(new_password, u->username);
	
	    save_users("users.json");
	    backup_users();
	
	    std::cout << "Doi mat khau thanh cong!\n";
	}
	
    // Get wallet balance from file
    int getWalletBalance(const string& username) {
	    for (auto& u : users) {
	        if (u.username == username) {
	            return u.wallet.getBalance();
	        }
	    }
	    return 0;
	}

    // Update wallet balance and save
    void updateWallet(const string& username, int amount) {
	    for (auto& u : users) {
	        if (u.username == username) {
	            u.wallet.addBalance(amount);
	            return;
	        }
	    }
	}
};

#endif

