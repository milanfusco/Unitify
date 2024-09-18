/**
 * @file UnitConverter.cpp
 * @brief Implementation of the UnitConverter class
*/

#include "UnitConverter.h"

Measurement UnitConverter::convert(const Measurement& m, Units* toUnit) {
    double baseValue = m.getUnit()->toBaseUnit(m.getMagnitude());
    double convertedValue = toUnit->fromBaseUnit(baseValue);
    return Measurement(convertedValue, toUnit);
}

double UnitConverter::getConversionFactor(Units* fromUnit, Units* toUnit) {
    double toBase = fromUnit->toBaseUnit(1.0);
    double fromBase = toUnit->fromBaseUnit(1.0);
    return toBase / fromBase;
}