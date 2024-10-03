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
  std::cout << "Length | Expected Magnitude: 1.0, Actual: " << m1.getMagnitude()
            << std::endl;
  assert(m1.getMagnitude() == 1.0);
  std::cout << "Mass | Expected Magnitude: 2.0, Actual: " << m2.getMagnitude()
            << std::endl;
  assert(m2.getMagnitude() == 2.0);
  std::cout << "Volume | Expected Magnitude: 3.0, Actual: " << m3.getMagnitude()
            << std::endl;
  assert(m3.getMagnitude() == 3.0);
  std::cout << "Time | Expected Magnitude: 4.0, Actual: " << m4.getMagnitude()
            << std::endl;
  assert(m4.getMagnitude() == 4.0);

  // Test constructors (unit)
  std::cout << "Length | Expected Unit: m, Actual: " << m1.getUnit()->getName()
            << std::endl;
  assert(m1.getUnit()->getName() == length->getName());
  std::cout << "Mass | Expected Unit: g, Actual: " << m2.getUnit()->getName()
            << std::endl;
  assert(m2.getUnit()->getName() == mass->getName());
  std::cout << "Volume | Expected Unit: L, Actual: " << m3.getUnit()->getName()
            << std::endl;
  assert(m3.getUnit()->getName() == volume->getName());
  std::cout << "Time | Expected Unit: s, Actual: " << m4.getUnit()->getName()
            << std::endl;
  assert(m4.getUnit()->getName() == time->getName());

  // Test copy constructor
  Measurement m5(m1);
  std::cout << "Copy Constructor | Expected Magnitude: 1.0, Actual: "
            << m5.getMagnitude() << std::endl;
  assert(m5.getMagnitude() == 1.0);
  std::cout << "Copy Constructor | Expected Unit: m, Actual: "
            << m5.getUnit()->getName() << std::endl;
  assert(m5.getUnit()->getName() == length->getName());

  std::cout << "All constructor tests passed." << std::endl;
}

/**
 * @brief Unit tests for unit conversions using UnitConverter.
 */
void testUnitConversions() {
  std::shared_ptr<Units> kilograms =
      std::make_shared<Mass>("kilograms", 1000.0);
  std::shared_ptr<Units> kilometers =
      std::make_shared<Length>("kilometers", 1000.0);
  std::shared_ptr<Units> seconds = std::make_shared<TimeUnit>("seconds", 1.0);
  // Test mass conversion (kilograms to grams)
  Measurement mMass(0.5, kilograms);  // 0.5 kg
  Measurement convertedMass = UnitConverter::convertToBaseUnit(mMass);
  std::cout << "(0.5 kg -> g) | Expected: 500.0, Actual: "
            << convertedMass.getMagnitude() << std::endl;
  assert(convertedMass.getMagnitude() == 500.0);  // 0.5 kilograms = 500 grams

  // Test length conversion (kilometers to meters)
  Measurement mLength(1.0, kilometers);  // 1 km
  Measurement convertedLength = UnitConverter::convertToBaseUnit(mLength);
  std::cout << "(1 km -> m) | Expected: 1000.0, Actual: "
            << convertedLength.getMagnitude() << std::endl;
  assert(convertedLength.getMagnitude() ==
         1000.0);  // 1 kilometer = 1000 meters

  // Test compound unit conversion (m/s to base unit m/s)
  std::vector<std::shared_ptr<Units>> units = {kilometers, seconds};
  std::vector<char> operators = {'/'};
  auto velocityPtr = std::make_shared<CompoundUnit>(units, operators);

  Measurement velocityMeasurement(10.0, velocityPtr);  // 10 km/s
  Measurement convertedVelocity =
      UnitConverter::convertToBaseUnit(velocityMeasurement);
  std::cout << "(10 km/s -> m/s) | Expected: 10000.0, Actual: "
            << convertedVelocity.getMagnitude() << std::endl;
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
  std::cout << "(+) | Expected: 150.0, Actual: " << resultAdd.getMagnitude()
            << std::endl;
  assert(resultAdd.getMagnitude() == 150.0);  // 50g + 100g = 150g

  // Test subtraction
  Measurement resultSub = m2 - m1;
  std::cout << "(-) | Expected: 50.0, Actual: " << resultSub.getMagnitude()
            << std::endl;
  assert(resultSub.getMagnitude() == 50.0);  // 100g - 50g = 50g

  // Test multiplication
  Measurement resultMul = m1 * m2;
  std::cout << "(*) | Expected: 5000.0, Actual: " << resultMul.getMagnitude()
            << std::endl;
  assert(resultMul.getMagnitude() ==
         5000.0);  // 50g * 100g = 5000g^2 (arbitrary unit for test)

  // Test division
  Measurement resultDiv = m2 / m1;
  std::cout << "(/) | Expected: 2.0, Actual: " << resultDiv.getMagnitude()
            << std::endl;
  assert(resultDiv.getMagnitude() == 2.0);  // 100g / 50g = 2

  std::cout << "All arithmetic calculation tests passed." << std::endl;
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
  std::cout << "Validating grams | expected: 1, Actual: "
            << MeasurementValidator::validateMeasurement(mValid) << std::endl;
  assert(MeasurementValidator::validateMeasurement(mValid));

  auto gramsPtrInvalid = std::make_shared<Mass>(grams);
  Measurement mInvalid(-50.0, gramsPtrInvalid);  // Negative value
  std::cout << "Validating -grams | expected: 0, Actual: "
            << MeasurementValidator::validateMeasurement(mInvalid) << std::endl;
  assert(!MeasurementValidator::validateMeasurement(mInvalid));

  std::cout << "All validation tests passed." << std::endl;
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
  std::cout << "Expected mean: 20.0, Actual mean: " << mean << std::endl;
  assert(mean == 20.0);  // Mean of 10, 20, 20, 30 is 20.0

  // Test mode calculation
  double mode = StatisticsCalculator::computeMode(measurements);
  std::cout << "Expected mode: 20.0, Actual mode: " << mode << std::endl;
  assert(mode == 20.0);  // Mode is 20.0

  // Test median calculation
  double median = StatisticsCalculator::computeMedian(measurements);
  std::cout << "Expected median: 20.0, Actual median: " << median << std::endl;
  assert(median == 20.0);  // Median is 20.0

  std::cout << "All statistics tests passed." << std::endl;
}


/**
 * @brief Main function to run all unit tests.
 * 
 * The main function runs all unit tests for the Unitify library. The tests cover
 * constructors, unit conversions, calculations, validators, and statistics.
 * 
 * @note Compound units are tested in TestCompoundUnits.cpp.
 * @return 0 if all tests pass, 1 otherwise.
 */
int main() {
  // Test constructors
  testConstructors();

  // Test unit conversions
  testUnitConversions();

  // Test calculations
  testCalculations();

  // Test validators
  testValidators();

  // Test statistics
  testStatistics();

  std::cout << "All tests passed successfully." << std::endl;

  return 0;
}
