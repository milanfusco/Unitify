/**
 * @file randomMeasurementGenerator.cpp
 * @brief Program to generate a file with random measurement expressions.
 * 
 * This program generates a file with random measurement expressions.
 * Each line in the file contains three magnitudes and units, separated by operators.
 * The magnitudes are random double values between 1 and 1000.
 * The units are randomly chosen from predefined categories (length, mass, volume, time).
 * The operators are randomly chosen from a list of operators (+, -, *, /).
 * The file is generated with 687 lines. (A Martian year is 687 Earth days.)
 * 
 * @version 0.1
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

/**
 * @brief Generate a random double value between 1 and 1000.
 * 
 * @return Random double value between 1 and 1000.
 */
double getRandomMagnitude() {
    return (static_cast<double>(rand()) / RAND_MAX) * 999 + 1;
}

/**
 * @brief Get a random element from a vector.
 * 
 * @tparam T Type of the vector elements.
 * @param vec Vector of elements.
 * @return Random element from the vector.
 */
template <typename T>
T getRandomElement(const std::vector<T>& vec) {
    int index = rand() % vec.size();
    return vec[index];
}

/**
 * @brief Main function to generate the file with random measurement expressions.
 * 
 * @return Program exit status.
 */
int main() {
    std::ofstream file("generated_measurements.txt");

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // List of categorized units
    std::vector<std::string> lengthUnits = {"millimeters", "centimeters", "meters", "kilometers"};
    std::vector<std::string> massUnits = {"centigrams", "grams", "kilograms", "milligrams"};
    std::vector<std::string> volumeUnits = {"milliliters", "centiliters", "liters", "kiloliters"};
    std::vector<std::string> timeUnits = {"seconds", "minutes", "hours"};

    // List of operators
    std::vector<std::string> operators = {"+", "-", "*", "/"};

    if (file.is_open()) {
        // Generate 687 lines
        for (int i = 0; i < 687; ++i) {
            double magnitude1 = getRandomMagnitude();
            double magnitude2 = getRandomMagnitude();
            double magnitude3 = getRandomMagnitude();
            std::string operator1 = getRandomElement(operators);
            std::string operator2 = getRandomElement(operators);

            std::string unit1, unit2, unit3;

            // Choose compatible units based on the operator
            if (operator1 == "+" || operator1 == "-") {
                // For addition and subtraction, units must be of the same type
                int unitType = rand() % 4;  // Randomly select unit category: 0=length, 1=mass, 2=volume, 3=time

                switch (unitType) {
                    case 0: // Length
                        unit1 = getRandomElement(lengthUnits);
                        unit2 = getRandomElement(lengthUnits);
                        break;
                    case 1: // Mass
                        unit1 = getRandomElement(massUnits);
                        unit2 = getRandomElement(massUnits);
                        break;
                    case 2: // Volume
                        unit1 = getRandomElement(volumeUnits);
                        unit2 = getRandomElement(volumeUnits);
                        break;
                    case 3: // Time
                        unit1 = getRandomElement(timeUnits);
                        unit2 = getRandomElement(timeUnits);
                        break;
                }
            } else {
                // For multiplication and division, units can be different
                unit1 = getRandomElement(lengthUnits);
                unit2 = getRandomElement(massUnits);  // Example: you can multiply length and mass
            }

            // Choose a random unit for the third magnitude (operator2 can be anything)
            unit3 = getRandomElement(lengthUnits);  // You can change this to match your specific use case

            // Write the line to the file (using spaces instead of commas)
            file << magnitude1 << " " << unit1 << " " << operator1 << " "
                 << magnitude2 << " " << unit2 << " " << operator2 << " "
                 << magnitude3 << " " << unit3 << "\n";
        }

        file.close();
        std::cout << "File 'generated_measurements.txt' generated successfully." << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }

    return 0;
}
