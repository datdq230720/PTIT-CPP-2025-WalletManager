#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Very basic hash simulation
string simple_hash(const string& password) {
    stringstream ss;
    for (char c : password) {
        ss << int(c) + 13;
    }
    return ss.str();
}

// Simulate password hashing with salt
string hashPassword(string password, string username) {
	return simple_hash(password + username);
}

#endif
