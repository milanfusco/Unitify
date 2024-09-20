/** 
 * @file MeasurementFileProcessor.cpp
 *  @brief Implementation of the MeasurementFileProcessor class.
 * 
 * The MeasurementFileProcessor class is responsible for loading measurement data from a file, 
 * sorting the measurements, computing statistics, and generating reports. It serves as the controller
 * for the application logic. 
 * 
 * @version 0.2
*/

#include "MeasurementFileProcessor.h"
#include "Measurement.h"
#include "IOStreamHandler.h"
#include "StatisticsCalculator.h"
#include "ReportGenerator.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <variant>
#include <stdexcept>

MeasurementFileProcessor::MeasurementFileProcessor(const std::string& fileName) 
    : fileName(fileName), isFileLoaded(false) {}

bool MeasurementFileProcessor::isValidOperator(const std::string& op) {
    return validOperators.find(op) != validOperators.end();
}


void MeasurementFileProcessor::readFile() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line); // Use a string stream to parse the line

        try {
            std::string m1_str, m2_str, m3_str;
            std::string operator_a, operator_b;

            // Extract measurement strings and operators
            iss >> m1_str >> operator_a >> m2_str >> operator_b >> m3_str;

            // Use the fromString method to parse each measurement
            Measurement m1 = Measurement::fromString(m1_str);
            Measurement m2 = Measurement::fromString(m2_str);
            Measurement m3 = Measurement::fromString(m3_str);

            // Ensure the operators are valid
            if (!isValidOperator(operator_a) || !isValidOperator(operator_b)) {
                std::cerr << "Invalid operators in line: " << line << std::endl;
                continue; // Skip invalid lines
            }

            // Store the measurements and operators in the same line (in their original order)
            std::vector<MeasurementOrOperator> measurementLine = {m1, operator_a, m2, operator_b, m3};

            // Add the structured measurementLine to measurementsList
            measurementsList.push_back(measurementLine);

        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            continue; // Skip invalid lines
        }
    }

    isFileLoaded = true;
    file.close();
}

void MeasurementFileProcessor::sortMeasurements() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return;
    }

    // Extract Measurements and sort them
    std::vector<Measurement> measurementsToSort;

    for (const auto& measurementLine : measurementsList) {
        for (const auto& element : measurementLine) {
            if (std::holds_alternative<Measurement>(element)) {
                measurementsToSort.push_back(std::get<Measurement>(element));
            }
        }
    }

    // Sort the extracted measurements based on magnitude
    std::sort(measurementsToSort.begin(), measurementsToSort.end(), [](const Measurement& a, const Measurement& b) {
        return a.getMagnitude() < b.getMagnitude();
    });

    // Output sorted measurements
    std::cout << "Sorted measurements: \n";
    for (const auto& m : measurementsToSort) {
        std::cout << m.getMagnitude() << " " << m.getUnit()->getName() << "\n";
    }
}

void MeasurementFileProcessor::numberOriginalOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return;
    }

    int i = 1;
    for (const auto& measurementLine : measurementsList) {
        for (const auto& element : measurementLine) {
            if (std::holds_alternative<Measurement>(element)) {
                const Measurement& m = std::get<Measurement>(element);
                std::cout << i << ". " << m.getMagnitude() << " " << m.getUnit()->getName() << "\n";
                i++;
            }
        }
    }
}

std::vector<std::string> MeasurementFileProcessor::generateReportsInOriginalOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return {};
    }

    std::vector<std::string> reportLines;

    for (const auto& measurementLine : measurementsList) {
        for (const auto& element : measurementLine) {
            if (std::holds_alternative<Measurement>(element)) {
                const Measurement& m = std::get<Measurement>(element);
                std::ostringstream oss;
                oss << m.getMagnitude() << " " << m.getUnit()->getName();
                reportLines.push_back(oss.str());
            }
        }
    }

    return reportLines;
}

std::vector<std::string> MeasurementFileProcessor::generateReportsInSortedOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return {};
    }

    std::vector<Measurement> sortedMeasurements;

    for (const auto& measurementLine : measurementsList) {
        for (const auto& element : measurementLine) {
            if (std::holds_alternative<Measurement>(element)) {
                sortedMeasurements.push_back(std::get<Measurement>(element));
            }
        }
    }

    std::sort(sortedMeasurements.begin(), sortedMeasurements.end(), [](const Measurement& a, const Measurement& b) {
        return a.getMagnitude() < b.getMagnitude();
    });

    std::vector<std::string> reportLines;
    for (const auto& m : sortedMeasurements) {
        std::ostringstream oss;
        oss << m.getMagnitude() << " " << m.getUnit()->getName();
        reportLines.push_back(oss.str());
    }

    return reportLines;
}

void MeasurementFileProcessor::computeStatistics() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to compute statistics." << std::endl;
        return;
    }

    std::vector<Measurement> measurementsForStats;

    for (const auto& measurementLine : measurementsList) {
        for (const auto& element : measurementLine) {
            if (std::holds_alternative<Measurement>(element)) {
                measurementsForStats.push_back(std::get<Measurement>(element));
            }
        }
    }

    if (measurementsForStats.empty()) {
        std::cerr << "No valid measurements to compute statistics." << std::endl;
        return;
    }

    double mean = StatisticsCalculator::computeMean(measurementsForStats);
    double mode = StatisticsCalculator::computeMode(measurementsForStats);
    double median = StatisticsCalculator::computeMedian(measurementsForStats);

    std::cout << "Mean: " << mean << "\n";
    std::cout << "Mode: " << mode << "\n";
    std::cout << "Median: " << median << "\n";
}