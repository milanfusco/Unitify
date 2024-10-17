/**
 * @file UnitConverter.cpp
 * @brief Implementation of the UnitConverter class
 */

#include "UnitConverter.h"
#include "Length.h"
#include "Mass.h"
#include "Measurement.h"
#include "TimeUnit.h"
#include "Units.h"
#include "Volume.h"

Measurement UnitConverter::convertToBaseUnit(const Measurement& measurement) {
  std::shared_ptr<Units> baseUnit = measurement.getUnit()->getBaseUnit();
  double baseMagnitude =
      measurement.getUnit()->toBaseUnit(measurement.getMagnitude());
  return Measurement(baseMagnitude, baseUnit);
}

double UnitConverter::getConversionFactor(std::shared_ptr<Units> fromUnit,
                                          std::shared_ptr<Units> toUnit) {
  double toBase = fromUnit->toBaseUnit(1.0);
  double fromBase = toUnit->fromBaseUnit(1.0);
  return toBase / fromBase;
}