#include "Lib/TrainManager.h"
#include <iostream> 

std::vector<Train> TrainManager::loadTrains() {
    std::vector<Train> trains;
    trains.emplace_back(1, "Express A", "Kraków", "Warszawa", 100, 50.0);
    trains.emplace_back(2, "Intercity B", "Poznań", "Wrocław", 80, 75.0);
    trains.emplace_back(3, "Regional C", "Szczecin", "Kołobrzeg", 120, 30.0);
    return trains;
}

void TrainManager::displayTrains(const std::vector<Train>& trains) {
    std::cout << "\nAvailable Trains:\n";
    for (const auto& train : trains) {
        std::cout << "Train ID: " << train.getTrainID()
                  << ", Name: " << train.getTrainName()
                  << ", Route: " << train.getStartCity() << " -> " << train.getEndCity()
                  << ", Available Seats: " << train.getAvailableSeats()
                  << ", Ticket Price: $" << train.getTicketPrice()
                  << "\n";
    }
}