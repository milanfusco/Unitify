/**
 * @file MeasurementFileProcessor.h
 * @brief Definition of the MeasurementFileProcessor class.
 *
 * The MeasurementFileProcessor class is responsible for loading measurement
 * data from a file, sorting the measurements, computing statistics, and
 * generating reports. It serves as the controller for the application logic.
 *
 * The class uses the Measurement, StatisticsCalculator, and ReportGenerator
 * classes to perform these tasks.
 * @version 0.1
 */

#ifndef MEASUREMENTFILEPROCESSOR_H
#define MEASUREMENTFILEPROCESSOR_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <optional>
#include "Measurement.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"

/**
 * @class MeasurementFileProcessor
 * @brief Handles the reading, processing, and analysis of measurement data from
 * a file.
 *
 * The MeasurementFileProcessor class serves as the controller for the
 * application logic. It is responsible for loading measurement data from a
 * file, sorting the measurements, computing statistics, and generating reports.
 */
class MeasurementFileProcessor {
 private:
  std::string fileName;  ///< The name of the file containing measurement data.
  std::vector< std::vector<Measurement> >measurementsList;  ///< A list of measurements loaded from the file.
  bool isFileLoaded;     ///< Flag to check if the file has been successfully
                         ///< loaded.
  bool isValidOperator(
      const std::string& op);  ///> Checks if the operator is valid.

 public:
  /**
   * @brief Constructs a MeasurementFileProcessor with the specified file name.
   * @param fileName The name of the file to be processed.
   */
  MeasurementFileProcessor(const std::string& fileName);

  /**
   * @enum
   * @brief Enumerates the precedence levels for arithmetic operators.
   * Enhances readability and maintainability of the code.
   * 0 is invalid, 1 is for addition and subtraction, 2 is for multiplication
   * and division. higher the integer value, higher the precedence.
   */
  enum precedence { INVALID = 0, ADD_SUB = 1, MUL_DIV = 2 };

  /**
   * @brief Determines the precedence level of an arithmetic operator.
   * @param op The operator character.
   * @return The precedence level of the operator.
   */
  int getPrecedence(char op);

  /**
   * @brief Applies an arithmetic operation to two Measurement objects.
   * @param left The left operand Measurement.
   * @param right The right operand Measurement.
   * @param op The arithmetic operator character.
   * @return The result of the operation.
   */
  std::optional<Measurement> applyOperation(const Measurement& left,
                             const Measurement& right,
                             char op);

  /**
   * @brief Processes a list of measurements and operators using the PEMDAS
   * order of operations.
   *
   * This method evaluates the arithmetic operations in the order of precedence
   * (PEMDAS). It uses the Shunting Yard algorithm to process the measurements
   * and operators. This ensures that the arithmetic operations are performed in
   * the correct order.
   *
   * @param measurements A vector of Measurement objects.
   * @param operators A vector of arithmetic operators.
   * @return The result of the arithmetic operations.
   */
  std::optional<Measurement> processOperatorsWithPEMDAS(
      const std::vector<Measurement>& measurements,
      const std::vector<char>& operators);

    /**
     * @brief Processes a line of input data from the file.
     * @param line The line of input data to process.
     * @param lineNum The line number in the file.
     * @param measurements The vector to store the Measurement objects.
     * @param operators The vector to store the arithmetic operators.
     * @return true if the line was processed successfully, false otherwise.
     */
    bool applyTopOperator(std::stack<Measurement>& operandStack, 
                          std::stack<char>& operatorStack);

  /**
   * @brief Reads the measurement data from the file and stores it in a
   * measurementLine vector in the measurementsList vector.
   *
   * Throws an exception if the file cannot be opened or read properly.
   */
  void readFile();

    /**
     * @brief Processes a line of input data from the file.
     * @param line The line of input data to process.
     * @param lineNum The line number in the file.
     * @param measurements The vector to store the Measurement objects.
     * @param operators The vector to store the arithmetic operators.
     */
    void processLine(const std::string& line, int lineNum,
                     std::vector<Measurement>& measurements,
                     std::vector<char>& operators);

  /**
   * @brief Sorts the loaded measurements in ascending order.
   */
  void sortMeasurements();

  /**
   * @brief Adds a unique identifier to each measurement to maintain their
   * original order.
   */
  void numberOriginalOrder();

  /**
   * @brief Generates reports based on the original order of the measurements.
   * @return A vector of strings, each representing a report in the original
   * order.
   */
  std::vector<std::string> generateReportsInOriginalOrder();

  /**
   * @brief Generates reports based on the sorted order of the measurements.
   * @return A vector of strings, each representing a report in sorted order.
   */
  std::vector<std::string> generateReportsInSortedOrder();

  /**
   * @brief Computes statistics (mean, mode, median) for the loaded
   * measurements.
   */
  void computeStatistics();
};

#endif  // MEASUREMENTFILEPROCESSOR_H