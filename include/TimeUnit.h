/**
 * @file TimeUnit.h
 * @brief Declaration of the TimeUnit class for representing time units.
 * 
 * The TimeUnit class inherits from the Units base class and provides specific 
 * implementations for converting between different time units and a base unit.
 * 
 * @version 0.1
*/

#ifndef TIMEUNIT_H
#define TIMEUNIT_H

#include <string>
#include "Units.h"

/**
 * @class TimeUnit
 * @brief A class to represent time units and provide conversion functionality.
 * 
 * The TimeUnit class handles conversion to and from a base unit (seconds) for various 
 * time units such as seconds, minutes, and hours.
 */
class TimeUnit : public Units {
public:
    /**
     * @brief Constructs a Time unit.
     * @param name The name of the time unit.
     * @param baseUnitFactor The factor to convert the unit to the base unit (seconds).
     */
    TimeUnit(const std::string& name, double baseUnitFactor);

    /**
     * @brief Converts a value to the base unit (seconds).
     * @param value The value in the current unit.
     * @return The equivalent value in seconds.
     */
    double toBaseUnit(double value) const override;

    /**
     * @brief Converts a value from the base unit (seconds).
     * @param value The value in the seconds.
     * @return The equivalent value in the desired unit.
     */
    double fromBaseUnit(double value) const override;
};

#endif // TIMEUNIT_H