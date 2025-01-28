#include "Lib/ReservationManager.h"
#include "Lib/ticket.h"
#include "Lib/json.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using json = nlohmann::json;

void ReservationManager::displayUserReservations(const User& user, const std::vector<Train>& trains) {
    std::ifstream file("Data/tickets.json");
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading ticket data.\n";
        return;
    }

    json tickets;
    try {
        file >> tickets;
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing tickets.json: " << e.what() << '\n';
        return;
    }
    file.close();

    if (!tickets.is_array()) {
        std::cerr << "Invalid ticket data format.\n";
        return;
    }

    bool hasReservations = false;
    std::cout << "Your Reservations:\n";
    std::cout << "========================\n";

    for (const auto& ticket : tickets) {
        if (ticket["username"] == user.getUsername()) {
            hasReservations = true;
            int trainID = ticket["trainID"];
            auto train = std::find_if(trains.begin(), trains.end(),
                [trainID](const Train& t) { return t.getTrainID() == trainID; });

            if (train != trains.end()) {

                std::cout << "========================================\n";
                std::cout << "Train ID: " << train->getTrainID() << "\n";
                std::cout << "Name: " << train->getTrainName() << "\n";
                std::cout << "Route: " << train->getStartCity() << " -> " << train->getEndCity() << "\n";
                std::cout << "Arrival Time: " << train->getArrivalTime() << "\n";
                std::cout << "Departure Time: " << train->getDepartureTime() << "\n";
                std::cout << "Price: $" << std::fixed << std::setprecision(2) << train->getTicketPrice() << "\n";
                std::cout << "========================================\n";
            } else {
                std::cout << "Train ID: " << trainID << " (Details not found)\n";
            }
        }
    }

    if (!hasReservations) {
        std::cout << "You have no reservations.\n";
    }

    std::cout << "========================\n";
}

void ReservationManager::viewTicket(const User& user, const std::vector<Train>& trains) {
    const auto& reservations = user.getReservations();

    if (reservations.empty()) {
        std::cout << "You have no reservations.\n";
        return;
    }

    std::cout << "Your Ticket:\n";
    std::cout << "========================\n";

    for (int trainID : reservations) {
        // Find the train by ID
        auto train = std::find_if(trains.begin(), trains.end(),
            [trainID](const Train& t) { return t.getTrainID() == trainID; });

        if (train != trains.end()) {
            std::cout << "========================================\n";
            std::cout << "| Name: " << user.getName() << "\n";
            std::cout << "| Train ID: " << train->getTrainID() << "\n";
            std::cout << "| Train Name: " << train->getTrainName() << "\n";
            std::cout << "| Route: " << train->getStartCity() << " -> " << train->getEndCity() << "\n";
            std::cout << "| Arrival Time: " << train->getArrivalTime() << "\n";
            std::cout << "| Departure Time: " << train->getDepartureTime() << "\n";
            std::cout << "| Price: $" << std::fixed << std::setprecision(2) << train->getTicketPrice() << "\n";
            std::cout << "========================================\n";
        } else {
            std::cout << "Train ID: " << trainID << " (Details not found)\n";
        }
    }

    std::cout << "========================\n";
}

void ReservationManager::cancelReservation(User& user, int trainID, std::vector<Train>& trains) {
    // Remove reservation from user's list
    user.cancelReservation(trainID);

    // Update available seats for the train
    auto train = std::find_if(trains.begin(), trains.end(),
        [trainID](const Train& t) { return t.getTrainID() == trainID; });

    if (train != trains.end()) {
        train->cancelSeat();
    } else {
        std::cerr << "Train not found.\n";
        return;
    }

    // Remove reservation from tickets.json
    std::ifstream file("Data/tickets.json");
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading ticket data.\n";
        return;
    }
    json tickets;
     try {
        file >> tickets;
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing tickets.json: " << e.what() << '\n';
        return;
    }
    file.close();

    if (!tickets.is_array()) {
        std::cerr << "Invalid ticket data format.\n";
        return;
    }

    auto it = std::remove_if(tickets.begin(), tickets.end(), [&](const json& ticket) {
        return ticket["username"] == user.getUsername() && ticket["trainID"] == trainID;
    });

    if (it != tickets.end()) {
        tickets.erase(it, tickets.end());

        std::ofstream outFile("Data/tickets.json");
        if (!outFile.is_open()) {
            std::cerr << "Unable to open file for writing ticket data.\n";
            return;
        }

        outFile << tickets.dump(4);
        outFile.close();

        std::cout << "Reservation canceled successfully.\n";
    } else {
        std::cout << "No reservation found for the given train ID.\n";
    }
}

std::ostream& operator<<(std::ostream& os, const ReservationManager& rm) {
    if (rm.isLoggedIn) {
        // Display the logged-in menu
        os << "========================\n";
        os << "1. View Available Trains\n";
        os << "2. Book a Ticket\n";
        os << "3. My reservations\n";
        os << "4. Cancel a Reservation\n";
        os << "5. View Ticket\n";
        os << "6. Logout\n";
        os << "========================\n";
        os << "Enter your choice: ";
    } else {
        // Display the main menu
        os << "========================\n";
        os << "Welcome to Train Reservation System.\n";
        os << "========================\n";
        os << "1. Register\n";
        os << "2. Login\n";
        os << "3. Exit\n";
        os << "========================\n";
        os << "Enter your choice: ";
    }
    return os;
}