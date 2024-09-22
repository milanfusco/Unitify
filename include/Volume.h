/**
 * @file Volume.h
 * @brief Declaration of the Volume class for representing volume units.
 * 
 * The Volume class inherits from the Units base class and provides specific 
 * implementations for converting between different volume units and a base unit.
 * 
 * @version 0.1
 */

#ifndef VOLUME_H
#define VOLUME_H

#include "Units.h"

/**
 * @class Volume
 * @brief A class to represent volume units and provide conversion functionality.
 * 
 * The Volume class handles conversion to and from a base unit (liters) for various 
 * volume units such as milliliters, centiliters, liters, and kiloliters.
 */
class Volume : public Units {
public:
    /**
     * @brief Constructs a Volume unit.
     * @param name The name of the volume unit.
     * @param baseUnitFactor The factor to convert the unit to the base unit (liters).
     */
    Volume(const std::string& name, double baseUnitFactor);

    /**
     * @brief Get the type (Volume) of the unit
     * @return Type of the unit (Volume)
     */
    std::string getType() const override;

    /**
     * @brief Get the base unit (liters) of the unit
     * @return Pointer to the base unit (liters)
     */
    std::shared_ptr<Units> getBaseUnit() const override;

    /**
     * @brief Converts a value to the base unit (liters).
     * @param value The value in the current unit.
     * @return The equivalent value in liters.
     */
    double toBaseUnit(double value) const override;

    /**
     * @brief Converts a value from the base unit (liters).
     * @param value The value in liters.
     * @return The equivalent value in the desired unit.
     */
    double fromBaseUnit(double value) const override;
};

#endif // VOLUME_H
