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

/**
 * @brief Displays the title banner for the application.
 * 
 * This function prints the title banner for the application, including
 * information about the software, licensing, and support.
 * 
 * Displays government restricted rights notice and warranty disclaimer, as this 
 * software is developed by SpaceX and licensed to the U.S. Government.
 * 
 * @warning FOR INTERNAL USE ONLY - DO NOT DISTRIBUTE
 */
void titleBanner() {
  std::cout << "/=============================================================="
               "======\\ \n"
            << "|| __  __     __   __     __     ______   __     ______   __  "
               "__    || \n"
            << "||/\\ \\/\\ \\   /\\ '-.\\ \\   /\\ \\   /\\__  _\\ /\\ \\   "
               "/\\  ___\\ /\\ \\_\\ \\   || \n"
            << "||\\ \\ \\_\\ \\  \\ \\ \\-.  \\  \\ \\ \\  \\/_/\\ \\/ \\ \\ "
               "\\  \\ \\  __\\ \\ \\____ \\  || \n"
            << "|| \\ \\_____\\  \\ \\_\\ '\\_\\  \\ \\_\\    \\ \\_\\  \\ "
               "\\_\\  \\ \\_\\    \\/\\_____\\ || \n"
            << "||  \\/_____/   \\/_/ \\/_/   \\/_/     \\/_/   \\/_/   \\/_/  "
               "   \\/_____/ || \n"
            << "\\============================================================="
               "=======/ \n"
            << std::endl;

  std::cout << "                          Unitify v1.0\n" << std::endl;
    std::cout << "           FOR INTERNAL USE ONLY - DO NOT DISTRIBUTE\n"
            << std::endl;
  std::cout << "Copyright (c) 2024 Space Exploration Technologies Corporation "
               "(SpaceX) \n"
               "Licensed to Mars Exploration Program, NASA, under U.S. "
               "Government Contract.\n"
               "All Foreign Rights Reserved to the U.S. Government.\n"
            << std::endl;
  std::cout
      << " For software support, please contact SpaceX at emusk@spacex.com\n"
      << std::endl;

  std::cout << "              GOVERNMENT RESTRICTED RIGHTS NOTICE\n"
            << std::endl;
  std::cout << "This software is developed by SpaceX and licensed to the U.S. "
               "Government\n"
               "with RESTRICTED RIGHTS. Use, duplication, or disclosure is "
               "subject to\n"
               "restrictions as set forth in subparagraph (c)(1)(ii) of the "
               "Rights in\n"
               "Technical Data and Computer Software clause at DFARS "
               "252.227-7013. \n"
            << std::endl;
  std::cout
      << "Export of this software is controlled under the International "
         "Traffic in Arms\n"
         "Regulations (ITAR). Unauthorized export or disclosure to non-U.S. "
         "persons is\n"
         "prohibited without prior authorization from the U.S. Government.\n"
      << std::endl;
  std::cout << "Warranty Disclaimer: This software is provided 'AS IS' with no "
               "warranties,\n"
               "including fitness for a particular purpose or merchantability. "
               "SpaceX assumes no\n"
               "liability for any damages arising from its use.\n"
            << std::endl;
  
}


/**
 * @brief Process the file and generate reports.
 * 
 * This function processes the file, generates reports in original order and
 * sorted order, and stores the responses in the provided vectors.
 * 
 * @param fileName The name of the file to process.
 * @param responses The vector to store the responses in original order.
 * @param sortedResponses The vector to store the responses in sorted order.
 */
void processFile(const std::string& fileName,
                 std::vector<std::string>& responses,
                 std::vector<std::string>& sortedResponses) {
  MeasurementFileProcessor fileProcessor(fileName);
  fileProcessor.readFile();

  responses = fileProcessor.generateReportsInOriginalOrder();

  sortedResponses = fileProcessor.generateReportsInSortedOrder();
}

/**
 * @brief Compute and display statistics.
 * 
 * This function computes and displays the mean, mode, and median statistics
 * for the provided responses and writes them to the output file.
 * 
 * @param responses The responses to compute statistics for.
 * @param fileName The name of the file to display statistics for.
 * @param outputFile The output file stream to write the statistics to.
 */
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

/**
 * @brief Save output to a file.
 * 
 * This function saves the output to a file with the provided file name.
 * 
 * @param outputFileName The name of the output file.
 * @param responsesYear1 The responses for argv[1] in original order.
 * @param sortedResponsesYear1 The responses for argv[1] in sorted order.
 * @param responsesYear2 The responses for argv[2] in original order.
 * @param sortedResponsesYear2 The responses for argv[2] in sorted order.
 */
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

  computeAndDisplayStatistics(responsesYear1, "argv[1]", outputFile);

  outputFile << "\nResponses for year2measurements.txt in original order:\n";
  for (const auto& response : responsesYear2) {
    outputFile << response << "\n";
  }

  outputFile << "\nResponses for year2measurements.txt in ascending order:\n";
  for (const auto& response : sortedResponsesYear2) {
    outputFile << response << "\n";
  }

  computeAndDisplayStatistics(responsesYear2, "argv[2]", outputFile);

  outputFile.close();
}

/**
 * @brief Main function to process the files and generate reports.
 * 
 * This function processes the files provided as command-line arguments,
 * generates reports, and saves the output to a file.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if the program exits successfully, 1 otherwise.
 */
int main(int argc, char* argv[]) {
  titleBanner();

  ///> Check if the correct number of arguments are provided
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <year1_file> <year2_file>"
              << std::endl;
    return 1;
  }

  ///> Store the file names from the command-line arguments
  std::string year1File = argv[1];
  std::string year2File = argv[2];

  ///> Create vectors to store the responses and sorted responses
  std::vector<std::string> responsesYear1, sortedResponsesYear1;
  std::vector<std::string> responsesYear2, sortedResponsesYear2;

  ///> Process both files
  processFile(year1File, responsesYear1, sortedResponsesYear1);
  processFile(year2File, responsesYear2, sortedResponsesYear2);

  ///> Display results for year1 in original order
  std::cout << "Responses for " << year1File << " in original order:\n";
  for (const auto& response : responsesYear1) {
    std::cout << response << "\n";
  }

  ///> Display results for year1 in ascending order
  std::cout << "\nResponses for " << year1File << " in ascending order:\n";
  for (const auto& response : sortedResponsesYear1) {
    std::cout << response << "\n";
  }

  ///> Display results for year2 in original order
  std::cout << "\nResponses for " << year2File << " in original order:\n";
  for (const auto& response : responsesYear2) {
    std::cout << response << "\n";
  }
  ///> Display results for year2 in ascending order
  std::cout << "\nResponses for " << year2File << " in ascending order:\n";
  for (const auto& response : sortedResponsesYear2) {
    std::cout << response << "\n";
  }

  ///> Create the string for the output file
  std::string outputFileName = "measurement_report.txt";

  ///> Save output to file
  saveOutputToFile(outputFileName, responsesYear1, sortedResponsesYear1,
                   responsesYear2, sortedResponsesYear2);

  ///> Get the current working directory and print the output file path for the user
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    std::cout << "\nOutput saved to: " << cwd << "/" << outputFileName << "\n";
  } else {
    std::cerr << "Error retrieving current working directory." << std::endl;
  }

  return 0;
}