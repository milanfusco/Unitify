/**
 * @file MeasurementFileProcessor.h
 * @brief Definition of the MeasurementFileProcessor class.
 * 
 * The MeasurementFileProcessor class is responsible for loading measurement data from a file, 
 * sorting the measurements, computing statistics, and generating reports. It serves as the controller
 * for the application logic. 
 * 
 * The class uses the Measurement, StatisticsCalculator, and ReportGenerator classes to perform these tasks.
 * @version 0.1
 */

#ifndef MEASUREMENTFILEPROCESSOR_H
#define MEASUREMENTFILEPROCESSOR_H

#include "Measurement.h"
#include "StatisticsCalculator.h"
#include "ReportGenerator.h"
#include <vector>
#include <string>
#include <fstream>

/**
 * @class MeasurementFileProcessor
 * @brief Handles the reading, processing, and analysis of measurement data from a file.
 * 
 * The MeasurementFileProcessor class serves as the controller for the application logic. 
 * It is responsible for loading measurement data from a file, sorting the measurements, 
 * computing statistics, and generating reports.
 */
class MeasurementFileProcessor {
private:
    std::string fileName;   ///< The name of the file containing measurement data.
    std::vector<Measurement> measurementsList;  ///< A vector of Measurement objects loaded from the file.
    bool isFileLoaded;  ///< Flag to check if the file has been successfully loaded.

public:
    /**
     * @brief Constructs a MeasurementFileProcessor with the specified file name.
     * @param fileName The name of the file to be processed.
     */
    MeasurementFileProcessor(const std::string& fileName);

    /**
     * @brief Reads the measurement data from the file and stores it in measurementsList.
     * 
     * Throws an exception if the file cannot be opened or read properly.
     */
    void readFile();

    /**
     * @brief Sorts the loaded measurements in ascending order.
     */
    void sortMeasurements();

    /**
     * @brief Adds a unique identifier to each measurement to maintain their original order.
     */
    void numberOriginalOrder();

    /**
     * @brief Generates reports based on the original order of the measurements.
     * @return A vector of strings, each representing a report in the original order.
     */
    std::vector<std::string> generateReportsInOriginalOrder();

    /**
     * @brief Generates reports based on the sorted order of the measurements.
     * @return A vector of strings, each representing a report in sorted order.
     */
    std::vector<std::string> generateReportsInSortedOrder();

    /**
     * @brief Computes statistics (mean, mode, median) for the loaded measurements.
     */
    void computeStatistics();
};

#endif // MEASUREMENTFILEPROCESSOR_H