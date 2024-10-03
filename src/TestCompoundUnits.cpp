/**
 * @file TestCompoundUnits
 * @brief Unit tests for compound units and operations.
 * 
 * This file contains unit tests for compound units and arithmetic operations
 * involving compound units. It includes tests for creating compound units,
 * performing arithmetic operations with compound units, and handling errors
 * related to compound units.
 * 
 * @version 0.1
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
 * @brief Simple unit test for compound unit creation.
 * 
 * Tests for the creation of compound units with multiple base units and operators.
 */
void SimpleCompoundUnitTest() {
  // Define simple units
  Length meters("m", 1.0);
  TimeUnit seconds("s", 1.0);

  // Create compound units (e.g., m/s)
  std::vector<std::shared_ptr<Units>> units = {
      std::make_shared<Length>(meters), std::make_shared<TimeUnit>(seconds)};
  std::vector<char> operators = {'/'};
  CompoundUnit velocity(units, operators);

  std::cout << "Units in compound unit | Expected: 2, Actual: " << units.size()
            << std::endl;
  assert(!units.empty());

  // Test measurements using compound units
  auto velocityPtr = std::make_shared<CompoundUnit>(velocity);
  Measurement velocityMeasurement(10.0, velocityPtr);
  assert(velocityMeasurement.getMagnitude() == 10.0);
  std::string unitName = velocityMeasurement.getCompoundUnitName();

  std::cout << "Expected: m / s, Actual: " << unitName << std::endl;
  assert(unitName == "m / s");

}

/**
 * @brief Unit tests for compound unit operations.
 * 
 * Tests for arithmetic operations with compound units, such as division of mass
 * by volume to calculate density.
 */
void testCompoundUnitOperations() {
  // Test division of mass by volume (g / L)
  Mass grams("g", 1.0);
  Volume liters("L", 1.0);
  Measurement massMeasurement(100.0, std::make_shared<Mass>(grams));  // 100 g
  Measurement volumeMeasurement(2.0, std::make_shared<Volume>(liters));  // 2 L

  auto densityMeasurement = massMeasurement / volumeMeasurement;
  std::cout << "(100 g / 2 L) | Expected: 50 g/L, Actual: "
            << densityMeasurement.getMagnitude() << " "
            << densityMeasurement.getUnitName() << std::endl;
  assert(densityMeasurement.getMagnitude() == 50.0);
  assert(densityMeasurement.getUnitName() == "g / L");

  std::cout << "All compound unit operation tests passed." << std::endl;
}

/**
 * @brief Expanded unit conversion tests with compound units.
 * 
 * Tests for unit conversion with compound units that require conversion to base
 * units before performing arithmetic operations.
 */
void testExpandedUnitConversions() {
  std::shared_ptr<Units> kilometers =
      std::make_shared<Length>("kilometers", 1000.0);
  std::shared_ptr<Units> hours = std::make_shared<TimeUnit>("hours", 3600.0);
  std::shared_ptr<Units> meters = std::make_shared<Length>("meters", 1.0);
  std::shared_ptr<Units> seconds = std::make_shared<TimeUnit>("seconds", 1.0);

  // Test velocity conversion: kilometers per hour to meters per second
  std::vector<std::shared_ptr<Units>> velocityUnits = {kilometers, hours};
  std::vector<char> operators = {'/'};
  auto velocity = std::make_shared<CompoundUnit>(velocityUnits, operators);

  Measurement velocityMeasurement(72.0, velocity);  // 72 km/h
  Measurement convertedVelocity =
      UnitConverter::convertToBaseUnit(velocityMeasurement);
  std::cout << "(72 km/h -> m/s) | Expected: 20.0, Actual: "
            << convertedVelocity.getMagnitude() << std::endl;
  assert(convertedVelocity.getMagnitude() == 20.0);  // 72 km/h = 20 m/s

  ///> Test incompatible unit conversion (expect failure)
  try {
    Measurement mass(10.0, std::make_shared<Mass>("grams", 1.0));
    Measurement incompatibleConversion = UnitConverter::convertToBaseUnit(mass);
    std::cerr << "Expected exception for incompatible conversion not thrown.\n";
  } catch (const std::invalid_argument& e) {
    std::cout << "Incompatible conversion test passed: " << e.what()
              << std::endl;
  }

  std::cout << "All expanded unit conversion tests passed." << std::endl;
}

/**
 * @brief Unit tests for mixed unit operations and compatibility checks.
 * 
 * Tests for arithmetic operations with mixed units that may or may not be
 * compatible.
 */
void testMixedUnitOperations() {
  // Define simple units
  Length meters("m", 1.0);
  TimeUnit seconds("s", 1.0);
  Mass grams("g", 1.0);

  ///> Test incompatible addition (expect exception)
  try {
    Measurement m1(10.0, std::make_shared<Length>(meters));
    Measurement m2(5.0, std::make_shared<Mass>(grams));  // Incompatible units
    Measurement result = m1 + m2;  // Should throw an exception
    std::cerr << "Expected exception for incompatible addition not thrown.\n";
  } catch (const std::invalid_argument& e) {
    std::cout << "Incompatible unit addition test passed: " << e.what()
              << std::endl;
  }

  std::cout << "All mixed unit operation tests passed." << std::endl;
}

/**
 * @brief Unit tests for arithmetic operations involving unit conversion.
 * 
 * Tests for arithmetic operations with mixed units that require conversion.
 */
void testArithmeticWithConversion() {
  Length kilometers("kilometers", 1000.0);
  Length meters("meters", 1.0);

  // Test multiplication of kilometers and meters (convert to base units)
  Measurement km(1.0, std::make_shared<Length>(kilometers));  // 1 km
  Measurement m(500.0, std::make_shared<Length>(meters));     // 500 meters

  Measurement totalDistance = km + m;  // Should be 1500 meters (1.5 km)
  std::cout << "(1 km + 500 m) | Expected: 1500 meters, Actual: "
            << totalDistance.getMagnitude() << " "
            << totalDistance.getUnit()->getName() << std::endl;
  assert(totalDistance.getMagnitude() == 1500.0);  // After conversion to meters

  std::cout << "All arithmetic with conversion tests passed." << std::endl;
}

/**
 * @brief Unit tests for error handling in compound unit creation
 * 
 * Tests for invalid compound unit creation with mismatched operators.
 */
void testCompoundUnitErrors() {
  // Test invalid compound unit creation (mismatched operators)
  try {
    Length meters("m", 1.0);
    TimeUnit seconds("s", 1.0);
    std::vector<std::shared_ptr<Units>> units = {
        std::make_shared<Length>(meters)};
    std::vector<char> operators = {'/'};

    CompoundUnit invalidCompound(units, operators);  // Should throw error
    std::cerr << "Expected exception for invalid compound unit not thrown.\n";
  } catch (const std::logic_error& e) {
    std::cout << "Invalid compound unit creation test passed: " << e.what()
              << std::endl;
  }
}

/**
 * @brief Main function to run unit tests for compound units and operations.
 * 
 * @return 0 if all tests pass
 */
int main() {
  SimpleCompoundUnitTest();

  testCompoundUnitOperations();

  testExpandedUnitConversions();

  testMixedUnitOperations();

  testArithmeticWithConversion();

  testCompoundUnitErrors();

  std::cout << "All unit tests passed." << std::endl;
  return 0;
}