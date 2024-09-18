/**
 * @file StatisticsCalculator.cpp
 * @brief Implementation of the StatisticsCalculator class
 * 
 * This file contains the implementation of the StatisticsCalculator class, which provides
 * methods for computing statistical measures (mean, median, and mode) from a collection of
 * measurements.
 */

#include "StatisticsCalculator.h"
#include <algorithm>
#include <map>

double StatisticsCalculator::computeMean(const std::vector<Measurement>& measurements) {
    double sum = 0.0;
    for (const auto& m : measurements) {
        sum += m.getMagnitude();
    }
    return sum / measurements.size();
}

double StatisticsCalculator::computeMode(const std::vector<Measurement>& measurements) {
    std::map<double, int> frequency;
    for (const auto& m : measurements) {
        frequency[m.getMagnitude()]++;
    }

    int maxCount = 0;
    double mode = 0.0;
    for (const auto& pair : frequency) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mode = pair.first;
        }
    }
    return mode;
}

double StatisticsCalculator::computeMedian(std::vector<Measurement>& measurements) {
    std::sort(measurements.begin(), measurements.end(), [](const Measurement& a, const Measurement& b) {
        return a.getMagnitude() < b.getMagnitude();
    });

    size_t size = measurements.size();
    if (size % 2 == 0) {
        return (measurements[size / 2 - 1].getMagnitude() + measurements[size / 2].getMagnitude()) / 2;
    } else {
        return measurements[size / 2].getMagnitude();
    }
}
