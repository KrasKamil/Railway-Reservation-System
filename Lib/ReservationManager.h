#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Train.h"
#include "User.h"
#include <vector>
#include <iostream>
#include <algorithm>

class ReservationManager {
    private :
        bool isLoggedIn;
    public:
        // Displays reservations for a given user
        static void displayUserReservations(const User& user, const std::vector<Train>& trains);
        static void viewTicket(const User& user, const std::vector<Train>& trains); 

        ReservationManager() : isLoggedIn(false) {}
        void setLoginStatus(bool status) {
        isLoggedIn = status;
        }

        bool getLoginStatus() const {
            return isLoggedIn;
        }
        friend std::ostream& operator<<(std::ostream& os, const ReservationManager& rm);
};
#endif
