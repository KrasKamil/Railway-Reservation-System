#include "Lib/User.h" 
#include "Lib/json.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using json = nlohmann::json;

User::User(int id,const std::string& name, const std::string& email,const std::string& password)
: userID(id), username(name), email(email), password(password) {};

int User::getUserID() const {
    return userID;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return inputPassword == password;
}

void User::registerUser(std::vector<User>& users){
    std::string name, email, password; 

    std::cout<<"Enter your name: ";
    std::cin>>name;
    std::cout<<"Enter your email: ";
    std::cin>>email;
    std::cout<<"Enter your password: ";
    std::cin>>password;

    // Convert email to lowercase before registration
    std::transform(email.begin(), email.end(), email.begin(), ::tolower);

    // Check if the email is already in use
    auto it = std::find_if(users.begin(),users.end(),[&email](const User& user){
        return user.getEmail() == email;
    });

    if (it != users.end()){
        std::cout<<"Email already in use\n";
        return;
    }

    // Register the user
    int newID = users.empty() ? 1 : users.back().getUserID() + 1;
    
    users.emplace_back(newID, name, email, password);
    std::cout<<"User registered successfully\n";

    saveToFile(users);
}

void User::saveToFile(const std::vector<User>& users) {
    json jUsers = json::array();

    for (const auto& user : users) {
        jUsers.push_back({
            {"userID", user.getUserID()},
            {"username", user.getUsername()},
            {"email", user.getEmail()},
            {"password", user.getPassword()}
        });
    }

    std::ofstream file("Data/users.json");
    if (!file) {
        std::cout << "Error: Could not open file for writing\n";
        return;
    }

    file << jUsers.dump(4); // 4-space indentation for readability
    file.close();
}

// Login user
User* User::loginUser(std::vector<User>& users, const std::string& email, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(), [&email](const User& user) {
        return user.getEmail() == email;
    });
    if (it != users.end() && it->verifyPassword(password)) {
        std::cout << "Login successful\n";
        return &(*it);
    }
    std::cout << "Invalid email or password\n";
    return nullptr;
}

std::vector<User> User::loadFromFile() {
    std::vector<User> users;
    std::ifstream file("Data/users.json");
    
    if (!file) {
        std::cout << "No existing users file found\n";
        return users;
    }

    json jUsers;
    file >> jUsers;

    for (const auto& jUser : jUsers) {
        users.emplace_back(
            jUser["userID"].get<int>(),
            jUser["username"].get<std::string>(),
            jUser["email"].get<std::string>(),
            jUser["password"].get<std::string>()
        );
    }

    file.close();
    return users;
}

bool User::checkUserExists(const std::string& email) {
    std::vector<User> users = loadFromFile();
    
    auto it = std::find_if(users.begin(), users.end(), 
        [&email](const User& user) {
            return user.getEmail() == email;
        });
    
    return it != users.end();
}

// Reservations

void User::addReservation(int trainID) {
    reservations.push_back(trainID);
}

void User::cancelReservation(int trainID) {
    auto it = std::find(reservations.begin(), reservations.end(), trainID);
    if (it != reservations.end()) {
        reservations.erase(it);
    }
}

std::vector<int> User::getReservations() const {
    return reservations;
}