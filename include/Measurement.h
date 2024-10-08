/**
 * @file Measurement.h
 * @brief Header file for the Measurement class.
 *
 * The `Measurement` class represents a measurement with a numeric value and a
 * unit. It provides methods to perform arithmetic operations, comparisons,
 * conversions, and to create a Measurement object from a string representation.
 * @version 0.1
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "CompoundUnit.h"
#include "Units.h"

/**
 * @class Measurement
 * @headerfile Measurement.h
 * @brief Represents a measurement with a numeric value and a unit.
 *
 * The `Measurement` class encapsulates a numeric magnitude and an associated
 * unit. It provides methods to perform arithmetic operations, comparisons,
 * conversions, and to create a Measurement object from a string representation.
 */
class Measurement {
 private:
  double magnitude;  ///> The numeric value of the measurement
  std::shared_ptr<Units>
      unit;  ///> Pointer to Units base class representing the unit

 public:
  /**
   * @brief Constructs a new Measurement object.
   *
   * @param magnitude The numeric value of the measurement.
   * @param unit A pointer to a Units object representing the unit of the
   * measurement.
   */
  Measurement(double magnitude,
              std::shared_ptr<Units> unit);  ///> Regular constructor

  /**
   * @brief Constructs a new Measurement object with a unit that is not a shared
   * pointer.
   *
   * @param magnitude The numeric value of the measurement.
   * @param unit A reference to a Units object representing the unit of the
   * measurement.
   */

  /**
   * @brief Constructs a new Measurement object with a compound unit.s
   *
   * @param magnitude The numeric value of the measurement.
   * @param unit A pointer to a CompoundUnit object representing the compound
   * unit of the measurement.
   */
  Measurement(double magnitude,
              std::shared_ptr<CompoundUnit>
                  unit);  ///> Constructor for CompoundUnit measurements

  /**
   * @brief Copy constructor for the Measurement class.
   *
   * @param other The Measurement object to copy from.
   */
  Measurement(const Measurement& other);

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
   * @return A pointer to the Units object representing the unit of the
   * measurement.
   */
  std::shared_ptr<Units> getUnit() const;

  /**
   * @brief Retrieves the compound unit of the measurement.
   *
   * @return A pointer to the CompoundUnit object representing the compound unit
   * of the measurement.
   * @throws std::runtime_error if the unit is not a CompoundUnit.
   */
  std::shared_ptr<CompoundUnit> getCompoundUnit() const;

  /**
   * @brief Retrieves the name of the compound unit.
   *
   * @return The name of the compound unit.
   */
  std::string getCompoundUnitName() const;

  /**
   * @brief Create a Compound Unit object
   * 
   * @param left left side operand
   * @param right right side operand
   * @param op operator
   * @return std::shared_ptr<CompoundUnit>  compound unit
   */
  std::shared_ptr<CompoundUnit> createCompoundUnit(
      const Measurement& left, const Measurement& right, char op) const;

   /**
    * @brief Retrieves the name of the unit or compound unit.
    *
    * @return The name of the unit.
    */
  std::string getUnitName() const;


  /**
   * @brief Ensures that addition or subtraction operations are performed on the
   * same type of measurement.
   *
   * @param m The Measurement object to compare against.
   */
  std::pair<Measurement, Measurement> ensureSameType(const Measurement& m) const;

  /**
   * @brief Overload the addition operator.
   *
   * @param m The Measurement object to add.
   * @return A new Measurement object representing the sum.
   */
  Measurement operator+(const Measurement& m) const;

  /**
   * @brief Overload the subtraction operator.
   *
   * @param m The Measurement object to subtract.
   * @return A new Measurement object representing the difference.
   */
  Measurement operator-(const Measurement& m) const;

  /**
   * @brief Overload the multiplication operator.
   *
   * @param m The Measurement object to multiply with.
   * @return A new Measurement object representing the product.
   */
  Measurement operator*(const Measurement& m) const;

  /**
   * @brief Overload the division operator.
   *
   * @param m The Measurement object to divide by.
   * @return A new Measurement object representing the quotient.
   * @throws std::invalid_argument if division by zero is attempted.
   */
  Measurement operator/(const Measurement& m) const;

  // Comparison Operations

  /**
   * @brief Overload the equality operator.
   *
   * @param m The Measurement object to compare with.
   * @return True if the magnitudes and units are equal, false otherwise.
   */
  bool operator==(const Measurement& m) const;

  /**
   * @brief Overload the inequality operator.
   *
   * @param m The Measurement object to compare with.
   * @return True if the objects are not equal, false otherwise.
   */
  bool operator!=(const Measurement& m) const;

  /**
   * @brief Overload the less than operator.
   *
   * @param m The Measurement object to compare with.
   * @return True if this object is less than the other, false otherwise.
   */
  bool operator<(const Measurement& m) const;

  /**
   * @brief Overload the greater than operator.
   *
   * @param m The Measurement object to compare with.
   * @return True if this object is greater than the other, false otherwise.
   */
  bool operator>(const Measurement& m) const;

  /**
   * @brief Overload the assignment operator.
   *
   * @param m The Measurement object to assign from.
   * @return A reference to the assigned object.
   */
  Measurement operator=(const Measurement& m);

  /**
   * @brief Creates a Measurement object from a string representation.
   *
   * @param str The string to parse.
   * @return A Measurement object constructed from the parsed string.
   */
  static Measurement fromString(const std::string& str);

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
#endif  // MEASUREMENT_H