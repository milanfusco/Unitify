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

Measurement::Measurement(double magnitude, Units* unit)
    : magnitude(magnitude), unit(unit) {}
Measurement::Measurement(const Measurement& other)
    : magnitude(other.magnitude), unit(other.unit) {}
Measurement::~Measurement() {}

double Measurement::getMagnitude() const {
  return magnitude;
}

Units* Measurement::getUnit() const {
  return unit;
}

void Measurement::ensureSameType(const Measurement& m) const {
  if (unit->getType() != m.unit->getType()){
    throw std::invalid_argument("Unit types are not compatible for this operation.");
  } else if (unit->getName() != m.unit->getName()) {
    throw std::invalid_argument("Units are not the same. Cannot perform operation.");
  }
}

Measurement Measurement::operator+(const Measurement& m) const {
  ensureSameType(m);

  return Measurement(magnitude + m.magnitude, unit);
}

Measurement Measurement::operator-(const Measurement& m) const {
  ensureSameType(m);
  return Measurement(magnitude - m.magnitude, unit);
}

Measurement Measurement::operator*(const Measurement& m) const {
  return Measurement(magnitude * m.magnitude, unit); 
}

Measurement Measurement::operator/(const Measurement& m) const {
  if (m.magnitude == 0) {
    throw std::invalid_argument("Undefined, Cannot divide by zero.");
  }
  return Measurement(magnitude / m.magnitude, unit);
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

  Units* unit = Units::getUnitByName(unitStr);
  if (MeasurementValidator::validateUnit(unitStr) == false) {
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
  if (MeasurementValidator::validateUnit(unitStr) == false) {
    throw std::invalid_argument("Invalid unit type: " + unitStr);
  }

  m = Measurement(magnitude, unit);
  return is;
}