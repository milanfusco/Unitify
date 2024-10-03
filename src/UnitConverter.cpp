/**
 * @file UnitConverter.cpp
 * @brief Implementation of the UnitConverter class
 */

#include "UnitConverter.h"
#include "Measurement.h"
#include "Units.h"
#include "CompoundUnit.h"
#include "Length.h"
#include "TimeUnit.h"
#include "Mass.h"
#include "Volume.h"

Measurement UnitConverter::convertToBaseUnit(const Measurement& measurement) {
  std::shared_ptr<Units> unit = measurement.getUnit();
  if (unit->isCompound()) {
    return UnitConverter::convertCompoundUnit(
        measurement, std::static_pointer_cast<CompoundUnit>(unit));
  }

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

Measurement UnitConverter::convertCompoundUnit(
    const Measurement& measurement,
    std::shared_ptr<CompoundUnit> compoundUnit) {
  const std::vector<std::shared_ptr<Units>>& units = compoundUnit->getUnits();
  const std::vector<char>& operators = compoundUnit->getOperators();

  std::vector<double> convertedMagnitudes;
  for (const auto& u : units) {
    double convertedMagnitude =
        u->toBaseUnit(1.0);  // Convert magnitude of each unit to base unit
    convertedMagnitudes.push_back(convertedMagnitude);
  }

  double overallMagnitude = convertedMagnitudes[0];
  for (size_t i = 0; i < operators.size(); i++) {
    if (operators[i] == '/') {
      overallMagnitude /= convertedMagnitudes[i + 1];
    } else if (operators[i] == '*') {
      overallMagnitude *= convertedMagnitudes[i + 1];
    }
  }

  double baseMagnitude = measurement.getMagnitude() * overallMagnitude;

  std::vector<std::shared_ptr<Units>> baseUnits;
  for (const auto& u : units) {
    baseUnits.push_back(u->getBaseUnit());
  }

  std::shared_ptr<CompoundUnit> baseCompoundUnit =
      std::make_shared<CompoundUnit>(baseUnits, operators);

  return Measurement(baseMagnitude, baseCompoundUnit);
}

std::shared_ptr<Units> UnitConverter::simplifyUnits(const std::shared_ptr<Units>& leftUnit, 
                                                    const std::shared_ptr<Units>& rightUnit, 
                                                    char op) {
    if (op == '*' && leftUnit->getName() == "m/s" && rightUnit->getName() == "s") {
        // Simplify m/s * s to meters (m)
        return std::make_shared<Length>("m", 1.0);
    }
    if (op == '/' && leftUnit->getName() == "g" && rightUnit->getName() == "L") {
        // Simplify g / L to g/L
        return std::make_shared<CompoundUnit>(std::vector<std::shared_ptr<Units>>{leftUnit, rightUnit}, std::vector<char>{'/'});
    }
    // Return null if no simplification
    return nullptr;
}