#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Measurement.h"
#include "Units.h"
#include "Mass.h"
#include "Length.h"
#include "TimeUnit.h"
#include "Volume.h"
#include "UnitConverter.h"
#include "MeasurementValidator.h"
#include "IOStreamHandler.h"
#include "StatisticsCalculator.h"
#include "ReportGenerator.h"
#include "MeasurementFileProcessor.h"

// Function to process a single file
void processFile(const std::string& fileName, std::vector<std::string>& responses, std::vector<std::string>& sortedResponses) {
    MeasurementFileProcessor fileProcessor(fileName);
    fileProcessor.readFile();

    // Generate original order responses
    responses = fileProcessor.generateReportsInOriginalOrder();

    // Generate sorted responses
    sortedResponses = fileProcessor.generateReportsInSortedOrder();
}

// Function to compute and display statistics for a given list of measurements
void computeAndDisplayStatistics(const std::vector<std::string>& responses) {
    std::vector<Measurement> measurements;
    for (const auto& response : responses) {
        Measurement m = Measurement::fromString(response);
        measurements.push_back(m);
    }

    double mean = StatisticsCalculator::computeMean(measurements);
    double mode = StatisticsCalculator::computeMode(measurements);
    double median = StatisticsCalculator::computeMedian(measurements);

    std::cout << "Mean: " << mean << "\n";
    std::cout << "Mode: " << mode << "\n";
    std::cout << "Median: " << median << "\n";
}

int main() {
    // Vectors to store responses for both files
    std::vector<std::string> responsesYear1, sortedResponsesYear1;
    std::vector<std::string> responsesYear2, sortedResponsesYear2;

    // Process both files
    processFile("year1measurements.txt", responsesYear1, sortedResponsesYear1);
    processFile("year2measurements.txt", responsesYear2, sortedResponsesYear2);

    // Display results
    std::cout << "Responses for year1measurements.txt in original order:\n";
    for (const auto& response : responsesYear1) {
        std::cout << response << "\n";
    }

    std::cout << "\nResponses for year1measurements.txt in ascending order:\n";
    for (const auto& response : sortedResponsesYear1) {
        std::cout << response << "\n";
    }

    std::cout << "\nResponses for year2measurements.txt in original order:\n";
    for (const auto& response : responsesYear2) {
        std::cout << response << "\n";
    }

    std::cout << "\nResponses for year2measurements.txt in ascending order:\n";
    for (const auto& response : sortedResponsesYear2) {
        std::cout << response << "\n";
    }

    // Compute and display statistics
    std::cout << "\nStatistics for year1measurements.txt:\n";
    computeAndDisplayStatistics(responsesYear1);

    std::cout << "\nStatistics for year2measurements.txt:\n";
    computeAndDisplayStatistics(responsesYear2);

    // Save output to a file
    std::ofstream outputFile("measurement_report.txt");
    outputFile << "Responses for year1measurements.txt in original order:\n";
    for (const auto& response : responsesYear1) {
        outputFile << response << "\n";
    }

    outputFile << "\nResponses for year1measurements.txt in ascending order:\n";
    for (const auto& response : sortedResponsesYear1) {
        outputFile << response << "\n";
    }

    outputFile << "\nResponses for year2measurements.txt in original order:\n";
    for (const auto& response : responsesYear2) {
        outputFile << response << "\n";
    }

    outputFile << "\nResponses for year2measurements.txt in ascending order:\n";
    for (const auto& response : sortedResponsesYear2) {
        outputFile << response << "\n";
    }

    outputFile << "\nStatistics for year1measurements.txt:\n";
    computeAndDisplayStatistics(responsesYear1);

    outputFile << "\nStatistics for year2measurements.txt:\n";
    computeAndDisplayStatistics(responsesYear2);

    outputFile.close();

    return 0;
}
