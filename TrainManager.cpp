#include "Lib/TrainManager.h"
#include "Lib/json.hpp" // Handles JSON parsing
#include <fstream>
#include <iostream>
#include <iomanip> 

using json = nlohmann::json; 

std::vector<Train> TrainManager::loadTrains() {
    std::vector<Train> trains;
    std::ifstream file("Data/trains.json");

    if (!file) {
        std::cout << "Error: Could not open file for reading\n";
        return trains;
    }

    json jTrains;
    file >> jTrains;

    for (const auto& jTrain : jTrains) {
        trains.emplace_back(
            jTrain["trainID"].get<int>(),
            jTrain["name"].get<std::string>(),
            jTrain["startCity"].get<std::string>(),
            jTrain["endCity"].get<std::string>(),
            jTrain["availableSeats"].get<int>(),
            jTrain["ticketPrice"].get<double>(),
            jTrain["arrivalTime"].get<std::string>(),
            jTrain["departureTime"].get<std::string>()
        );
    }

    file.close();
    return trains;
}

void TrainManager::displayTrains(const std::vector<Train>& trains) {
    std::cout << "\nAvailable Trains:\n";
    std::cout << "========================================\n";
    for (const auto& train : trains) {
        std::cout << "Train ID: " << train.getTrainID() << "\n";
        std::cout << "Name: " << train.getTrainName() << "\n";
        std::cout << "Route: " << train.getStartCity() << " -> " << train.getEndCity() << "\n";
        std::cout << "Available Seats: " << train.getAvailableSeats() << "\n";
        std::cout << "Ticket Price: $" << std::fixed << std::setprecision(2) << train.getTicketPrice() << "\n";
        std::cout << "Arrival Time: " << train.getArrivalTime() << "\n";
        std::cout << "Departure Time: " << train.getDepartureTime() << "\n";
        std::cout << "========================================\n";
    }
}