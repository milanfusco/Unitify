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
#include "CompoundUnit.h"
#include "MeasurementValidator.h"
#include "UnitConverter.h"

Measurement::Measurement(double magnitude, std::shared_ptr<Units> unit)
    : magnitude(magnitude), unit(unit) {}  ///> Regular constructor

Measurement::Measurement(double magnitude, std::shared_ptr<CompoundUnit> unit)
    : magnitude(magnitude),
      unit(unit) {}  ///> Constructor for CompoundUnit measurements

Measurement::Measurement(const Measurement& other)
    : magnitude(other.magnitude), unit(other.unit) {}  ///> Copy constructor
Measurement::~Measurement() {}                         ///> Destructor

double Measurement::getMagnitude() const {
  return magnitude;
}

std::shared_ptr<Units> Measurement::getUnit() const {
  return unit;
}

std::shared_ptr<CompoundUnit> Measurement::getCompoundUnit() const {
  // Check if the unit can be cast to CompoundUnit
  std::shared_ptr<CompoundUnit> compoundUnit =
      std::dynamic_pointer_cast<CompoundUnit>(unit);
  if (!compoundUnit) {
    throw std::runtime_error("Unit is not a CompoundUnit");
  }
  return compoundUnit;
}

std::string Measurement::getCompoundUnitName() const {
  std::shared_ptr<CompoundUnit> compoundUnit = getCompoundUnit();
  return compoundUnit->getCompoundName();
}

std::shared_ptr<CompoundUnit> Measurement::createCompoundUnit(
    const Measurement& left, const Measurement& right, char operation) const {
    
    std::vector<std::shared_ptr<Units>> units;
    std::vector<char> operators;

    // Handle left-hand side units
    if (auto leftCompound = std::dynamic_pointer_cast<CompoundUnit>(left.unit)) {
        units = leftCompound->getUnits();
        operators = leftCompound->getOperators();
    } else {
        units.push_back(left.unit);  // Treat as single unit
    }

    // Add right-hand side unit and operator
    units.push_back(right.unit);
    operators.push_back(operation);

    // Check operator balance
    if (operators.size() != units.size() - 1) {
        std::cerr << "Units size: " << units.size() << std::endl;
        std::cerr << "Operators size: " << operators.size() << std::endl;
        throw std::logic_error("Number of operators does not match the number of units.");
    }

    // Return the compound unit
    return std::make_shared<CompoundUnit>(units, operators);
}



std::string Measurement::getUnitName() const {
  // Check if the unit is a CompoundUnit
  std::shared_ptr<CompoundUnit> compoundUnit =
      std::dynamic_pointer_cast<CompoundUnit>(unit);
  if (compoundUnit) {
    return Measurement::getCompoundUnitName();
  } else {
    return unit->getName();  // For regular units
  }
}

// Refactored ensureSameType to handle conversions and return converted
// Measurements
std::pair<Measurement, Measurement> Measurement::ensureSameType(
    const Measurement& m) const {
  if (unit->getType() != m.unit->getType()) {
    throw std::invalid_argument(
        "Unit types are not compatible for this operation.");
  }

  Measurement leftBase = UnitConverter::convertToBaseUnit(*this);
  Measurement rightBase = UnitConverter::convertToBaseUnit(m);

  if (leftBase.getUnit()->getName() != rightBase.getUnit()->getName()) {
    throw std::invalid_argument(
        "Post-conversion check failed. Units are not compatible for this "
        "operation.");
  }

  return {leftBase, rightBase};
}

Measurement Measurement::operator+(const Measurement& m) const {
  auto [leftBase, rightBase] = ensureSameType(m);
  return Measurement(leftBase.getMagnitude() + rightBase.getMagnitude(),
                     leftBase.getUnit());
}

Measurement Measurement::operator-(const Measurement& m) const {
  auto [leftBase, rightBase] = ensureSameType(m);
  return Measurement(leftBase.getMagnitude() - rightBase.getMagnitude(),
                     getUnit());
}

Measurement Measurement::operator*(const Measurement& m) const {
  if (unit->getType() == m.unit->getType()) {
    auto [leftBase, rightBase] = ensureSameType(m);

    return Measurement(leftBase.getMagnitude() * rightBase.getMagnitude(),
                       leftBase.getUnit());
  }

  auto compoundUnit = createCompoundUnit(*this, m, '*');
  return Measurement(magnitude * m.magnitude, compoundUnit);
}

Measurement Measurement::operator/(const Measurement& m) const {
  if (m.magnitude == 0) {
    throw std::invalid_argument("Undefined, Cannot divide by zero.");
  }

  if (this->unit->getType() == m.unit->getType()) {
    auto [leftBase, rightBase] = ensureSameType(m);
    return Measurement(leftBase.getMagnitude() / rightBase.getMagnitude(),
                       leftBase.getUnit());
  }

  auto compoundUnit = createCompoundUnit(*this, m, '/');
  return Measurement(this->magnitude / m.magnitude, compoundUnit);
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