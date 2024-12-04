#ifndef TRAIN_MANAGER_H
#define TRAIN_MANAGER_H

#include "Train.h"
#include <vector>

class TrainManager {
public:
    static std::vector<Train> loadTrains(); // Deklaracja funkcji
    static void displayTrains(const std::vector<Train>& trains);
};
#endif
