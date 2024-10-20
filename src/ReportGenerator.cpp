/**
 * @file ReportGenerator.cpp
 * @brief Implementation of the ReportGenerator class
 *
 * This file contains the implementation of the ReportGenerator class, which
 * provides methods for generating reports from a collection of Measurement
 * objects. It supports generating both text-based and CSV-formatted reports,
 * allowing for flexible presentation of measurement data.
 *
 * @version 0.1
 */

#include "ReportGenerator.h"
#include <sstream>
#include <iomanip>

std::string ReportGenerator::generateTextReport(
    const std::vector<Measurement>& measurements) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2);
  for (const auto& m : measurements) {
    oss << m.getMagnitude() << " " << m.getUnit()->getName() << "\n";
  }
  return oss.str();
}

std::string ReportGenerator::generateCSVReport(
    const std::vector<Measurement>& measurements) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2);
  oss << "Magnitude,Unit\n";
  for (const auto& m : measurements) {
    oss << m.getMagnitude() << "," << m.getUnit()->getName() << "\n";
  }
  return oss.str();
}