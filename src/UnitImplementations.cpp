/**
 * @file UnitImplementations.cpp
 * @brief This file contains the implementation of the Units class and its derived classes.
 * @version 0.1
 */

#include "Mass.h"
#include "Length.h"
#include "Volume.h"
#include "TimeUnit.h"

Mass::Mass(const std::string& name, double baseUnitFactor) : Units(name, baseUnitFactor) {}

double Mass::toBaseUnit(double value) const {
    return value * baseUnitFactor;
}

double Mass::fromBaseUnit(double value) const {
    return value / baseUnitFactor;
}

Length::Length(const std::string& name, double baseUnitFactor) : Units(name, baseUnitFactor) {}

double Length::toBaseUnit(double value) const {
    return value * baseUnitFactor;
}

double Length::fromBaseUnit(double value) const {
    return value / baseUnitFactor;
}

Volume::Volume(const std::string& name, double baseUnitFactor) : Units(name, baseUnitFactor) {}

double Volume::toBaseUnit(double value) const {
    return value * baseUnitFactor;
}

double Volume::fromBaseUnit(double value) const {
    return value / baseUnitFactor;
}

TimeUnit::TimeUnit(const std::string& name, double baseUnitFactor) : Units(name, baseUnitFactor) {}

double TimeUnit::toBaseUnit(double value) const {
    return value * baseUnitFactor;
}

double TimeUnit::fromBaseUnit(double value) const {
    return value / baseUnitFactor;
}
