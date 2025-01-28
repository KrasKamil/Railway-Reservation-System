#include "Lib/ticket.h"
#include "Lib/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void saveTicketToFile(const User& user, const Train& train) {
    std::ifstream file("Data/tickets.json");
    json tickets;

    if (file.is_open()) {
        try {
            file >> tickets;
        } catch (const json::parse_error& e) {
            std::cerr << "Error parsing tickets.json: " << e.what() << '\n';
        }
        file.close();
    } else {
        tickets = json::array();
    }

    json newTicket = {
        {"username", user.getUsername()},
        {"trainID", train.getTrainID()},
        {"trainName", train.getTrainName()},
        {"startCity", train.getStartCity()},
        {"endCity", train.getEndCity()},
        {"arrivalTime", train.getArrivalTime()},
        {"departureTime", train.getDepartureTime()},
        {"ticketPrice", train.getTicketPrice()}
    };

    tickets.push_back(newTicket);

    std::ofstream outFile("Data/tickets.json");
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing ticket data.\n";
        return;
    }

    outFile << tickets.dump(4);
    outFile.close();
}

json searchTicket(const std::string& username, int trainID) {
    std::ifstream file("Data/tickets.json");
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading ticket data.\n";
        return nullptr;
    }

    json tickets;
    try {
        file >> tickets;
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing tickets.json: " << e.what() << '\n';
        return nullptr;
    }
    file.close();

    if (!tickets.is_array()) {
        std::cerr << "Invalid ticket data format.\n";
        return nullptr;
    }

    for (const auto& ticket : tickets) {
        if (ticket["username"] == username && ticket["trainID"] == trainID) {
            return ticket;
        }
    }

    return nullptr;
}