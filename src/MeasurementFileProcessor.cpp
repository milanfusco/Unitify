/**
 * @file MeasurementFileProcessor.cpp
 *  @brief Implementation of the MeasurementFileProcessor class.
 *
 * The MeasurementFileProcessor class is responsible for loading measurement
 * data from a file, sorting the measurements, computing statistics, and
 * generating reports. It serves as the controller for the application logic.
 *
 * @version 0.2
 */

#include "MeasurementFileProcessor.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "IOStreamHandler.h"
#include "Measurement.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"
#include "UnitConverter.h"

/**
 * @namespace anonymous (not the hacktivist group :P)
 * @brief Anonymous namespace to encapsulate the validOperators set.
 */
namespace {
static const std::set<std::string> validOperators = {
    "+", "-", "*", "/"};  ///< Set of valid operators.
}

MeasurementFileProcessor::MeasurementFileProcessor(const std::string& fileName)
    : fileName(fileName), isFileLoaded(false) {}

bool MeasurementFileProcessor::isValidOperator(const std::string& op) {
  return validOperators.find(op) != validOperators.end();
}

enum precedence { INVALID = 0, MUL_DIV, ADD_SUB };

int MeasurementFileProcessor::getPrecedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return ADD_SUB;  ///> Lower precedence
    case '*':
    case '/':
      return MUL_DIV;  ///> Higher precedence
    default:
      return INVALID;  ///> Invalid operator
  }
}

Measurement MeasurementFileProcessor::applyOperation(const Measurement& left,
                                                     const Measurement& right,
                                                     char op) {
  try {
    // Check if units are the same
    if (left.getUnit()->getName() != right.getUnit()->getName()) {
      throw std::invalid_argument(
          "Units must be the same for arithmetic operations.");
    }

    // Convert both to base units
    Measurement leftBase = UnitConverter::convertToBaseUnit(left);
    Measurement rightBase = UnitConverter::convertToBaseUnit(right);

    // Perform the arithmetic in base units
    double newMagnitude;
    switch (op) {
      case '+':
        newMagnitude = leftBase.getMagnitude() + rightBase.getMagnitude();
        break;
      case '-':
        newMagnitude = leftBase.getMagnitude() - rightBase.getMagnitude();
        break;
      case '*':
        newMagnitude = leftBase.getMagnitude() * rightBase.getMagnitude();
        break;
      case '/':
        if (rightBase.getMagnitude() == 0) {
          throw std::invalid_argument("Division by zero is not allowed.");
        }
        newMagnitude = leftBase.getMagnitude() / rightBase.getMagnitude();
        break;
      default:
        throw std::invalid_argument("Invalid operator.");
    }

    // Return result in the original left unit
    return UnitConverter::convertToBaseUnit(
        Measurement(newMagnitude, leftBase.getUnit()));

  } catch (const std::invalid_argument& e) {
    std::cerr << "Operation error: " << e.what() << std::endl;
    throw;
  }
}

Measurement MeasurementFileProcessor::processOperatorsWithPEMDAS(
    const std::vector<Measurement>& measurements,
    const std::vector<char>& operators) {
  std::stack<Measurement> operandStack;
  std::stack<char> operatorStack;

  std::cout << "Processing PEMDAS, operands: " << measurements.size()
            << ", operators: " << operators.size() << std::endl;

  for (size_t i = 0; i < measurements.size(); ++i) {
    operandStack.push(measurements[i]);

    if (i < operators.size()) {
      char currentOperator = operators[i];

      while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >=
                                           getPrecedence(currentOperator)) {
        if (!applyTopOperator(operandStack, operatorStack)) {
          throw std::runtime_error("Failed to apply operator");
        }
      }
      operatorStack.push(currentOperator);
    }
  }

  while (!operatorStack.empty()) {
    if (!applyTopOperator(operandStack, operatorStack)) {
      throw std::runtime_error("Failed to apply operator");
    }
  }

  if (operandStack.empty()) {
    throw std::runtime_error("No result available");
  }

  return operandStack.top();
}

bool MeasurementFileProcessor::applyTopOperator(
    std::stack<Measurement>& operandStack,
    std::stack<char>& operatorStack) {
  if (operandStack.size() < 2) {
    std::cerr << "Not enough operands for operation" << std::endl;
    return false;
  }

  Measurement right = operandStack.top();
  operandStack.pop();
  Measurement left = operandStack.top();
  operandStack.pop();
  char op = operatorStack.top();
  operatorStack.pop();

  try {
    Measurement result = applyOperation(left, right, op);
    operandStack.push(result);
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error applying operation: " << e.what() << std::endl;
    return false;
  }
}

void MeasurementFileProcessor::readFile() {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + fileName);
  }

  std::string line;
  int lineNum = 1;

  while (getline(file, line)) {
    std::vector<Measurement> measurements;
    std::vector<char> operators;

    processLine(line, lineNum++, measurements, operators);

    try {
      Measurement result = processOperatorsWithPEMDAS(measurements, operators);
      std::cout << "Result: " << result.getMagnitude() << " "
                << result.getUnit()->getName() << std::endl;
      measurementsList.push_back({result});
    } catch (const std::exception& e) {
      throw std::runtime_error("Error: " + std::string(e.what()));
    }
  }

  file.close();
  isFileLoaded = true;
}

void MeasurementFileProcessor::processLine(
    const std::string& line,
    int lineNum,
    std::vector<Measurement>& measurements,
    std::vector<char>& operators) {
  std::stringstream ss(line);
  double magnitude;
  std::string unitStr, operatorStr;

  while (ss >> magnitude >> unitStr) {
    try {
      std::shared_ptr<Units> unit = Units::getUnitByName(unitStr);
      if (!unit) {
        throw std::invalid_argument("Invalid unit: " + unitStr);
      }
      measurements.emplace_back(magnitude, unit);

      if (ss >> operatorStr && isValidOperator(operatorStr)) {
        operators.push_back(operatorStr[0]);
      }
    } catch (const std::exception& e) {
      std::cerr << "Line " << lineNum << " error: " << e.what() << std::endl;
    }
  }
}

void MeasurementFileProcessor::sortMeasurements() {
  if (!isFileLoaded) {
    std::cerr << "No file loaded to process." << std::endl;
    return;
  }

  std::vector<Measurement> measurementsToSort;

  for (const auto& measurements : measurementsList) {
    for (const auto& m : measurements) {
      measurementsToSort.push_back(m);
    }
  }

  std::sort(measurementsToSort.begin(), measurementsToSort.end(),
            [](const Measurement& a, const Measurement& b) {
              return a.getMagnitude() < b.getMagnitude();
            });
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
  for (const auto& measurements : measurementsList) {
    for (const auto& m : measurements) {
      std::cout << i++ << ". " << m.getMagnitude() << " "
                << m.getUnit()->getName() << std::endl;
    }
  }
}

std::vector<std::string>
MeasurementFileProcessor::generateReportsInOriginalOrder() {
  if (!isFileLoaded) {
    std::cerr << "No file loaded to process." << std::endl;
    return {};
  }

  std::vector<std::string> reportLines;

  for (const auto& measurements : measurementsList) {
    for (const auto& m : measurements) {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(2);
      oss << m.getMagnitude() << " " << m.getUnit()->getName();
      reportLines.push_back(oss.str());
    }
  }

  return reportLines;
}

std::vector<std::string>
MeasurementFileProcessor::generateReportsInSortedOrder() {
  if (!isFileLoaded) {
    std::cerr << "No file loaded to process." << std::endl;
    return {};
  }

  std::vector<Measurement> sortedMeasurements;

  for (const auto& measurements : measurementsList) {
    for (const auto& m : measurements) {
      sortedMeasurements.push_back(m);
    }
  }

  std::sort(sortedMeasurements.begin(), sortedMeasurements.end(),
            [](const Measurement& a, const Measurement& b) {
              return a.getMagnitude() < b.getMagnitude();
            });
  std::vector<std::string> reportLines;
  for (const auto& m : sortedMeasurements) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
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

  for (const auto& measurements : measurementsList) {
    for (const auto& m : measurements) {
      measurementsForStats.push_back(m);
    }
  }

  if (measurementsList.empty()) {
    std::cerr << "No measurements to compute statistics." << std::endl;
    return;
  }

  double mean = StatisticsCalculator::computeMean(measurementsForStats);
  double mode = StatisticsCalculator::computeMode(measurementsForStats);
  double median = StatisticsCalculator::computeMedian(measurementsForStats);

  std::cout << "Mean: " << mean << "\n";
  std::cout << "Mode: " << mode << "\n";
  std::cout << "Median: " << median << "\n";
}