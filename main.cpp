#include "Lib/User.h"
#include "Lib/TrainManager.h"
#include "Lib/Train.h"
#include "Lib/ReservationManager.h"
#include "Lib/ticket.h"
#include <iostream>
#include <vector>
#include <algorithm> // For std::find_if
#include <limits>    // For numeric_limits
#include <cstdlib>   // For system()

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    // Load users from file
    std::vector<User> users = User::loadFromFile();

    // Load trains from file
    std::vector<Train> trains = TrainManager::loadTrains();

    // Create an instance of ReservationManager
    ReservationManager rm; 

    // Print the main menu
    std::cout << rm;  
    int choice;
    bool running = true;

    while (running) {
        std::cin >> choice;

        // Check if the input is valid
        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number from the menu.\n";
            std::cout << rm;  // Re-print the main menu after invalid input
            continue;
        }

        clearConsole(); // Clear console after each choice

        switch (choice) {
        case 1: {
            // Register new user
            User newUser("temp");
            newUser.registerUser(users);
            std::cout << rm;  // Return to main menu after registration
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
                rm.setLoginStatus(true); 
                std::cout << "Welcome, " << loggedInUser->getUsername() << "! You are now logged in!\n";

                // Menu after login
                bool inBookingMenu = true;
                while (inBookingMenu) {
                    // Print logged-in menu
                    std::cout << rm;  // Use overloaded << operator to print logged-in menu
                    int bookingChoice;
                    std::cin >> bookingChoice;

                    // Check if the input is valid
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number from the menu.\n";
                        std::cout << rm;  // Re-print the logged-in menu after invalid input
                        continue;
                    }

                    clearConsole(); // Clear console after each choice

                    switch (bookingChoice) {
                    case 1:
                        // Display available trains
                        TrainManager::displayTrains(trains);
                        break;
                    case 2: {
                        // Ticket booking
                        std::cout << "Enter Train ID to book a ticket: ";
                        int trainID;
                        std::cin >> trainID;

                        auto train = std::find_if(trains.begin(), trains.end(),
                            [trainID](const Train& t) { return t.getTrainID() == trainID; });

                        if (train != trains.end()) {
                            if (train->reserveSeat()) {
                                loggedInUser->addReservation(trainID);
                                saveTicketToFile(*loggedInUser, *train);
                                std::cout << "Ticket booked successfully for Train: " << train->getTrainName() << "\n";
                            } else {
                                std::cout << "No seats available on this train.\n";
                            }
                        } else {
                            std::cout << "Invalid Train ID. Please try again.\n";
                        }
                        break;
                    }
                    case 3: {
                        // Show user reservations
                        if (loggedInUser) {
                            ReservationManager::displayUserReservations(*loggedInUser, trains);
                        } else {
                            std::cout << "You must be logged in to view your reservations.\n";
                        }
                        break;
                    }
                    case 4: {
                        // Cancel reservation
                        if (loggedInUser) {
                            // Display the user's reservations
                            ReservationManager::displayUserReservations(*loggedInUser, trains);

                            // Check if the user has reservations
                            const auto& reservations = loggedInUser->getReservations();
                            if (reservations.empty()) {
                                break;  // No reservations, go back to the menu
                            }

                            // If the user has reservations, prompt for Train ID to cancel
                            std::cout << "Enter Train ID to cancel reservation: ";
                            int cancelID;
                            std::cin >> cancelID;

                            // Find the train by the provided Train ID
                            auto trainToCancel = std::find_if(trains.begin(), trains.end(),
                                [cancelID](const Train& t) { return t.getTrainID() == cancelID; });

                            // If the train exists, cancel the reservation
                              if (trainToCancel != trains.end()) {
                                rm.cancelReservation(*loggedInUser, cancelID, trains);
                            } else {
                                std::cout << "Invalid Train ID. Please try again.\n";
                            }
                        } else {
                            std::cout << "You must be logged in to cancel reservations.\n";
                        }
                        break;
                    }
                     case 5:
                        // View ticket
                        if (loggedInUser) {
                            ReservationManager::viewTicket(*loggedInUser, trains);
                        } else {
                            std::cout << "You must be logged in to view your ticket.\n";
                        }
                        break;
                    case 6:
                        // Log out
                        rm.setLoginStatus(false);
                        inBookingMenu = false;
                        std::cout << "Logged out successfully.\n";
                        std::cout << rm; // Print main menu again after logout
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        std::cout << rm;  // Re-print the logged-in menu after invalid choice
                        break;
                    }
                }
            } else {
                std::cout << "Login failed. Please check your credentials.\n";
                std::cout << rm; // Print main menu again after login failure
            }
            break;
        }
        case 3: {
            running = false;
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << rm;  // Reprint main menu after invalid choice
            break;
        }
    }

    return 0;
}
