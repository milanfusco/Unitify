/**
 * @file IOStreamHandler.h
 * @brief Handles input and output operations for Measurement objects.
 * 
 * This file contains the declaration of the IOStreamHandler class, which provides
 * static methods to facilitate reading and writing Measurement objects to and from
 * input and output streams.
*/

#ifndef IOSTREAMHANDLER_H
#define IOSTREAMHANDLER_H

#include "Measurement.h"
#include <iostream>

/**
 * @class IOStreamHandler
 * @headerfile IOStreamHandler.h
 * @brief Handles input and output operations for Measurement objects.
 * 
 * This class provides static methods to facilitate reading and writing 
 * Measurement objects to and from input and output streams.
 */
class IOStreamHandler {
public:
    /**
     * @brief Writes a Measurement object to an output stream.
     * 
     * This static method serializes a Measurement object and writes it to the output stream.
     * 
     * @param out The output stream to write to (e.g., std::cout).
     * @param m The Measurement object to be written to the stream.
     * @return A reference to the output stream after writing the Measurement object.
     */
    static std::ostream& writeToStream(std::ostream& out, const Measurement& m);

    /**
     * @brief Reads a Measurement object from an input stream.
     * 
     * This static method deserializes data from the input stream and populates a Measurement object.
     * 
     * @param in The input stream to read from (e.g., std::cin).
     * @param m The Measurement object to be populated with data from the stream.
     * @return A reference to the input stream after reading the Measurement object.
     */
    static std::istream& readFromStream(std::istream& in, Measurement& m);
};

#endif // IOSTREAMHANDLER_H