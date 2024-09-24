/**
 * @file UnitConverter.h
 * @brief Declaration of the UnitConverter class.
 *
 * The UnitConverter class provides methods to perform conversions between
 * different units of measurement. It includes functionality to convert a given
 * measurement to another unit and to compute the conversion factor between two
 * units.
 *
 * @version 0.1
 */

#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include "Measurement.h"
#include "Units.h"
/**
 * @class UnitConverter
 * @brief A utility class for converting measurements between different units.
 *
 * The UnitConverter class provides static methods for converting measurements
 * from one unit to another and calculating the conversion factor between two
 * units.
 */
class UnitConverter {
 public:
  /**
   * @brief Converts a measurement to its base unit.
   *
   * Converts a given measurement to its base unit by converting the magnitude
   * to the base unit and returning a new Measurement object with the base unit.
   *
   * @param measurement The measurement to convert.
   * @return A new Measurement object with the base unit.
   */
  static Measurement convertToBaseUnit(const Measurement& measurement);

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
  static double getConversionFactor(std::shared_ptr<Units> fromUnit,
                                    std::shared_ptr<Units> toUnit);

  /**
   * @brief Converts a compound unit measurement to its base unit.
   *
   * Converts a given compound unit measurement to its base unit by converting
   * each unit in the compound unit to its base unit and calculating the overall
   * magnitude based on the operators.
   *
   * @param measurement The compound unit measurement to convert.
   * @param compoundUnit The compound unit to convert.
   * @return A new Measurement object with the base unit.
   */
  static Measurement convertCompoundUnit(
      const Measurement& measurement,
      std::shared_ptr<CompoundUnit> compoundUnit);
};

#endif  // UNITCONVERTER_H