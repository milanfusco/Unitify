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
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "CompoundUnit.h"
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

std::optional<Measurement> MeasurementFileProcessor::applyOperation(
    const Measurement& left,
    const Measurement& right,
    char op) {
  try {
    // Check if units are the same (before converting to compound unit)
    if (left.getUnit()->getName() == right.getUnit()->getName()) {
      // Convert both to base units
      Measurement leftBase = UnitConverter::convertToBaseUnit(left);
      Measurement rightBase = UnitConverter::convertToBaseUnit(right);

      // Perform the arithmetic in base units
      double newMagnitude =
          (op == '*') ? leftBase.getMagnitude() * rightBase.getMagnitude()
                      : leftBase.getMagnitude() / rightBase.getMagnitude();

      // Return result in a single base unit
      return Measurement(newMagnitude, leftBase.getUnit());
    }

    // If units are different, proceed with compound unit construction
    std::vector<std::shared_ptr<Units>> units;
    std::vector<char> operators;

    // Handle left-hand side units
    std::shared_ptr<CompoundUnit> leftCompoundUnit =
        std::dynamic_pointer_cast<CompoundUnit>(left.getUnit());
    if (leftCompoundUnit) {
      units = leftCompoundUnit->getUnits();
      operators = leftCompoundUnit->getOperators();
    } else {
      units.push_back(left.getUnit());  // Treat as a single unit
    }

    // Handle right-hand side units
    std::shared_ptr<CompoundUnit> rightCompoundUnit =
        std::dynamic_pointer_cast<CompoundUnit>(right.getUnit());
    if (rightCompoundUnit) {
      units.insert(units.end(), rightCompoundUnit->getUnits().begin(),
                   rightCompoundUnit->getUnits().end());
    } else {
      units.push_back(right.getUnit());
    }

    // Add the current operator between the left and right units
    operators.push_back(op);

    // Ensure the operator count matches units count - 1
    if (operators.size() != units.size() - 1) {
      throw std::logic_error(
          "Number of operators does not match the number of units.");
    }

    // Create the compound unit
    std::shared_ptr<CompoundUnit> newCompoundUnit =
        std::make_shared<CompoundUnit>(units, operators);

    std::cout << "Constructed Compound Unit: "
              << newCompoundUnit->getCompoundName() << std::endl;

    // Perform the arithmetic operation for different units
    double newMagnitude = (op == '*')
                              ? left.getMagnitude() * right.getMagnitude()
                              : left.getMagnitude() / right.getMagnitude();

    // Return result with a compound unit
    return Measurement(newMagnitude, newCompoundUnit);

  } catch (const std::invalid_argument& e) {
    std::cerr << "Operation error: " << e.what() << std::endl;
    return std::nullopt;
  }
}

std::optional<Measurement> MeasurementFileProcessor::processOperatorsWithPEMDAS(
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
          return std::nullopt;
        }
      }
      operatorStack.push(currentOperator);
    }
  }

  while (!operatorStack.empty()) {
    if (!applyTopOperator(operandStack, operatorStack)) {
      return std::nullopt;
    }
  }

  return operandStack.empty() ? std::nullopt
                              : std::optional<Measurement>{operandStack.top()};
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

  std::optional<Measurement> result = applyOperation(left, right, op);
  if (!result)
    return false;
  operandStack.push(result.value());
  return true;
}

void MeasurementFileProcessor::readFile() {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << fileName << std::endl;
    return;
  }

  std::string line;
  int lineNum = 1;

  while (getline(file, line)) {
    std::vector<Measurement> measurements;
    std::vector<char> operators;            

    processLine(line, lineNum++, measurements, operators);

    std::optional<Measurement> result =
        processOperatorsWithPEMDAS(measurements, operators);

    if (result) {
      std::cout << "Result: " << result->getMagnitude() << " "
                << result->getUnit()->getName() << std::endl;
    } else {
      std::cerr << "Error: Invalid result, operation failed." << std::endl;
    }

    measurementsList.push_back(measurements);
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