#include <limits.h>  // For PATH_MAX
#include <unistd.h>  // For getcwd
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "IOStreamHandler.h"
#include "Length.h"
#include "Mass.h"
#include "Measurement.h"
#include "MeasurementFileProcessor.h"
#include "MeasurementValidator.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"
#include "TimeUnit.h"
#include "UnitConverter.h"
#include "Units.h"
#include "Volume.h"

void processFile(const std::string& fileName,
                 std::vector<std::string>& responses,
                 std::vector<std::string>& sortedResponses) {
  MeasurementFileProcessor fileProcessor(fileName);
  fileProcessor.readFile();

  responses = fileProcessor.generateReportsInOriginalOrder();

  sortedResponses = fileProcessor.generateReportsInSortedOrder();
}

void computeAndDisplayStatistics(const std::vector<std::string>& responses,
                                 const std::string& fileName,
                                 std::ofstream& outputFile) {
  std::vector<Measurement> measurements;

  for (const auto& response : responses) {
    Measurement m = Measurement::fromString(response);
    measurements.push_back(m);
  }

  double mean = StatisticsCalculator::computeMean(measurements);
  double mode = StatisticsCalculator::computeMode(measurements);
  double median = StatisticsCalculator::computeMedian(measurements);

  std::cout << "\nStatistics for " << fileName << ":\n";
  std::cout << "Mean: " << mean << "\n";
  std::cout << "Mode: " << mode << "\n";
  std::cout << "Median: " << median << "\n";

  outputFile << "\nStatistics for " << fileName << ":\n";
  outputFile << "Mean: " << mean << "\n";
  outputFile << "Mode: " << mode << "\n";
  outputFile << "Median: " << median << "\n";
}

void saveOutputToFile(const std::string& outputFileName,
                      const std::vector<std::string>& responsesYear1,
                      const std::vector<std::string>& sortedResponsesYear1,
                      const std::vector<std::string>& responsesYear2,
                      const std::vector<std::string>& sortedResponsesYear2) {
  std::ofstream outputFile(outputFileName);

  outputFile << "Responses for year1measurements.txt in original order:\n";
  for (const auto& response : responsesYear1) {
    outputFile << response << "\n";
  }

  outputFile << "\nResponses for year1measurements.txt in ascending order:\n";
  for (const auto& response : sortedResponsesYear1) {
    outputFile << response << "\n";
  }

  computeAndDisplayStatistics(responsesYear1, "year1measurements.txt",
                              outputFile);

  outputFile << "\nResponses for year2measurements.txt in original order:\n";
  for (const auto& response : responsesYear2) {
    outputFile << response << "\n";
  }

  outputFile << "\nResponses for year2measurements.txt in ascending order:\n";
  for (const auto& response : sortedResponsesYear2) {
    outputFile << response << "\n";
  }

  computeAndDisplayStatistics(responsesYear2, "year2measurements.txt",
                              outputFile);

  outputFile.close();
}


int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <year1_file> <year2_file>"
              << std::endl;
    return 1;
  }

  // File paths from command-line arguments
  std::string year1File = argv[1];
  std::string year2File = argv[2];

  // Vectors to store responses for both files
  std::vector<std::string> responsesYear1, sortedResponsesYear1;
  std::vector<std::string> responsesYear2, sortedResponsesYear2;

  // Process both files
  processFile(year1File, responsesYear1, sortedResponsesYear1);
  processFile(year2File, responsesYear2, sortedResponsesYear2);

  // Display results for year1
  std::cout << "Responses for " << year1File << " in original order:\n";
  for (const auto& response : responsesYear1) {
    std::cout << response << "\n";
  }

  std::cout << "\nResponses for " << year1File << " in ascending order:\n";
  for (const auto& response : sortedResponsesYear1) {
    std::cout << response << "\n";
  }

  // Display results for year2
  std::cout << "\nResponses for " << year2File << " in original order:\n";
  for (const auto& response : responsesYear2) {
    std::cout << response << "\n";
  }

  std::cout << "\nResponses for " << year2File << " in ascending order:\n";
  for (const auto& response : sortedResponsesYear2) {
    std::cout << response << "\n";
  }

  // Output file name
  std::string outputFileName = "measurement_report.txt";

  // Save output to a file
  saveOutputToFile(outputFileName, responsesYear1, sortedResponsesYear1,
                   responsesYear2, sortedResponsesYear2);

  // Get the current working directory and print the output file path
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    std::cout << "\nOutput saved to: " << cwd << "/" << outputFileName << "\n";
  } else {
    std::cerr << "Error retrieving current working directory." << std::endl;
  }

  return 0;
}