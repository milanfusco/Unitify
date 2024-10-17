/**
 * @file Units.h
 * @brief This file declares the Units class and its subclasses.
 *
 * The Units class provides a common interface for different units of
 * measurement. Particular units of measurement are implemented as subclasses of
 * this class. (e.g., Mass, Length, TimeUnit, Volume)
 *
 * @version 0.1
 */

#ifndef UNITS_H
#define UNITS_H

#include <memory>
#include <string>

/**
 * @class Units
 * @brief Abstract class to represent different units of measurement
 *
 * The 'Units' class provides a common interface for different units of
 * measurement. Particular units of measurement are implemented as subclasses of
 * this class. (e.g., Mass, Length, TimeUnit, Volume)
 */
class Units {
 protected:
  std::string name;       ///< Name of the unit
  double baseUnitFactor;  ///< Factor to convert the unit to the base unit

 public:
  /**
   * @brief Constructor for the Units class.
   *
   * Initializes a unit with a specified name and base unit conversion factor.
   *
   * @param name The name of the unit (e.g., "grams", "meters").
   * @param baseUnitFactor The conversion factor to the base unit (e.g., grams
   * to base unit grams = 1.0).
   */
  Units(const std::string& name, double baseUnitFactor);

  virtual ~Units() = default;  ///< Virtual destructor

  /**
   * @brief Equality operator for comparing units.
   *
   * This operator checks if two units are equal based on their names.
   *
   * @param right The right-hand side unit to compare.
   * @return True if the units are equal, false otherwise.
   */
  bool operator==(const std::shared_ptr<Units>& right) const;

  /**
   * @brief Get the name of the unit
   * @return Name of the unit
   */
  std::string getName() const;

  double getBaseFactor() const;

  /**
   * @brief Get the type of the unit
   * @return Type of the unit
   */
  virtual std::string getType() const = 0;

  /**
   * @brief Get the base unit of the unit
   * @return Pointer to the base unit
   */
  virtual std::shared_ptr<Units> getBaseUnit() const = 0;

  /**
   * @brief Convert the value to the base unit
   * @param value Value to convert
   * @return Converted value in the base unit
   */
  virtual double toBaseUnit(double value) const = 0;  // Convert to base unit

  /**
   * @brief Convert the value from the base unit
   * @param value Value to convert
   * @return Converted value from the base unit
   */
  virtual double fromBaseUnit(
      double value) const = 0;  // Convert from base unit

  /**
   * @brief Retrieves a unit object by its name.
   *
   * This static method maps a unit name to its corresponding class instance
   * (e.g., "grams" to a Mass object, "meters" to a Length object).
   *
   * @param unitName The name of the unit (e.g., "grams", "m", "s").
   * @return A dynamically allocated pointer to the corresponding Units object.
   * @throws std::invalid_argument If the unit name is not recognized.
   */
  static std::shared_ptr<Units> getUnitByName(const std::string& unitName);
};

#endif  // UNITS_H