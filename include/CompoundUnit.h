/**
 * @file CompoundUnit.h
 * @brief Compound unit class for representing combined units of measurement.
 * 
 * The CompoundUnit class represents a compound unit formed by multiple units and operators.
 * For example, "g/m/s" is a CompoundUnit with grams, meters, and seconds.
 * The CompoundUnit can perform operations between the units.
 * The CompoundUnit is a subclass of the Units class.
 * @version 0.1
 * 
 */

#ifndef COMPOUNDUNIT_H
#define COMPOUNDUNIT_H

#include <vector>
#include <string>
#include <stdexcept>
#include "Units.h"
#include "Measurement.h"

/// @class CompoundUnit
/// @brief Represents a compound unit formed by multiple units and operators (e.g., "g/m/s").
class CompoundUnit : public Units {
private:
    std::vector<Units*> units;        ///< List of base units (e.g., grams, meters, seconds)
    std::vector<char> operators;      ///< List of operators ('*' or '/')
    Measurement totalMeasurement;     ///< Store the combined measurement (magnitude + unit)

public:
    /**
     * @brief 
     * @param measurement The initial measurement (magnitude + unit).
     *  @param unitName Name for the compound unit.
     */
    explicit CompoundUnit(const Measurement& measurement, const std::string& unitName);

    /**
        * @brief Constructor for multiple units with operators.
        * @param measurements Vector of measurements to combine.
        * @param operatorList Vector of operators ('*' or '/') for combining the measurements.
        * @param unitName Name for the compound unit.
        */
    CompoundUnit(const std::vector<Measurement>& measurements, const std::vector<char>& operatorList, const std::string& unitName);

    /**
     * @brief Method to dynamically add a measurement and operator to the compound unit.
     * @param measurement The measurement to be added.
     * @param op The operator to be applied ('*' or '/').
     */
    void addMeasurement(const Measurement& measurement, char op);

    /**
     * @brief Get the name of the compound unit (e.g., "g/m/s").
     * @return A string representing the compound unit.
     */
    std::string getName() const ;

    /**
     * @brief Get the total magnitude of the compound unit after all operations.
     * @return The resulting magnitude.
     */
    double getMagnitude() const ;

    /**
     * @brief Get the unit of the compound measurement (final result unit).
     * @return Pointer to the unit representing the result.
     */
    Units* getUnit() const ;
};

#endif // COMPOUNDUNIT_H
