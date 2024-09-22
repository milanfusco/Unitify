/**
 * @file UnitImplementations.cpp
 * @brief This file contains the implementation of the Units class and its
 * derived classes.
 * @version 0.1
 */

#include "CompoundUnit.h"
#include "Length.h"
#include "Mass.h"
#include "TimeUnit.h"
#include "Volume.h"

Mass::Mass(const std::string& name, double baseUnitFactor)
    : Units(name, baseUnitFactor) {}

double Mass::toBaseUnit(double value) const {
  return value * baseUnitFactor;
}

double Mass::fromBaseUnit(double value) const {
  return value / baseUnitFactor;
}

std::string Mass::getType() const {
  return "Mass";
}

std::shared_ptr<Units> Mass::getBaseUnit() const {
  return std::make_shared<Mass>("g", 1.0);
}

Length::Length(const std::string& name, double baseUnitFactor)
    : Units(name, baseUnitFactor) {}

double Length::toBaseUnit(double value) const {
  return value * baseUnitFactor;
}

double Length::fromBaseUnit(double value) const {
  return value / baseUnitFactor;
}

std::string Length::getType() const {
  return "Length";
}

std::shared_ptr<Units> Length::getBaseUnit() const {
  return std::make_shared<Length>("m", 1.0);
}

Volume::Volume(const std::string& name, double baseUnitFactor)
    : Units(name, baseUnitFactor) {}

double Volume::toBaseUnit(double value) const {
  return value * baseUnitFactor;
}

double Volume::fromBaseUnit(double value) const {
  return value / baseUnitFactor;
}

std::string Volume::getType() const {
  return "Volume";
}

std::shared_ptr<Units> Volume::getBaseUnit() const {
  return std::make_shared<Volume>("l", 1.0);
}

TimeUnit::TimeUnit(const std::string& name, double baseUnitFactor)
    : Units(name, baseUnitFactor) {}

double TimeUnit::toBaseUnit(double value) const {
  return value * baseUnitFactor;
}

double TimeUnit::fromBaseUnit(double value) const {
  return value / baseUnitFactor;
}

std::string TimeUnit::getType() const {
  return "TimeUnit";
}

std::shared_ptr<Units> TimeUnit::getBaseUnit() const {
  return std::make_shared<TimeUnit>("s", 1.0);
}