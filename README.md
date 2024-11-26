# Unitify


**Unitify** is a project aimed at handling and processing various unit measurements seamlessly. It provides tools for validating, converting, and processing measurements, with capabilities for generating statistical reports and handling measurement files programmatically.

## Features

- **Unit Conversion**: Seamless conversion between different units like length, mass, time, and volume.
- **Measurement Validation**: Ensures input measurements adhere to expected formats and ranges.
- **Statistics Calculation**: Generates statistical data from measurement files.
- **Report Generation**: Produces detailed reports based on processed measurements.
- **File Handling**: Reads, processes, and validates measurement files efficiently.

## Project Structure

### Core Components
- `include/` - Header files defining interfaces and utilities:
   - `Length.h`, `Mass.h`, `TimeUnit.h`, `Volume.h`: Units handling.
   - `Measurement.h`, `MeasurementValidator.h`: Handling and validating measurements.
   - `StatisticsCalculator.h`, `ReportGenerator.h`: Statistical computations and reporting.
   - `UnitConverter.h`: Conversion utilities for units.
   - 
- `src/` - Implementation files for the core logic:
  - E.g., `Measurement.cpp`, `UnitConverter.cpp`, `ReportGenerator.cpp`.
  
  - ### Additional Components
    - `testFileGenerator/` - Scripts and data for generating test files:
     - Includes `RandomMeasurementGenerator` and sample datasets like `year1measurements.txt`.
    - `measurement_report.txt` - Example or output report file.


### Build Files
- `CMakeLists.txt` - Build system configuration.
- `Doxyfile` - Documentation generation using Doxygen.

## Getting Started

### Prerequisites
- **C++ Compiler**: Requires a modern C++ compiler (C++17 or later recommended).
- **CMake**: For building the project.


### Building the Project
  - 1. Clone the repository:
        - ``` git clone https://github.com/milanfusco/Unitify.git ```
  - 2. Navigate to the project directory:
        - ```cd Unitify```
  - 3. Build using CMake:
  
       - ```mkdir build```
       
       - ```cd build```
       
       - ``` cmake ..```
       
       - ```make```


### Running the Application
Run the compiled executable: ```./Unitify```


### Testing
Test utilities and scripts are available under the `testFileGenerator` directory. 
  - Example usage:```./testFileGenerator/randomMeasurementGenerator```

## License
[MIT License](LICENSE)

## Acknowledgments
- Tools used: CMake, Doxygen.
- Inspired by the need for accurate measurement handling in scientific applications.
