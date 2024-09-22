/**
 * @file TestUnitify.cpp
 * @brief Unit tests for the Unitify library.
 *
 * This file contains unit tests for the classes and functions in the Unitify
 * library. The tests cover constructors, unit conversions, calculations,
 * validators, and statistics.
 *
 * @version 0.1
 *
 */

#include <cassert>
#include <iostream>
#include <vector>

#include "CompoundUnit.h"
#include "IOStreamHandler.h"
#include "Length.h"
#include "Mass.h"
#include "Measurement.h"
#include "MeasurementFileProcessor.h"
#include "MeasurementValidator.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"
#include "TimeUnit.h"
#include "UnitConverter.h"
#include "Units.h"
#include "Volume.h"

/**
 * @brief Unit tests for constructors of Measurement class.
 */
void testConstructors() {
  // Create measurements (magnitude, unit)
  std::shared_ptr<Units> length = std::make_shared<Length>("m", 1.0);
  std::shared_ptr<Units> mass = std::make_shared<Mass>("g", 1.0);
  std::shared_ptr<Units> volume = std::make_shared<Volume>("L", 1.0);
  std::shared_ptr<Units> time = std::make_shared<TimeUnit>("s", 1.0);

  Measurement m1(1.0, length);
  Measurement m2(2.0, mass);
  Measurement m3(3.0, volume);
  Measurement m4(4.0, time);

  // Test constructors (magnitude)
  assert(m1.getMagnitude() == 1.0);
  assert(m2.getMagnitude() == 2.0);
  assert(m3.getMagnitude() == 3.0);
  assert(m4.getMagnitude() == 4.0);

  // Test constructors (unit)
  assert(m1.getUnit()->getName() == length->getName());
  assert(m2.getUnit()->getName() == mass->getName());
  assert(m3.getUnit()->getName() == volume->getName());
  assert(m4.getUnit()->getName() == time->getName());

  // Test copy constructor
  Measurement m5(m1);
  assert(m5.getMagnitude() == 1.0);
  assert(m5.getUnit()->getName() == length->getName());
}

/**
 * @brief Unit tests for compound units.
 */
void testCompoundUnits() {
  // Define simple units
  Length meters("m", 1.0);
  TimeUnit seconds("s", 1.0);

  // Create compound units (e.g., m/s)
  std::vector<std::shared_ptr<Units>> units = {
      std::make_shared<Length>(meters), std::make_shared<TimeUnit>(seconds)};
  std::vector<char> operators = {'/'};
  CompoundUnit velocity(units, operators);

  assert(!units.empty());

  // Test compound unit name
  assert(velocity.getCompoundName() == "m / s");

  // Test measurements using compound units
  auto velocityPtr = std::make_shared<CompoundUnit>(velocity);
  Measurement velocityMeasurement(10.0, velocityPtr);
  assert(velocityMeasurement.getMagnitude() == 10.0);
  std::string unitName = velocityMeasurement.getCompoundUnitName();

  std::cout << "Expected: m / s, Actual: " << unitName << std::endl;
  assert(unitName == "m / s");
}

/**
 * @brief Unit tests for unit conversions using UnitConverter.
 */
void testUnitConversions() {
  // Test mass conversion (kilograms to grams)
  auto kilogramsPtr = std::make_shared<Mass>("kilograms", 1000.0);
  Measurement mMass(0.5, kilogramsPtr);  // 0.5 kg
  Measurement convertedMass = UnitConverter::convertToBaseUnit(mMass);
  assert(convertedMass.getMagnitude() == 500.0);  // 0.5 kilograms = 500 grams

  // Test length conversion (kilometers to meters)
  auto kilometersPtr = std::make_shared<Length>("kilometers", 1000.0);
  Measurement mLength(1.0, kilometersPtr);  // 1 km
  Measurement convertedLength = UnitConverter::convertToBaseUnit(mLength);
  assert(convertedLength.getMagnitude() ==
         1000.0);  // 1 kilometer = 1000 meters

  // Test compound unit conversion (m/s to base unit m/s)
  auto secondsPtr = std::make_shared<TimeUnit>("s", 1.0);
  std::vector<std::shared_ptr<Units>> units = {kilometersPtr, secondsPtr};
  std::vector<char> operators = {'/'};
  auto velocityPtr = std::make_shared<CompoundUnit>(units, operators);

  Measurement velocityMeasurement(10.0, velocityPtr);  // 10 km/s
  Measurement convertedVelocity =
      UnitConverter::convertToBaseUnit(velocityMeasurement);
  assert(convertedVelocity.getMagnitude() == 10000.0);  // 10 km/s = 10000 m/s

  std::cout << "All unit conversion tests passed." << std::endl;
}

/**
 * @brief Unit tests for arithmetic calculations using Measurement class.
 */
void testCalculations() {
  Mass grams("grams", 1.0);

  // Test addition
  auto gramsPtr = std::make_shared<Mass>(grams);
  Measurement m1(50.0, gramsPtr);
  auto gramsPtr2 = std::make_shared<Mass>(grams);
  Measurement m2(100.0, gramsPtr2);
  Measurement resultAdd = m1 + m2;
  assert(resultAdd.getMagnitude() == 150.0);  // 50g + 100g = 150g

  // Test subtraction
  Measurement resultSub = m2 - m1;
  assert(resultSub.getMagnitude() == 50.0);  // 100g - 50g = 50g

  // Test multiplication
  Measurement resultMul = m1 * m2;
  assert(resultMul.getMagnitude() ==
         5000.0);  // 50g * 100g = 5000g^2 (arbitrary unit for test)

  // Test division
  Measurement resultDiv = m2 / m1;
  assert(resultDiv.getMagnitude() == 2.0);  // 100g / 50g = 2
}

/**
 * @brief Unit tests for validators in MeasurementValidator class.
 */
void testValidators() {
  // Test unit validation
  assert(MeasurementValidator::validateUnit("grams"));
  assert(MeasurementValidator::validateUnit("meters"));
  assert(!MeasurementValidator::validateUnit("invalidUnit"));

  // Test measurement validation
  Mass grams("grams", 1.0);
  auto gramsPtr = std::make_shared<Mass>(grams);
  Measurement mValid(50.0, gramsPtr);
  assert(MeasurementValidator::validateMeasurement(mValid));

  auto gramsPtrInvalid = std::make_shared<Mass>(grams);
  Measurement mInvalid(-50.0, gramsPtrInvalid);  // Negative value
  assert(!MeasurementValidator::validateMeasurement(mInvalid));
}

/**
 * @brief Unit tests for statistics calculations using StatisticsCalculator
 * class.
 */
void testStatistics() {
  Mass grams("grams", 1.0);

  std::vector<Measurement> measurements = {
      Measurement(10.0, std::make_shared<Mass>(grams)),
      Measurement(20.0, std::make_shared<Mass>(grams)),
      Measurement(20.0, std::make_shared<Mass>(grams)),
      Measurement(30.0, std::make_shared<Mass>(grams))};

  // Test mean calculation
  double mean = StatisticsCalculator::computeMean(measurements);
  assert(mean == 20.0);  // Mean of 10, 20, 20, 30 is 20.0

  // Test mode calculation
  double mode = StatisticsCalculator::computeMode(measurements);
  assert(mode == 20.0);  // Mode is 20.0

  // Test median calculation
  double median = StatisticsCalculator::computeMedian(measurements);
  assert(median == 20.0);  // Median is 20.0
}

int main() {
  // Test constructors
  testConstructors();

  // Test compound units
  testCompoundUnits();

  // Test unit conversions
  testUnitConversions();

  // Test calculations
  testCalculations();

  // Test validators
  testValidators();

  // Test statistics
  testStatistics();

  return 0;
}
