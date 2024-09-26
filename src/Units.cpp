/**
 * @file Units.cpp
 * @brief This file implements the Units class and its subclasses. It also
 * implements CompoundUnit parsing.
 *
 * The Units class provides a common interface for different units of
 * measurement. Particular units of measurement are implemented as subclasses of
 * this class. (e.g., Mass, Length, TimeUnit, Volume) CompoundUnit is a subclass
 * of Units that represents a composition of multiple units with operators. This
 * allows for dimensional analysis and unit conversion in compound units.
 * @version 0.1
 */

#include "Units.h"
#include "CompoundUnit.h"
#include "Length.h"
#include "Mass.h"
#include "TimeUnit.h"
#include "Volume.h"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Units::Units(const std::string& name, double baseUnitFactor)
    : name(name), baseUnitFactor(baseUnitFactor) {}

bool Units::operator==(const std::shared_ptr<Units>& right) const {
  return name == right->name;
}

std::string Units::getName() const {
  return name;
}

std::string Units::setCompoundName(const std::string& name) {
  return name;
}

double Units::getBaseFactor() const {
  return baseUnitFactor;
}

std::shared_ptr<Units> Units::getUnitByName(const std::string& unitName) {
  if (isCompoundUnitName(unitName)) {
    return parseCompoundUnit(unitName);
  }

  ///> Handling mass units
  if (unitName == "micrograms" || unitName == "ug") {
    return std::make_unique<Mass>("g", 1e-6);  ///> Convert micrograms to grams
  } else if (unitName == "milligrams" || unitName == "mg") {
    return std::make_unique<Mass>("g", 0.001);  ///> Convert milligrams to grams
  } else if (unitName == "centigrams" || unitName == "cg") {
    return std::make_unique<Mass>("g", 0.01);  ///> Convert centigrams to grams
  } else if (unitName == "decigrams" || unitName == "dg") {
    return std::make_unique<Mass>("g", 0.1);  ///> Convert decigrams to grams
  } else if (unitName == "grams" || unitName == "g") {
    return std::make_unique<Mass>("g", 1.0);  ///> Base unit: grams
  } else if (unitName == "kilograms" || unitName == "kg") {
    return std::make_unique<Mass>("g", 1000.0);  ///> Convert kilograms to grams

    ///> Handling length units
  } else if (unitName == "micrometers" || unitName == "um") {
    return std::make_unique<Length>("m",
                                    1e-6);  ///> Convert micrometers to meters
  } else if (unitName == "millimeters" || unitName == "mm") {
    return std::make_unique<Length>("m",
                                    0.001);  ///> Convert millimeters to meters
  } else if (unitName == "centimeters" || unitName == "cm") {
    return std::make_unique<Length>("m",
                                    0.01);  ///> Convert centimeters to meters
  } else if (unitName == "decimeters" || unitName == "dm") {
    return std::make_unique<Length>("m",
                                    0.1);  ///> Convert decimeters to meters
  } else if (unitName == "meters" || unitName == "m") {
    return std::make_unique<Length>("m", 1.0);  ///> Base unit: meters
  } else if (unitName == "kilometers" || unitName == "km") {
    return std::make_unique<Length>("m",
                                    1000.0);  ///> Convert kilometers to meters

    ///> Handling time units
  } else if (unitName == "milliseconds" || unitName == "ms") {
    return std::make_unique<TimeUnit>(
        "s",
        0.001);  ///> Convert milliseconds to seconds
  } else if (unitName == "seconds" || unitName == "s") {
    return std::make_unique<TimeUnit>("s", 1.0);  ///> Base unit: seconds
  } else if (unitName == "minutes" || unitName == "min") {
    return std::make_unique<TimeUnit>("s",
                                      60.0);  ///> Convert minutes to seconds
  } else if (unitName == "hours" || unitName == "hr") {
    return std::make_unique<TimeUnit>("s",
                                      3600.0);  ///> Convert hours to seconds

    ///> Handling volume units
  } else if (unitName == "microliters" || unitName == "ul") {
    return std::make_unique<Volume>("l",
                                    1e-6);  ///> Convert microliters to liters
  } else if (unitName == "milliliters" || unitName == "ml") {
    return std::make_unique<Volume>("l",
                                    0.001);  ///> Convert milliliters to liters
  } else if (unitName == "centiliters" || unitName == "cl") {
    return std::make_unique<Volume>("l",
                                    0.01);  ///> Convert centiliters to liters
  } else if (unitName == "deciliters" || unitName == "dl") {
    return std::make_unique<Volume>("l",
                                    0.1);  ///> Convert deciliters to liters
  } else if (unitName == "liters" || unitName == "l") {
    return std::make_unique<Volume>("l", 1.0);  ///> Base unit: liters
  } else if (unitName == "kiloliters" || unitName == "kl") {
    return std::make_unique<Volume>("l",
                                    1000.0);  ///> Convert kiloliters to liters
  } else {
    throw std::invalid_argument("Invalid unit type: " + unitName);
  }
}

bool Units::isCompoundUnitName(const std::string& unitName) {
  return unitName.find_first_of("*/") != std::string::npos;
}

std::shared_ptr<Units> Units::parseCompoundUnit(const std::string& unitName) {
  std::vector<std::shared_ptr<Units>> unitList;
  std::vector<char> operators;
  std::stringstream ss(unitName);
  std::string token;
  char lastOperator = '*';

  while (std::getline(ss, token, ' ')) {
    if (token == "*" || token == "/") {
      operators.push_back(token[0]);
      lastOperator = token[0];
    } else {
      std::shared_ptr<Units> unit = getUnitByName(token);
      if (unit == nullptr) {
        throw std::invalid_argument("Invalid unit type: " + token);
      }
      unitList.push_back(unit);
    }
  }

  return std::make_shared<CompoundUnit>(unitList, operators);
}