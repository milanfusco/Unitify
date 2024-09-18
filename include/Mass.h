/**
 * @file Mass.h
 * @brief Declaration of the Mass class for representing mass units.
 * 
 * The Mass class inherits from the Units base class and provides specific 
 * implementations for converting between different mass units and a base unit.
 * 
 * @version 0.1
*/

#ifndef MASS_H
#define MASS_H

#include "Units.h"

/**
 * @class Mass
 * @brief A class to represent mass units and provide conversion functionality.
 * 
 * The Mass class handles conversion to and from a base unit (grams) for various 
 * mass units such as milligrams, grams, and kilograms.
 */
class Mass : public Units {
public:
    /**
     * @brief Constructs a Mass unit.
     * @param name The name of the mass unit.
     * @param baseUnitFactor The factor to convert the unit to the base unit (grams).
     */
    Mass(const std::string& name, double baseUnitFactor);

    /**
     * @brief Converts a value to the base unit (grams).
     * @param value The value in the current unit.
     * @return The equivalent value in grams.
     */
    double toBaseUnit(double value) const override;

    /**
     * @brief Converts a value from the base unit (grams).
     * @param value The value in grams.
     * @return The equivalent value in the desired unit.
     */
    double fromBaseUnit(double value) const override;
};

#endif // MASS_H