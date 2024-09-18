/**
 * @file MeasurementValidator.cpp
 * @brief Implementation of the MeasurementValidator class
 * 
 * This file contains the implementation of the MeasurementValidator class, which provides
 * methods for validating measurement data and units. It ensures that the provided data is
 * consistent, correct, and within the acceptable format or range.
 * 
 * @version 0.1
 */

#include "MeasurementValidator.h"
#include <set>

bool MeasurementValidator::validateMeasurement(const Measurement& m) {
    return m.getMagnitude() >= 0; // Ensure magnitude is non-negative
}

bool MeasurementValidator::validateUnit(const std::string& unitStr) {
    std::set<std::string> validUnits = {"millimeters", "centimeters", "meters", "kilometers",
                                        "milliliters", "centiliters", "liters", "kiloliters",
                                        "milligrams", "centigrams", "grams", "kilograms",
                                        "seconds", "minutes", "hours"};
    return validUnits.find(unitStr) != validUnits.end();
}