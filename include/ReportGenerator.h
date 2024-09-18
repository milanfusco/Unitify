/**
 * @file ReportGenerator.h
 * @brief Declaration of the ReportGenerator class.
 * 
 * The ReportGenerator class provides methods to generate various types of reports
 * based on a collection of Measurement objects. It supports generating both text-based
 * and CSV-formatted reports, allowing for flexible presentation of measurement data.
 * 
 * @version 0.1
*/

#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "Measurement.h"
#include <vector>
#include <string>

/**
 * @class ReportGenerator
 * @brief A utility class for generating reports from a collection of measurements.
 * 
 * The ReportGenerator class provides static methods to create different types of reports
 * from a given set of Measurement objects. Reports can be generated in plain text format 
 * or as CSV (Comma-Separated Values) format, which can be easily exported or displayed.
 */
class ReportGenerator {
public:
    /**
     * @brief Generates a text-based report from a collection of measurements.
     * 
     * Creates a human-readable text report summarizing the measurements provided.
     * The report includes each measurement's magnitude and unit information.
     * 
     * @param measurements A vector containing Measurement objects to be reported.
     * @return A string representing the text-based report of the measurements.
     */
    static std::string generateTextReport(const std::vector<Measurement>& measurements);

    /**
     * @brief Generates a CSV-formatted report from a collection of measurements.
     * 
     * Creates a CSV (Comma-Separated Values) report summarizing the measurements 
     * provided. The CSV format is suitable for importing into spreadsheets or other 
     * applications that handle tabular data.
     * 
     * @param measurements A vector containing Measurement objects to be reported.
     * @return A string representing the CSV-formatted report of the measurements.
     */
    static std::string generateCSVReport(const std::vector<Measurement>& measurements);
};

#endif // REPORTGENERATOR_H