/**
 * @file CompoundUnit.h
 * @brief Compound unit class for representing combined units of measurement.
 *
 * The CompoundUnit class represents a compound unit formed by multiple units
 * and operators. For example, "g/m/s" is a CompoundUnit with grams, meters, and
 * seconds. The CompoundUnit can perform operations between the units. The
 * CompoundUnit is a subclass of the Units class.
 * @version 0.1
 *
 */

#ifndef COMPOUNDUNIT_H
#define COMPOUNDUNIT_H

#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include "Units.h"

class CompoundUnit : public Units {
 private:
  std::vector<std::shared_ptr<Units> >
      units;  ///> List of base units (e.g., grams, meters, seconds)
  std::vector<char> operators;   ///> List of operators ('*' or '/')
  std::string compoundUnitName;  ///> Name of the compound unit

  /**
   * @brief Sanitizes a string by removing null characters.
   *
   * @param input The input string to sanitize.
   * @return The sanitized string.
   */
  std::string sanitizeString(const std::string &input) const;

  /**
   * @brief Builds the name of the compound unit.
   *
   * The name of the compound unit is built by concatenating the names of the
   * base units with the operators between them.
   *
   * For example, if the compound unit is "g/m/s", the name will be "grams /
   * meters / seconds".
   *
   * @return void
   */
  void buildCompoundUnitName();

 public:
  /**
   * @brief CompoundUnit constructor for a single unit.
   *
   * This constructor creates a CompoundUnit with a single unit.
   *
   * @param unit
   */
  CompoundUnit(std::shared_ptr<Units> unit);

  /**
   * @brief CompoundUnit constructor for multiple units with operators.
   *
   * This constructor creates a CompoundUnit with multiple units and operators.
   *
   * @param unitList List of base units.
   * @param operatorList List of operators.
   */
  CompoundUnit(const std::vector< std::shared_ptr<Units> > unitList,
               const std::vector<char>& operatorList);

  /**
   * @brief Get the name of the compound unit.
   *
   * @return The name of the compound unit.
   */
  std::string getCompoundName() const;

  /**
   * @brief Get the type of the compound unit.
   *
   * @return The type of the compound unit.
   */
  std::string getType() const override;

  /**
   * @brief Get the base unit of the compound unit.
   *
   * @return Pointer to the base unit of the compound unit.
   */
  std::shared_ptr<Units> getBaseUnit() const override;

  /**
   * @brief Convert a value to the base unit of the compound unit.
   *
   * @param value The value in the current unit.
   * @return The equivalent value in the base unit.
   */
  double toBaseUnit(double value) const override;

  /**
   * @brief Convert a value from the base unit of the compound unit.
   *
   * @param value The value in the base unit.
   * @return The equivalent value in the desired unit.
   */
  double fromBaseUnit(double value) const override;
};

#endif  // COMPOUNDUNIT_H
