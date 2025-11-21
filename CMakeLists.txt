# Start by setting the version of CMAKE
cmake_minimum_required(VERSION 3.22.1)

set (CMAKE_CXX_STANDARD 11)

# Give the project a name
project(bank_app)

# Include the src directory so CMAKE compiles it
add_subdirectory(src)
add_subdirectory(test)