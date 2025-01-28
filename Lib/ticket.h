#ifndef TICKET_H
#define TICKET_H

#include "User.h"
#include "Train.h"
#include "json.hpp"

using json = nlohmann::json;

void saveTicketToFile(const User& user, const Train& train);
json searchTicket(const std::string& username, int trainID);

#endif