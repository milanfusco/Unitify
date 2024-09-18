/**
 * @file MeasurementValidator.h
 * @brief Declaration of the MeasurementValidator class.
 * 
 * The MeasurementValidator class provides static methods for validating 
 * measurements and units. It ensures that the provided measurement data 
 * is consistent, correct, and within the acceptable format or range.
 * 
 * This class plays a key role in input validation to maintain data integrity 
 * throughout the application.
 * 
 * @version 0.1
 */

#ifndef MEASUREMENTVALIDATOR_H
#define MEASUREMENTVALIDATOR_H

#include "Measurement.h"
#include <string>

/**
 * @class MeasurementValidator
 * @brief A utility class for validating measurement data and units.
 * 
 * The MeasurementValidator class provides static methods that validate 
 * measurement objects and their associated unit strings. This helps ensure 
 * that the measurements used within the application conform to expected standards 
 * and prevent errors due to invalid data.
 */
class MeasurementValidator {
public:
    /**
     * @brief Validates a Measurement object.
     * 
     * Checks if the provided Measurement object is valid. Validation may include 
     * checking the magnitude for non-negative values, ensuring the unit is recognized, 
     * and other application-specific validation rules.
     * 
     * @param m A Measurement object to be validated.
     * @return True if the measurement is valid; otherwise, false.
     */
    static bool validateMeasurement(const Measurement& m);

    /**
     * @brief Validates a unit string.
     * 
     * Ensures that the provided unit string corresponds to a valid unit in the system.
     * This method checks if the unit string matches any known or accepted unit names.
     * 
     * @param unitStr A string representing the unit to be validated.
     * @return True if the unit string is valid; otherwise, false.
     */
    static bool validateUnit(const std::string& unitStr);
};

#endif // MEASUREMENTVALIDATOR_H