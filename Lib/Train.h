#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>

class Train{

    private: 
        int trainID;
        std::string trainName;
        std::string startCity;
        std::string endCity;
        int availableSeats;
        double ticketPrice;
        std::string arrivalTime;
        std::string departureTime;

    public: 
        Train(int id, const std::string& name, const std::string& start, const std::string& end, int seats, double price, const std::string& arrival, const std::string& departure);

        int getTrainID() const; 
        std::string getTrainName() const; 
        std::string getStartCity() const; 
        std::string getEndCity() const;
        int getAvailableSeats() const;
        double getTicketPrice() const;
        std::string getArrivalTime() const;
        std::string getDepartureTime() const;

        bool reserveSeat();
        
        void cancelSeat();

};

#endif