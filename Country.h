#ifndef COUNTRY_H
#define COUNTRY_H

#include <QString>

class Country {
public:
    Country(const QString &name, long population, double birthRate, double deathRate)
        : m_name(name), m_population(population), m_birthRate(birthRate), m_deathRate(deathRate) {}

    QString name() const { return m_name; }
    long population() const { return m_population; }
    double birthRate() const { return m_birthRate; }
    double deathRate() const { return m_deathRate; }

    void setPopulation(long pop) { m_population = pop; }
    void setBirthRate(double br) { m_birthRate = br; }
    void setDeathRate(double dr) { m_deathRate = dr; }

private:
    QString m_name;
    long m_population;
    double m_birthRate;
    double m_deathRate;
};

#endif // COUNTRY_H
