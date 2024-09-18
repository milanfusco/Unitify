/**
 * @file Measurement.cpp
 * @brief Implementation of the Measurement class
 * 
 * This file implements the methods of the Measurement class.
 * 
 * @version 0.1
*/

#include "Measurement.h"
#include "UnitConverter.h"
#include <stdexcept>
#include <sstream>

Measurement::Measurement(double magnitude, Units* unit) : magnitude(magnitude), unit(unit) {}
Measurement::Measurement(const Measurement& other) : magnitude(other.magnitude), unit(other.unit) {}
Measurement::~Measurement() {}

double Measurement::getMagnitude() const {
    return magnitude;
}

Units* Measurement::getUnit() const {
    return unit;
}

Measurement Measurement::add(const Measurement& m) const {
    if (unit->getName() != m.unit->getName()) {
        throw std::invalid_argument("Units must be the same for addition.");
    }
    return Measurement(magnitude + m.magnitude, unit);
}

Measurement Measurement::subtract(const Measurement& m) const {
    if (unit->getName() != m.unit->getName()) {
        throw std::invalid_argument("Units must be the same for subtraction.");
    }
    return Measurement(magnitude - m.magnitude, unit);
}

Measurement Measurement::multiply(const Measurement& m) const {
    return Measurement(magnitude * m.magnitude, unit);
}

Measurement Measurement::divide(const Measurement& m) const {
    if (m.magnitude == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    return Measurement(magnitude / m.magnitude, unit);
}

int Measurement::compareTo(const Measurement& m) const {
    double baseThis = unit->toBaseUnit(magnitude);
    double baseOther = m.unit->toBaseUnit(m.magnitude);
    if (baseThis < baseOther) return -1;
    if (baseThis > baseOther) return 1;
    return 0;
}

void Measurement::convertToBaseUnit() {
    magnitude = unit->toBaseUnit(magnitude);
}

Measurement Measurement::fromString(const std::string& str) {
    std::istringstream iss(str);
    double magnitude;
    std::string unitStr;
    iss >> magnitude >> unitStr;

    Units* unit = Units::getUnitByName(unitStr);
    if (!unit) {
        throw std::invalid_argument("Invalid unit type in string: " + unitStr);
    }

    return Measurement(magnitude, unit);
}