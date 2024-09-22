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
#include <variant>
#include <vector>
#include "CompoundUnit.h"
#include "IOStreamHandler.h"
#include "Measurement.h"
#include "ReportGenerator.h"
#include "StatisticsCalculator.h"

/**
 * @namespace anonymous (not the hacktivist group :P)
 * @brief Anonymous namespace to encapsulate the MeasurementOrOperator type and
 * validOperators set.
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
  switch (op) {
    case '+':
    case '-':
      return (op == '+') ? left + right : left - right;

    case '*':
    case '/': {
      if (left.getUnit()->getType() == right.getUnit()->getType()) {
        left.ensureSameType(right);
        return (op == '*')
                   ? left * right
                   : left / right;  ///> division by zero is handled by
                                    ///> Measurement class overloaded operator
      } else {
        std::vector<std::shared_ptr<Units> > units = {
            std::shared_ptr<Units>(left.getUnit()),
            std::shared_ptr<Units>(right.getUnit())};
        std::vector<char> operators;
        std::shared_ptr<Units> compoundUnit =
            std::make_shared<CompoundUnit>(units, operators);

        double newMagnitude = (op == '*')
                                  ? left.getMagnitude() * right.getMagnitude()
                                  : left.getMagnitude() / right.getMagnitude();
        return Measurement(newMagnitude, compoundUnit);
      }
    }
    default:
      throw std::invalid_argument("Invalid operator: " + std::string(1, op));
  }
}

Measurement MeasurementFileProcessor::processOperatorsWithPEMDAS(
    const std::vector<Measurement>& measurements,
    const std::vector<char>& operators) {
  std::stack<Measurement> operandStack;
  std::stack<char> operatorStack;

  size_t measurementIndex = 0;
  size_t operatorIndex = 0;

  while (measurementIndex < measurements.size()) {
    operandStack.push(measurements[measurementIndex++]);

    if (operatorIndex < operators.size()) {
      char currentOperator = operators[operatorIndex++];

      while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >=
                                           getPrecedence(currentOperator)) {
        char topOp = operatorStack.top();
        operatorStack.pop();

        Measurement right = operandStack.top();
        operandStack.pop();
        Measurement left = operandStack.top();
        operandStack.pop();

        operandStack.push(applyOperation(left, right, topOp));
      }

      operatorStack.push(currentOperator);
    }
  }

  while (!operatorStack.empty()) {
    char topOp = operatorStack.top();
    operatorStack.pop();

    Measurement right = operandStack.top();
    operandStack.pop();
    Measurement left = operandStack.top();
    operandStack.pop();

    operandStack.push(applyOperation(left, right, topOp));
  }

  return operandStack.top();
}

void MeasurementFileProcessor::readFile() {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << fileName << std::endl;
    return;
  }

  std::string line;
  std::vector<Measurement> measurements;
  std::vector<char> operators;

  while (getline(file, line)) {
    std::stringstream ss(line);
    double magnitude;
    std::string unitStr, operatorStr;

    ss >> magnitude >> unitStr >> operatorStr;

    std::shared_ptr<Units> unit = Units::getUnitByName(unitStr);
    if (!unit) {
      throw std::invalid_argument("Invalid unit: " + unitStr);
    }

    Measurement measurement(magnitude, unit);
    measurements.push_back(measurement);

    if (!operatorStr.empty() && isValidOperator(operatorStr)) {
      operators.push_back(operatorStr[0]);
    }
  }
  Measurement result = processOperatorsWithPEMDAS(measurements, operators);

  std::cout << "Result: " << result.getMagnitude() << " "
            << result.getUnit()->getName() << std::endl;

  file.close();
}

void MeasurementFileProcessor::sortMeasurements() {
  if (!isFileLoaded) {
    std::cerr << "No file loaded to process." << std::endl;
    return;
  }

  // Extract Measurements and sort them
  std::vector<Measurement> measurementsToSort;

  for (const auto& measurementLine : measurementsList) {
    for (const auto& element : measurementLine) {
      if (std::holds_alternative<Measurement>(element)) {
        measurementsToSort.push_back(std::get<Measurement>(element));
      }
    }
  }

  // Sort the extracted measurements based on magnitude
  std::sort(measurementsToSort.begin(), measurementsToSort.end(),
            [](const Measurement& a, const Measurement& b) {
              return a.getMagnitude() < b.getMagnitude();
            });

  // Output sorted measurements
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
  for (const auto& measurementLine : measurementsList) {
    for (const auto& element : measurementLine) {
      if (std::holds_alternative<Measurement>(element)) {
        const Measurement& m = std::get<Measurement>(element);
        std::cout << i << ". " << m.getMagnitude() << " "
                  << m.getUnit()->getName() << "\n";
        i++;
      }
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

  for (const auto& measurementLine : measurementsList) {
    for (const auto& element : measurementLine) {
      if (std::holds_alternative<Measurement>(element)) {
        const Measurement& m = std::get<Measurement>(element);
        std::ostringstream oss;
        oss << m.getMagnitude() << " " << m.getUnit()->getName();
        reportLines.push_back(oss.str());
      }
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

  for (const auto& measurementLine : measurementsList) {
    for (const auto& element : measurementLine) {
      if (std::holds_alternative<Measurement>(element)) {
        sortedMeasurements.push_back(std::get<Measurement>(element));
      }
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

  for (const auto& measurementLine : measurementsList) {
    for (const auto& element : measurementLine) {
      if (std::holds_alternative<Measurement>(element)) {
        measurementsForStats.push_back(std::get<Measurement>(element));
      }
    }
  }

  if (measurementsForStats.empty()) {
    std::cerr << "No valid measurements to compute statistics." << std::endl;
    return;
  }

  double mean = StatisticsCalculator::computeMean(measurementsForStats);
  double mode = StatisticsCalculator::computeMode(measurementsForStats);
  double median = StatisticsCalculator::computeMedian(measurementsForStats);

  std::cout << "Mean: " << mean << "\n";
  std::cout << "Mode: " << mode << "\n";
  std::cout << "Median: " << median << "\n";
}