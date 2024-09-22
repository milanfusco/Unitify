/**
 * @file IOStreamHandler.cpp
 * @brief Implementation of the IOStreamHandler class
 * @version 0.1
*/

#include "IOStreamHandler.h"
#include "MeasurementValidator.h"

std::ostream& IOStreamHandler::writeToStream(std::ostream& out, const Measurement& m) {
    out << m.getMagnitude() << " " << m.getUnit()->getName();
    return out;
}

std::istream& IOStreamHandler::readFromStream(std::istream& in, Measurement& m) {
    double magnitude;
    std::string unitStr;

    in >> magnitude >> unitStr;

    if (!MeasurementValidator::validateUnit(unitStr)) {
        throw std::invalid_argument("Invalid unit type.");
    }

    std::shared_ptr<Units> unit = Units::getUnitByName(unitStr); 
    m = Measurement(magnitude, std::move(unit));
    return in;
}