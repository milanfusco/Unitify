/**
 * @file Measurement.cpp
 * @brief Implementation of the Measurement class
 *
 * This file implements the methods of the Measurement class.
 *
 * @version 0.1
 */

#include "Measurement.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "MeasurementValidator.h"
#include "UnitConverter.h"

Measurement::Measurement(double magnitude, std::shared_ptr<Units> unit)
    : magnitude(magnitude), unit(unit) {}  ///> Regular constructor

Measurement::Measurement(const Measurement& other)
    : magnitude(other.magnitude), unit(other.unit) {}  ///> Copy constructor
Measurement::~Measurement() {}                         ///> Destructor

double Measurement::getMagnitude() const {
  return magnitude;
}

std::shared_ptr<Units> Measurement::getUnit() const {
  return unit;
}

// Refactored ensureSameType to handle conversions and return converted
// Measurements
std::pair<Measurement, Measurement> Measurement::ensureSameType(
    const Measurement& other) const {
  if (unit->getType() != other.unit->getType()) {
    throw std::invalid_argument(
        "Measurements must be of the same type for this operation.");
  }

  Measurement leftBase = UnitConverter::convertToBaseUnit(*this);
  Measurement rightBase = UnitConverter::convertToBaseUnit(other);

  return std::make_pair(leftBase, rightBase);
}

Measurement Measurement::operator+(const Measurement& m) const {
  std::pair<Measurement, Measurement> baseUnits = ensureSameType(m);
  return Measurement(baseUnits.first.getMagnitude() + baseUnits.second.getMagnitude(),
                     baseUnits.first.getUnit());
}

Measurement Measurement::operator-(const Measurement& m) const {
  std::pair<Measurement, Measurement> baseUnits = ensureSameType(m);
  return Measurement(baseUnits.first.getMagnitude() - baseUnits.second.getMagnitude(),
                     getUnit());
}

Measurement Measurement::operator*(const Measurement& m) const {
  if (unit->getType() == m.unit->getType()) {
    std::pair<Measurement, Measurement> baseUnits = ensureSameType(m);

    return Measurement(baseUnits.first.getMagnitude() * baseUnits.second.getMagnitude(),
                       baseUnits.first.getUnit());
  } else {
    throw std::invalid_argument(
        "Unit types are not compatible for this operation.");
  }
}

Measurement Measurement::operator/(const Measurement& m) const {
  if (m.magnitude == 0) {
    throw std::invalid_argument("Undefined, Cannot divide by zero.");
  }

  if (this->unit->getType() == m.unit->getType()) {
    std::pair<Measurement, Measurement> baseUnits = ensureSameType(m);
    return Measurement(baseUnits.first.getMagnitude() / baseUnits.second.getMagnitude(),
                       baseUnits.first.getUnit());
  } else {
    throw std::invalid_argument(
        "Unit types are not compatible for this operation.");
  }
}

bool Measurement::operator==(const Measurement& m) const {
  ensureSameType(m);
  return magnitude == m.magnitude;
}

bool Measurement::operator!=(const Measurement& m) const {
  return !(*this == m);
}

bool Measurement::operator<(const Measurement& m) const {
  ensureSameType(m);
  return magnitude < m.magnitude;
}

bool Measurement::operator>(const Measurement& m) const {
  ensureSameType(m);
  return magnitude > m.magnitude;
}

Measurement Measurement::operator=(const Measurement& m) {
  if (this == &m) {
    return *this;
  }
  magnitude = m.magnitude;
  unit = m.unit;
  return *this;
}

Measurement Measurement::fromString(const std::string& str) {
  std::istringstream iss(str);
  double magnitude;
  std::string unitStr;
  iss >> magnitude >> unitStr;

  std::shared_ptr<Units> unit = Units::getUnitByName(unitStr);
  if (MeasurementValidator::validateUnit(unitStr) == false) {
    throw std::invalid_argument("Invalid unit type in string: " + unitStr);
  }

  return Measurement(magnitude, std::shared_ptr<Units>(std::move(unit)));
}

std::ostream& operator<<(std::ostream& os, const Measurement& m) {
  os << m.getMagnitude() << " " << m.getUnit()->getName();
  return os;
}

std::istream& operator>>(std::istream& is, Measurement& m) {
  double magnitude;
  std::string unitStr;
  is >> magnitude >> unitStr;

  std::shared_ptr<Units> unit = Units::getUnitByName(unitStr);
  if (MeasurementValidator::validateUnit(unitStr) == false) {
    throw std::invalid_argument("Invalid unit type: " + unitStr);
  }

  m = Measurement(magnitude, std::move(unit));
  return is;
}
