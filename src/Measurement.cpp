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
#include "MeasurementValidator.h"
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
    ensureSameUnit(m);  
    return Measurement(magnitude + m.magnitude, unit);
}

Measurement Measurement::subtract(const Measurement& m) const {
    ensureSameUnit(m);  
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

Measurement::ComparisonResult Measurement::compareTo(const Measurement& m) const {
    double baseThis = unit->toBaseUnit(magnitude);
    double baseOther = m.unit->toBaseUnit(m.magnitude);
    if (baseThis < baseOther) 
        return Measurement::ComparisonResult::LESS_THAN;
    if (baseThis > baseOther) 
        return Measurement::ComparisonResult::GREATER_THAN;
    return Measurement::ComparisonResult::EQUAL;
}

void Measurement::ensureSameUnit(const Measurement& m) const {
    if (unit->getName() != m.unit->getName()) {
        throw std::invalid_argument("Units must be the same for this operation.");
    }
}

Measurement Measurement::fromString(const std::string& str) {
    std::istringstream iss(str);
    double magnitude;
    std::string unitStr;
    iss >> magnitude >> unitStr;

    Units* unit = Units::getUnitByName(unitStr);
    if (MeasurementValidator::validateUnit(unitStr)==false) {
        throw std::invalid_argument("Invalid unit type in string: " + unitStr);
    }

    return Measurement(magnitude, unit);
}

std::ostream& operator<<(std::ostream& os, const Measurement& m) {
    os << m.getMagnitude() << " " << m.getUnit()->getName();
    return os;
}

std::istream& operator>>(std::istream& is, Measurement& m) {
    double magnitude;
    std::string unitStr;
    is >> magnitude >> unitStr;

    Units* unit = Units::getUnitByName(unitStr);
    if (MeasurementValidator::validateUnit(unitStr)==false) {
        throw std::invalid_argument("Invalid unit type: " + unitStr);
    }

    m = Measurement(magnitude, unit);
    return is;
}