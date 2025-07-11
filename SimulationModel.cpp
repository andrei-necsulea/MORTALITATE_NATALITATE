#include "SimulationModel.h"
#include <cmath>

// Exponential model: P = P0 * exp(rate * years)
long SimulationModel::exponential(const Country &c, double rate, int years) {
    return static_cast<long>(c.population() * std::exp(rate * years));
}

// Logistic model: P = K / (1 + ((K - P0) / P0) * exp(-rate * years))
long SimulationModel::logistic(const Country &c, double rate, int years, long carryingCapacity) {
    double P0 = static_cast<double>(c.population());
    double K = static_cast<double>(carryingCapacity);
    double expTerm = std::exp(-rate * years);
    return static_cast<long>(K / (1.0 + ((K - P0) / P0) * expTerm));
}

// Simulate crisis: temporarily increased death rate
std::vector<long> SimulationModel::simulateCrisis(const Country &c, double extraDeathRate, int years) {
    std::vector<long> population;
    double rate = c.birthRate() - c.deathRate() - extraDeathRate;
    for (int i = 0; i <= years; ++i) {
        population.push_back(exponential(c, rate, i));
    }
    return population;
}

// Compare two birth rate scenarios
std::pair<std::vector<long>, std::vector<long>> SimulationModel::compareBirthScenarios(
    const Country &c, double rate1, double rate2, int years, long carryingCapacity) {
    std::vector<long> scenario1, scenario2;
    double net1 = rate1 - c.deathRate();
    double net2 = rate2 - c.deathRate();
    for (int i = 0; i <= years; ++i) {
        scenario1.push_back(exponential(c, net1, i));
        scenario2.push_back(logistic(c, net2, i, carryingCapacity));
    }
    return {scenario1, scenario2};
}
