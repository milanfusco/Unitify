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
#include <variant>
#include <vector>
#include "Measurement.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"

using MeasurementOrOperator =
    std::variant<Measurement, std::string>;  ///< Type to represent a
                                             ///< Measurement or an operator.

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
  std::vector<MeasurementOrOperator>
      measurementLine;  ///< A vector of Measurement objects and operators
                        ///< parsed from the file.
  std::vector<std::vector<MeasurementOrOperator>>
      measurementsList;  ///< A vector of vectors of lines of measurements and
                         ///< operators from the file.
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
  Measurement applyOperation(const Measurement& left,
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
  Measurement processOperatorsWithPEMDAS(
      const std::vector<Measurement>& measurements,
      const std::vector<char>& operators);

  /**
   * @brief Reads the measurement data from the file and stores it in a
   * measurementLine vector in the measurementsList vector.
   *
   * Throws an exception if the file cannot be opened or read properly.
   */
  void readFile();

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