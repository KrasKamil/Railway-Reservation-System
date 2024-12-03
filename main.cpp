#include "User.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Wczytanie użytkowników z pliku
    std::vector<User> users = User::loadFromFile();

    int choice;
    bool running = true;

    while (running) {
        
        std::cout << "========================\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "========================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // New User registration
            User newUser;
            newUser.registerUser(users);
            break;
        }
        case 2: {
            // User login
            std::string email, password;
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your password: ";
            std::cin >> password;

            if (User* loggedInUser = User::loginUser(users, email, password)) {
                std::cout << "Welcome, " << loggedInUser->getUsername() << "! You are now logged in!\n";
            } else {
                std::cout << "Login failed. Please check your credentials.\n";
            }
            break;
        }
        case 3:
            // Exit program
            running = false;
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
