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

    public: 
        Train(int id, const std::string& name, const std::string& start, const std::string& end, int seats, double price);

        int getTrainID() const; 
        std::string getTrainName() const; 
        std::string getStartCity() const; 
        std::string getEndCity() const;
        int getAvailableSeats() const;
        double getTicketPrice() const;

        bool reserveSeat();
        
        void cancelSeat();

};

#endif