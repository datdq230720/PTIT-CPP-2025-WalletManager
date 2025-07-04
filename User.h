#ifndef USER_H
#define USER_H

#include "Wallet.h"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class User
{
public:
    std::string username;
    std::string hashed_password;
    std::string full_name;
    std::string role; 
    Wallet wallet;

    User(const std::string &uname, const std::string &pwd_hash, const std::string &name, const std::string &r)
        : username(uname), hashed_password(pwd_hash), full_name(name), role(r), wallet(uname) {}

    User() = default;

    json to_json() const
    {
        return json{
            {"username", username},
            {"hashed_password", hashed_password},
            {"full_name", full_name},
            {"role", role},
            {"wallet", wallet.to_json()}};
    }

    void from_json(const json &j)
    {
        username = j.at("username").get<std::string>();
        hashed_password = j.at("hashed_password").get<std::string>();
        full_name = j.at("full_name").get<std::string>();
        role = j.at("role").get<std::string>();
        wallet.from_json(j.at("wallet"));
    }
};

#endif
