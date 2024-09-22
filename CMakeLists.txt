cmake_minimum_required(VERSION 3.10)
project(Unitify VERSION 0.1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing with CTest
include(CTest)
enable_testing()

#header files
file(GLOB HEADERS
    "./include/IOStreamHandler.h"
    "./include/Length.h"
    "./include/Mass.h"
    "./include/Measurement.h"
    "./include/MeasurementFileProcessor.h"
    "./include/MeasurementValidator.h"
    "./include/ReportGenerator.h"
    "./include/StatisticsCalculator.h"
    "./include/TimeUnit.h"
    "./include/UnitConverter.h"
    "./include/Units.h"
    "./include/CompoundUnit.h"
    "./include/Volume.h"
    
)

# Collect source files for the main application
file(GLOB MAIN_SRC
    "./src/main.cpp"
    "./src/Units.cpp"
    "./src/CompoundUnit.cpp"
    "./src/UnitConverter.cpp"
    "./src/UnitImplementations.cpp"
    "./src/Measurement.cpp"
    "./src/MeasurementFileProcessor.cpp"
    "./src/MeasurementValidator.cpp"
    "./src/IOStreamHandler.cpp"
    "./src/ReportGenerator.cpp"
    "./src/StatisticsCalculator.cpp")

# Collect source files for the tests (excluding main.cpp to avoid duplicate main symbols)
file(GLOB TEST_SRC
    "./src/TestUnitify.cpp"
    "./src/Units.cpp"
    "./src/UnitConverter.cpp"
    "./src/UnitImplementations.cpp"
    "./src/Measurement.cpp"
    "./src/MeasurementFileProcessor.cpp"
    "./src/MeasurementValidator.cpp"
    "./src/IOStreamHandler.cpp"
    "./src/ReportGenerator.cpp"
    "./src/StatisticsCalculator.cpp"
    "./src/CompoundUnit.cpp"
)

# Create the main application executable
add_executable(Unitify ${MAIN_SRC})

# Create the test executable
add_executable(TestUnitify ${TEST_SRC})

# Set include directories for both targets
target_include_directories(Unitify PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
target_include_directories(TestUnitify PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

# Add the test executable to CTest
add_test(NAME UnitTests COMMAND TestUnitify)

# Packaging settings (for cpack if needed)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
