#ifndef OTPMANAGER_H
#define OTPMANAGER_H

#include <string>
#include <ctime>
#include "utils.h"

class OTPManager {
private:
    std::string otp_code;
    time_t expire_time;

public:
    OTPManager() : otp_code(""), expire_time(0) {}

    void generate_otp() {
        otp_code = generate_random_string(6);
        expire_time = std::time(nullptr) + 60; // OTP sống 60 giây
    }

    std::string get_otp() const {
        return otp_code;
    }

    bool validate_otp(const std::string& input) {
        time_t now = std::time(nullptr);
        if (now > expire_time) {
            return false; // Hết hạn
        }
        return input == otp_code;
    }
};

#endif
