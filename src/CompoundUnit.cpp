/**
 * @file CompoundUnit.cpp
 * @brief Implementation of the CompoundUnit class.
 * A CompoundUnit is a combination of multiple units with operators.
 * For example, "g/m/s" is a CompoundUnit with grams, meters, and seconds.
 * The CompoundUnit can perform operations between the units.
 * The CompoundUnit is a subclass of the Units class.
 */
#include "CompoundUnit.h"
#include "Measurement.h"
#include "Units.h"
#include <stdexcept>
#include <string>
#include <vector>

class CompoundUnit : public Units {
private:
    std::vector<Units*> units;        // List of base units (e.g., grams, meters, seconds)
    std::vector<char> operators;      // List of operators ('*' or '/')
    Measurement totalMeasurement;     // Store the combined measurement (magnitude + unit)

public:
    // Constructor for a single unit
    CompoundUnit::CompoundUnit(const Measurement& measurement, const std::string& unitName)
        : totalMeasurement(measurement),  // Initialize totalMeasurement
        Units(unitName, 1)  // Call Units constructor
    {
    }

    // Constructor for multiple units with operators
    CompoundUnit::CompoundUnit(const std::vector<Measurement>& measurements, const std::vector<char>& operatorList, const std::string& unitName)
        : Units(unitName, 1),  // Call Units constructor
        operators(operatorList) {
        if (measurements.size() != operatorList.size() + 1) {
            throw std::invalid_argument("Mismatch between units and operators.");
        }
        totalMeasurement = measurements[0];  // Initialize with the first measurement
        units.push_back(measurements[0].getUnit());

        // Perform the operations between the measurements
        for (size_t i = 0; i < operatorList.size(); ++i) {
            if (operatorList[i] == '*') {
                totalMeasurement = totalMeasurement * measurements[i + 1];
            } else if (operatorList[i] == '/') {
                totalMeasurement = totalMeasurement / measurements[i + 1];
            }
            units.push_back(measurements[i + 1].getUnit());
        }
    }

    // Method to add a measurement dynamically
    void addMeasurement(const Measurement& measurement, char op) {
        units.push_back(measurement.getUnit());
        operators.push_back(op);
        if (op == '*') {
            totalMeasurement = totalMeasurement * measurement;
        } else if (op == '/') {
            totalMeasurement = totalMeasurement / measurement;
        }
    }

    // Get the name of the compound unit (e.g., "g/m/s")
    std::string getName() const {
        std::string name = units[0]->getName();  // Start with the first unit
        for (size_t i = 0; i < operators.size(); ++i) {
            name += " " + std::string(1, operators[i]) + " " + units[i + 1]->getName();
        }
        return name;
    }

    // Get the total magnitude after all operations
    double getMagnitude() const  {
        return totalMeasurement.getMagnitude();  // Return the combined magnitude
    }

    Units* getUnit() const  {
        return totalMeasurement.getUnit();  // Return the final unit
    }
};
