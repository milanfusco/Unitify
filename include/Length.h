/**
 * @file Length.h
 * @brief Declaration of the Length class for representing length units.
 * 
 * The Length class inherits from the Units base class and provides specific 
 * implementations for converting between different length units and a base unit.
 * 
 * @version 0.1
*/

#ifndef LENGTH_H
#define LENGTH_H

#include "Units.h"

/**
 * @class Length
 * @brief A class to represent length units and provide conversion functionality.
 * 
 * The Length class handles conversion to and from a base unit (meters) for various 
 * length units such as millimeters, centimeters, meters, and kilometers.
 */
class Length : public Units {
public:
    /**
     * @brief Constructs a Length unit.
     * @param name The name of the length unit.
     * @param baseUnitFactor The factor to convert the unit to the base unit (meters).
     */
    Length(const std::string& name, double baseUnitFactor);

    /**
     * @brief Converts a value to the base unit (meters).
     * @param value The value in the current unit.
     * @return The equivalent value in meters.
     */
    double toBaseUnit(double value) const override;

    /**
     * @brief Converts a value from the base unit (meters).
     * @param value The value in meters.
     * @return The equivalent value in the deisred unit.
     */
    double fromBaseUnit(double value) const override;
};

#endif // LENGTH_H