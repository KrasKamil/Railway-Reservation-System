#include "Lib/Train.h"
#include <iostream>

Train::Train(int id, const std::string& name, const std::string& start, const std::string& end, int seats, double price, const std::string& arrival, const std::string& departure)
    : trainID(id), trainName(name), startCity(start), endCity(end), availableSeats(seats), ticketPrice(price), arrivalTime(arrival), departureTime(departure) {}

int Train::getTrainID() const {
    return trainID;
}

std::string Train::getTrainName() const {
    return trainName;
}

std::string Train::getStartCity() const {
    return startCity;
}

std::string Train::getEndCity() const {
    return endCity;
}

int Train::getAvailableSeats() const {
    return availableSeats;
}

double Train::getTicketPrice() const {
    return ticketPrice;
}

std::string Train::getArrivalTime() const {
    return arrivalTime;
}

std::string Train::getDepartureTime() const {
    return departureTime;
}

bool Train::reserveSeat() {
    if (availableSeats > 0) {
        --availableSeats;
        return true;
    }
    return false;
}

void Train::cancelSeat() {
    ++availableSeats;
}

void Train::setAvailableSeats(int seats) {
    availableSeats = seats;
}
