/**
 * @file UnitConverter.h
 * @brief Declaration of the UnitConverter class.
 * 
 * The UnitConverter class provides methods to perform conversions between different 
 * units of measurement. It includes functionality to convert a given measurement 
 * to another unit and to compute the conversion factor between two units.
 * 
 * @version 0.1
*/

#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include "Measurement.h"

/**
 * @class UnitConverter
 * @brief A utility class for converting measurements between different units.
 * 
 * The UnitConverter class provides static methods for converting measurements from one 
 * unit to another and calculating the conversion factor between two units.
 */
class UnitConverter {
public:
    /**
     * @brief Converts a measurement to the specified unit.
     * 
     * Converts the given measurement `m` to the specified unit `toUnit`.
     * The result is a new Measurement object representing the converted value.
     * 
     * @param m The measurement to be converted.
     * @param toUnit The target unit to convert the measurement to.
     * @return A new Measurement object in the target unit.
     */
    static Measurement convert(const Measurement& m, Units* toUnit);

    /**
     * @brief Computes the conversion factor between two units.
     * 
     * Computes the conversion factor needed to convert a value from `fromUnit` 
     * to `toUnit`.
     * 
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The conversion factor between the two units.
     */
    static double getConversionFactor(Units* fromUnit, Units* toUnit);
};

#endif // UNITCONVERTER_H