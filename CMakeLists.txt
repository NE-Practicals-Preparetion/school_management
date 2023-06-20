cmake_minimum_required(VERSION 3.10)
project(school_management_system)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(include models)

# Add the source files
set(SOURCES
        src/main.cpp
        src/database.cpp
        models/Student.cpp)

# Add the executable target
add_executable(school_management_system ${SOURCES})

# Link libraries
target_link_libraries(school_management_system mysqlcppconn)
