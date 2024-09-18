/**
 * @file StatisticsCalculator.h
 * @brief Declaration of the StatisticsCalculator class.
 * 
 * The StatisticsCalculator class provides static methods to compute various statistical 
 * measures (mean, median, and mode) from a collection of measurements. This class 
 * is designed to handle common statistical operations that may be required for analyzing 
 * sets of measurements.
 * 
 * @version 0.1
 */

#ifndef STATISTICSCALCULATOR_H
#define STATISTICSCALCULATOR_H

#include "Measurement.h"
#include <vector>

/**
 * @class StatisticsCalculator
 * @brief A utility class for calculating statistical measures of a collection of measurements.
 * 
 * The StatisticsCalculator class provides static methods to compute the mean, median, 
 * and mode of a vector of Measurement objects. These methods can be used to analyze 
 * measurement data.
 */
class StatisticsCalculator {
public:
    /**
     * @brief Computes the mean of a collection of measurements.
     * 
     * Calculates the average (mean) value of the provided vector of Measurement objects.
     * 
     * @param measurements A vector containing Measurement objects.
     * @return The mean value of the measurements.
     */
    static double computeMean(const std::vector<Measurement>& measurements);

    /**
     * @brief Computes the mode of a collection of measurements.
     * 
     * Determines the mode (most frequently occurring value) of the provided vector of 
     * Measurement objects.
     * 
     * @param measurements A vector containing Measurement objects.
     * @return The mode value of the measurements.
     */
    static double computeMode(const std::vector<Measurement>& measurements);

    /**
     * @brief Computes the median of a collection of measurements.
     * 
     * Calculates the median (middle value when sorted) of the provided vector of 
     * Measurement objects. The input vector may be modified during this operation.
     * 
     * @param measurements A vector containing Measurement objects. The vector may be modified.
     * @return The median value of the measurements.
     */
    static double computeMedian(std::vector<Measurement>& measurements);
};

#endif // STATISTICSCALCULATOR_H