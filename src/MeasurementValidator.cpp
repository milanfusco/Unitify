/**
 * @file MeasurementValidator.cpp
 * @brief Implementation of the MeasurementValidator class
 *
 * This file contains the implementation of the MeasurementValidator class,
 * which provides methods for validating measurement data and units. It ensures
 * that the provided data is consistent, correct, and within the acceptable
 * format or range.
 *
 * @version 0.1
 */

#include "MeasurementValidator.h"
#include <set>

bool MeasurementValidator::validateMeasurement(const Measurement& m) {
  return m.getMagnitude() >= 0;
}

bool MeasurementValidator::validateUnit(const std::string& unitStr) {
  std::set<std::string> validUnits = {"micrometers",
                                      "um"
                                      "millimeters",
                                      "mm",
                                      "centimeters",
                                      "cm",
                                      "decimeters",
                                      "dm",
                                      "meters",
                                      "m",
                                      "kilometers",
                                      "km",
                                      "microliters",
                                      "uL",
                                      "ul",
                                      "milliliters",
                                      "mL",
                                      "ml",
                                      "centiliters",
                                      "cL",
                                      "cl",
                                      "deciliters",
                                      "dL",
                                      "dl",
                                      "liters",
                                      "L",
                                      "l",
                                      "kiloliters",
                                      "kL",
                                      "kl",
                                      "micrograms",
                                      "ug",
                                      "milligrams",
                                      "mg",
                                      "centigrams",
                                      "cg",
                                      "decigrams",
                                      "dg",
                                      "grams",
                                      "g",
                                      "kilograms",
                                      "kg",
                                      "milliseconds",
                                      "ms",
                                      "seconds",
                                      "s",
                                      "minutes",
                                      "min",
                                      "hours",
                                      "hr"};

  return validUnits.find(unitStr) != validUnits.end();
}