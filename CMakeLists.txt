cmake_minimum_required(VERSION 3.10)
project(Unitify VERSION 0.1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing if necessary
include(CTest)
enable_testing()

# Use GLOB to collect all source files
file(GLOB TARGET_SRC "./src/*.cpp")

# Create the executable with a meaningful name
add_executable(Unitify ${TARGET_SRC})

# Set include directories for this target
target_include_directories(Unitify PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

# Link libraries if necessary 
# target_link_libraries(new_project_main PRIVATE <library_name>)

# Packaging settings (for cpack if needed)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
