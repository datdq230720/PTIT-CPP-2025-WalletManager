#ifndef OTPMANAGER_H
#define OTPMANAGER_H

#include <string>
#include <ctime>
#include <cstdlib> 
#include <sstream>

class OTPManager {
private:
    std::string otp_code; 
    time_t expire_time;     

    // Generate a 6-digit random OTP as string
    std::string generate_otp_string() {
	    std::string otp = "";
	    std::string characters = "0123456789";
	    int charCount = characters.size();
	
	    // Seed the random number generator
	    std::srand(std::time(0));
	
	    for (int i = 0; i < 6; ++i) {
	        otp += characters[std::rand() % charCount];
	    }
	
	    return otp;
	}

public:
    OTPManager() : otp_code(""), expire_time(0) {}

    void generate_otp() {
        srand(time(0)); // seed once per second
        otp_code = generate_otp_string();
        expire_time = std::time(nullptr) + 60; // OTP valid for 60 seconds
    }

    std::string get_otp() const {
        return otp_code;
    }

    bool validate_otp(const std::string& input) {
        time_t now = std::time(nullptr);
        if (now > expire_time) {
            return false; // expired
        }
        return input == otp_code;
    }
};

#endif

