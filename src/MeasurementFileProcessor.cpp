/** 
 * @file MeasurementFileProcessor.cpp
 *  @brief Implementation of the MeasurementFileProcessor class.
 * 
 * The MeasurementFileProcessor class is responsible for loading measurement data from a file, 
 * sorting the measurements, computing statistics, and generating reports. It serves as the controller
 * for the application logic. 
 * 
 * The class uses the Measurement, StatisticsCalculator, and IOStreamHandler classes to perform these tasks.
*/

#include "MeasurementFileProcessor.h"
#include "IOStreamHandler.h"
#include <iostream>
#include <sstream>
#include <algorithm>

MeasurementFileProcessor::MeasurementFileProcessor(const std::string& fileName) 
    : fileName(fileName), isFileLoaded(false) {}

void MeasurementFileProcessor::readFile() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    Measurement m(0, nullptr);
    while (IOStreamHandler::readFromStream(file, m)) {
        measurementsList.push_back(m);
    }
    isFileLoaded = true;
    file.close();
}

void MeasurementFileProcessor::sortMeasurements() {
    std::sort(measurementsList.begin(), measurementsList.end(), [](const Measurement& a, const Measurement& b) {
        return a.getMagnitude() < b.getMagnitude();
    });
}

void MeasurementFileProcessor::numberOriginalOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return;
    }

    int i = 1;
    for (const auto& m : measurementsList) {
        std::cout << i << ". " << m.getMagnitude() << " " << m.getUnit()->getName() << "\n";
        i++;
    }
}

std::vector<std::string> MeasurementFileProcessor::generateReportsInOriginalOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return {};
    }

    std::vector<std::string> reportLines;
    for (const auto& m : measurementsList) {
        std::ostringstream oss;
        oss << m.getMagnitude() << " " << m.getUnit()->getName();
        reportLines.push_back(oss.str());
    }
    return reportLines;
}

std::vector<std::string> MeasurementFileProcessor::generateReportsInSortedOrder() {
    if (!isFileLoaded) {
        std::cerr << "No file loaded to process." << std::endl;
        return {};
    }

    
    std::vector<Measurement> sortedMeasurements = measurementsList;
    numberOriginalOrder();
    sortMeasurements();

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

    double mean = StatisticsCalculator::computeMean(measurementsList);
    double mode = StatisticsCalculator::computeMode(measurementsList);
    double median = StatisticsCalculator::computeMedian(measurementsList);

    std::cout << "Mean: " << mean << "\n";
    std::cout << "Mode: " << mode << "\n";
    std::cout << "Median: " << median << "\n";
}
