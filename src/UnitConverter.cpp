/**
 * @file UnitConverter.cpp
 * @brief Implementation of the UnitConverter class
 */

#include "UnitConverter.h"
#include "Units.h"
#include "Measurement.h"

Measurement UnitConverter::convertToBaseUnit(const Measurement& measurement) {
  std::shared_ptr<Units> baseUnit = measurement.getUnit()->getBaseUnit();  // Get the base unit
  double baseMagnitude = measurement.getUnit()->toBaseUnit(
      measurement.getMagnitude());  // Convert magnitude to base unit
  return Measurement(baseMagnitude, baseUnit);
}

double UnitConverter::getConversionFactor(Units* fromUnit, Units* toUnit) {
  double toBase = fromUnit->toBaseUnit(1.0);
  double fromBase = toUnit->fromBaseUnit(1.0);
  return toBase / fromBase;
}