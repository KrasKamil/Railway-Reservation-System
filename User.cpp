#include "Lib/User.h" 
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

User::User(int id,const std::string& name, const std::string& email,const std::string& password)
: userID(id), username(name), email(email), password(password) {}

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
    std::ofstream file("users.txt");
    if (!file) {
        std::cout << "Error: Could not open file for writing\n";
        return;
    }

    for (const auto& user : users) {
        file << user.getUserID() << ","
             << user.getUsername() << ","
             << user.getEmail() << ","
             << user.getPassword() << "\n";
    }
    file.close();
}

// Login user
bool User::loginUser(std::vector<User>& users, const std::string& email, const std::string& password){
    auto it = std::find_if(users.begin(),users.end(),[&email](const User& user){
        return user.getEmail() == email;
    });
    if (it != users.end() && it->verifyPassword(password)){
        std::cout<<"Login successful\n";
        return true;
    }
    std::cout<<"Invalid email or password\n";
    return false;
}

std::vector<User> User::loadFromFile() {
    std::vector<User> users;
    std::ifstream file("users.txt");
    
    if (!file) {
        std::cout << "No existing users file found\n";
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, email, password;
        
        // Parse CSV format
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, password);
        
        int id = std::stoi(idStr);
        users.emplace_back(id, name, email, password);
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
