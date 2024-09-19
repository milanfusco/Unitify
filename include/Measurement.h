/**
 * @file Measurement.h
 * @brief Header file for the Measurement class.
 *
 * The `Measurement` class represents a measurement with a numeric value and a unit.
 * It provides methods to perform arithmetic operations, comparisons, conversions,
 * and to create a Measurement object from a string representation.
 * @version 0.1
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <iostream>
#include <string>
#include <stdexcept> // For std::invalid_argument
#include <sstream>   // For std::stringstream
#include "Units.h"

/**
 * @class Measurement
 * @headerfile Measurement.h
 * @brief Represents a measurement with a numeric value and a unit.
 *
 * The `Measurement` class encapsulates a numeric magnitude and an associated unit.
 * It provides methods to perform arithmetic operations, comparisons, conversions,
 * and to create a Measurement object from a string representation.
 */
class Measurement
{
private:
    double magnitude; ///> The numeric value of the measurement
    Units *unit;      ///> Pointer to Units base class representing the unit

public:
    /**
     * @brief Constructs a new Measurement object.
     *
     * @param magnitude The numeric value of the measurement.
     * @param unit A pointer to a Units object representing the unit of the measurement.
     */
    Measurement(double magnitude, Units *unit); ///> Regular constructor

    /**
     * @brief Copy constructor for the Measurement class.
     *
     * @param other The Measurement object to copy from.
     */
    Measurement(const Measurement &other);

    /**
     * @brief Destructor for the Measurement class.
     */
    ~Measurement();

    /**
     * @brief Retrieves the magnitude of the measurement.
     *
     * @return The numeric value of the measurement.
     */
    double getMagnitude() const;

    /**
     * @brief Retrieves the unit of the measurement.
     *
     * @return A pointer to the Units object representing the unit of the measurement.
     */
    Units *getUnit() const;

    /**
     * @brief Adds two Measurement objects.
     *
     * @param m The Measurement object to add.
     * @return A new Measurement object representing the sum.
     */
    Measurement add(const Measurement &m) const;

    /**
     * @brief Subtracts one Measurement object from another.
     *
     * @param m The Measurement object to subtract.
     * @return A new Measurement object representing the difference.
     */
    Measurement subtract(const Measurement &m) const;

    /**
     * @brief Multiplies two Measurement objects.
     *
     * @param m The Measurement object to multiply.
     * @return A new Measurement object representing the product.
     */
    Measurement multiply(const Measurement &m) const;

    /**
     * @brief Divides one Measurement object by another.
     * @param m The Measurement object to divide by.
     * @return A new Measurement object representing the quotient.
     */
    Measurement divide(const Measurement &m) const;

    /** 
     * @enum ComparisonResult
     * @brief Compares two Measurement objects.
     * @return An integer representing the comparison result:
     *         - Negative if this object is less than `m`.
     *         - Zero if this object is equal to `m`.
     *         - Positive if this object is greater than `m`.
     */
    enum class ComparisonResult
    {
        LESS_THAN = -1,  ///> The first Measurement is less than the second.
        EQUAL = 0,       ///> The two Measurements are equal.
        GREATER_THAN = 1 ///> The first Measurement is greater than the second.
    };

    /**
     * @brief Compares two Measurement objects.
     *
     * @param m The Measurement object to compare against.
     * @return An enum representing the comparison result:
     *         - LESS_THAN if this object is less than `m`.
     *         - EQUAL if this object is equal to `m`.
     *         - GREATER_THAN if this object is greater than `m`.
     */
    ComparisonResult compareTo(const Measurement &m) const;

    /**
     * @brief Creates a Measurement object from a string representation.
     *
     * @param str The string to parse.
     * @return A Measurement object constructed from the parsed string.
     */
    static Measurement fromString(const std::string &str);

    /**
     * @brief Ensures that two Measurement objects have the same unit.
     *
     * @param m The Measurement object to compare against.
     */
    void ensureSameUnit(const Measurement &m) const;

    /**
     * @brief Overloaded assignment operator.
     * @param os The output stream.
     * @param m The Measurement object to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Measurement& m);

    /**
     * @brief Overloaded input operator.
     * @param is The input stream.
     * @param m The Measurement object to read into.
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream& is, Measurement& m);
};
#endif // MEASUREMENT_H