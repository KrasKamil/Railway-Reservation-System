#include "Lib/ReservationManager.h"
#include <iostream>
#include <iomanip>

void ReservationManager::displayUserReservations(const User& user, const std::vector<Train>& trains) {
    const auto& reservations = user.getReservations();

    if (reservations.empty()) {
        std::cout << "You have no reservations.\n";
        return;
    }

    std::cout << "Your Reservations:\n";
    std::cout << "========================\n";

    for (int trainID : reservations) {
        // Find the train by ID
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