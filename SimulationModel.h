#ifndef SIMULATIONMODEL_H
#define SIMULATIONMODEL_H

#include "Country.h"
#include <vector>
#include <utility>

class SimulationModel {
public:
    static long exponential(const Country &c, double rate, int years);
    static long logistic(const Country &c, double rate, int years, long carryingCapacity);
    static std::vector<long> simulateCrisis(const Country &c, double extraDeathRate, int years);
    static std::pair<std::vector<long>, std::vector<long>> compareBirthScenarios(
        const Country &c, double rate1, double rate2, int years, long carryingCapacity);
};

#endif // SIMULATIONMODEL_H
