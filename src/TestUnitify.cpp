/**
 * @file TestUnitify.cpp
 * @brief Unit tests for the Unitify library.
 * 
 * This file contains unit tests for the classes and functions in the Unitify library.
 * The tests cover constructors, unit conversions, calculations, validators, and statistics.
 * 
 * @version 0.1
 * 
 */

#include<cassert>
#include<vector>

#include "Measurement.h"
#include "Units.h"
#include "Mass.h"
#include "Length.h"
#include "TimeUnit.h"
#include "Volume.h"
#include "UnitConverter.h"
#include "MeasurementValidator.h"
#include "IOStreamHandler.h"
#include "StatisticsCalculator.h"
#include "ReportGenerator.h"
#include "MeasurementFileProcessor.h"

/**
 * @brief Unit tests for constructors of Measurement class.
 */
void testConstructors() {
    // Define units (unit and conversion factor)
    Length length("m", 1.0);
    Mass mass("g", 1.0);
    Volume volume("L", 1.0);
    TimeUnit time("s", 1.0);

    // Create measurements (magnitude, unit)
    Measurement m1(1.0, &length);
    Measurement m2(2.0, &mass);
    Measurement m3(3.0, &volume);
    Measurement m4(4.0, &time);

    // Test constructors (magnitude)
    assert(m1.getMagnitude() == 1.0);
    assert(m2.getMagnitude() == 2.0);
    assert(m3.getMagnitude() == 3.0);
    assert(m4.getMagnitude() == 4.0);

    // Test constructors (unit)
    assert(m1.getUnit() == &length);
    assert(m2.getUnit() == &mass);
    assert(m3.getUnit() == &volume);
    assert(m4.getUnit() == &time);

    // Test copy constructor
    Measurement m5(m1);
    // Test magnitude
    assert(m5.getMagnitude() == 1.0);
    // Test unit
    assert(m5.getUnit() == &length);
}

/**
 * @brief Unit tests for unit conversions using UnitConverter.
 */
void testUnitConversions() {
    // Test mass conversion (grams to kilograms)
    Mass grams("grams", 1.0);
    Mass kilograms("kilograms", 1000.0);
    Measurement m(500.0, &grams);
    Measurement converted = UnitConverter::convert(m, &kilograms);
    assert(converted.getMagnitude() == 0.5);  // 500 grams = 0.5 kilograms

    // Test length conversion (meters to kilometers)
    Length meters("meters", 1.0);
    Length kilometers("kilometers", 1000.0);
    Measurement mLength(1000.0, &meters);
    Measurement convertedLength = UnitConverter::convert(mLength, &kilometers);
    assert(convertedLength.getMagnitude() == 1.0);  // 1000 meters = 1 kilometer

    // Test time conversion (minutes to seconds)
    TimeUnit minutes("minutes", 60.0);
    TimeUnit seconds("seconds", 1.0);
    Measurement mTime(5.0, &minutes);
    Measurement convertedTime = UnitConverter::convert(mTime, &seconds);
    assert(convertedTime.getMagnitude() == 300.0);  // 5 minutes = 300 seconds

    // Test volume conversion (milliliters to liters)
    Volume milliliters("milliliters", 0.001);
    Volume liters("liters", 1.0);
    Measurement mVolume(1000.0, &milliliters);
    Measurement convertedVolume = UnitConverter::convert(mVolume, &liters);
    assert(convertedVolume.getMagnitude() == 1.0);  // 1000 milliliters = 1 liter
}

/**
 * @brief Unit tests for arithmetic calculations using Measurement class.
 */
void testCalculations() {
    Mass grams("grams", 1.0);
    
    // Test addition
    Measurement m1(50.0, &grams);
    Measurement m2(100.0, &grams);
    Measurement resultAdd = m1.add(m2);
    assert(resultAdd.getMagnitude() == 150.0);  // 50g + 100g = 150g
    
    // Test subtraction
    Measurement resultSub = m2.subtract(m1);
    assert(resultSub.getMagnitude() == 50.0);  // 100g - 50g = 50g
    
    // Test multiplication
    Measurement resultMul = m1.multiply(m2);
    assert(resultMul.getMagnitude() == 5000.0);  // 50g * 100g = 5000g^2 (arbitrary unit for test)
    
    // Test division
    Measurement resultDiv = m2.divide(m1);
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
    Measurement mValid(50.0, &grams);
    assert(MeasurementValidator::validateMeasurement(mValid));
    
    Measurement mInvalid(-50.0, &grams);  // Negative value
    assert(!MeasurementValidator::validateMeasurement(mInvalid));
}

/**
 * @brief Unit tests for statistics calculations using StatisticsCalculator class.
 */
void testStatistics() {
    Mass grams("grams", 1.0);
    
    std::vector<Measurement> measurements = {
        Measurement(10.0, &grams),
        Measurement(20.0, &grams),
        Measurement(20.0, &grams),
        Measurement(30.0, &grams)
    };
    
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