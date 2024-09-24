/**
 * @file CompoundUnit.cpp
 * Implementation of the CompoundUnit class.
 * A CompoundUnit is a combination of multiple units with operators.
 * For example, "g/m/s" is a CompoundUnit with grams, meters, and seconds.
 * The CompoundUnit can perform operations between the units.
 * The CompoundUnit is a subclass of the Units class.
 */
#include "CompoundUnit.h"

CompoundUnit::CompoundUnit(std::shared_ptr<Units> unit)
    : Units(unit->getName(), unit->getBaseFactor()) {  //> single unit
  compoundUnitName = unit->getName();
}

CompoundUnit::CompoundUnit(const std::vector<std::shared_ptr<Units>> unitList,
                           const std::vector<char>& operatorList)
    : Units("UnnamedCompoundUnit", 1.0), operators(operatorList) {
  if (unitList.empty()) {
    throw std::invalid_argument("No units provided to build compound unit.");
  }
  units = unitList;
  buildCompoundUnitName();
  Units::setCompoundName(compoundUnitName);
}

void CompoundUnit::buildCompoundUnitName() {
  if (units.empty()) {
    throw std::invalid_argument("No units provided to build name.");
  }
  std::stringstream nameStream;
  nameStream << units[0]->getName();
  for (size_t i = 0; i < operators.size(); i++) {
    nameStream << ' ' << operators[i] << ' ' << units[i + 1]->getName();
  }
  compoundUnitName = nameStream.str();
}

std::string CompoundUnit::getCompoundName() const {
  return compoundUnitName;
}

std::string CompoundUnit::getType() const {
  return "CompoundUnit";
}

std::vector<std::shared_ptr<Units>> CompoundUnit::getUnits() const {
  return units;
}

std::vector<char> CompoundUnit::getOperators() const {
  return operators;
}

std::shared_ptr<Units> CompoundUnit::getBaseUnit() const {
  std::vector<std::shared_ptr<Units>> baseUnits;
  for (auto& unit : units) {
    baseUnits.push_back(std::shared_ptr<Units>(unit->getBaseUnit()));
  }
  return std::make_shared<CompoundUnit>(baseUnits, operators);
}

double CompoundUnit::toBaseUnit(double value) const {
  double result = value;
  for (size_t i = 0; i < operators.size(); ++i) {
    if (operators[i] == '*') {
      result *= units[i + 1]->toBaseUnit(1.0);
    } else if (operators[i] == '/') {
      result /= units[i + 1]->toBaseUnit(1.0);
    }
  }
  return result;
}

double CompoundUnit::fromBaseUnit(double value) const {
  double result = value;
  for (size_t i = 0; i < operators.size(); ++i) {
    if (operators[i] == '*') {
      result *= units[i + 1]->fromBaseUnit(1.0);
    } else if (operators[i] == '/') {
      result /= units[i + 1]->fromBaseUnit(1.0);
    }
  }
  return result;
}
