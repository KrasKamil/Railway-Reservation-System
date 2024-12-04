#include "Lib/ReservationManager.h"

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
            std::cout << "Train ID: " << train->getTrainID()
                      << ", Name: " << train->getTrainName()
                      << ", From: " << train->getStartCity()
                      << ", To: " << train->getEndCity()
                      << ", Price: $" << train->getTicketPrice()
                      << "\n";
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
        os << "5. Logout\n";
        os << "========================\n";
        os << "Enter your choice: ";
    } else {
        // Display the main menu
        os << "========================\n";
        os << "1. Register\n";
        os << "2. Login\n";
        os << "3. Exit\n";
        os << "========================\n";
        os << "Enter your choice: ";
    }
    return os;
}