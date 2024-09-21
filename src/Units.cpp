/**
 * @file Units.cpp
 * @brief This file implements the Units class and its subclasses.
 * 
 * The Units class provides a common interface for different units of measurement.
 * Particular units of measurement are implemented as subclasses of this class.
 * (e.g., Mass, Length, TimeUnit, Volume)
 * @version 0.1
*/

#include "Units.h"
#include "Mass.h"
#include "Length.h"
#include "TimeUnit.h"
#include "Volume.h"
#include <stdexcept>


Units::Units(const std::string& name, double baseUnitFactor) : name(name), baseUnitFactor(baseUnitFactor) {}

Units* Units::getUnitByName(const std::string& unitName) {
    ///> Handling mass units
    if (unitName == "milligrams" || unitName == "mg") {
        return new Mass("g", 0.001);  ///> Convert milligrams to grams
    } else if (unitName == "grams" || unitName == "g") {
        return new Mass("g", 1.0);    ///> Base unit: grams
    } else if (unitName == "kilograms" || unitName == "kg") {
        return new Mass("g", 1000.0); ///> Convert kilograms to grams

    ///> Handling length units
    } else if (unitName == "millimeters" || unitName == "mm") {
        return new Length("m", 0.001);  ///> Convert millimeters to meters
    } else if (unitName == "centimeters" || unitName == "cm") {
        return new Length("m", 0.01);   ///> Convert centimeters to meters
    } else if (unitName == "meters" || unitName == "m") {
        return new Length("m", 1.0);    ///> Base unit: meters
    } else if (unitName == "kilometers" || unitName == "km") {
        return new Length("m", 1000.0); ///> Convert kilometers to meters

    ///> Handling time units
    } else if (unitName == "seconds" || unitName == "s") {
        return new TimeUnit("s", 1.0);      ///> Base unit: seconds
    } else if (unitName == "minutes" || unitName == "min") {
        return new TimeUnit("s", 60.0);     ///> Convert minutes to seconds
    } else if (unitName == "hours" || unitName == "hr") {
        return new TimeUnit("s", 3600.0);   ///> Convert hours to seconds

    ///> Handling volume units
    } else if (unitName == "milliliters" || unitName == "ml") {
        return new Volume("l", 0.001);  ///> Convert milliliters to liters
    } else if (unitName == "centiliters" || unitName == "cl") {
        return new Volume("l", 0.01);   ///> Convert centiliters to liters
    } else if (unitName == "liters" || unitName == "l") {
        return new Volume("l", 1.0);    ///> Base unit: liters
    } else if (unitName == "kiloliters" || unitName == "kl") {
        return new Volume("l", 1000.0); ///> Convert kiloliters to liters

    } else {
        throw std::invalid_argument("Invalid unit type: " + unitName);
    }
}
