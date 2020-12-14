cmake_minimum_required( VERSION 3.12 )

project( plots_generator
         VERSION 0.1
         DESCRIPTION "General class that generates the diferents plots that you want to visualize" )

 # Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# C++14
set(CMAKE_CXX_STANDARD 14)

add_definitions ( -DGLOBALPATH="${CMAKE_CURRENT_SOURCE_DIR}" )

# Make external libraries globally available.
#if(WIN32)
#    add_subdirectory( external )
#endif()

# Create targets for building the (local) libraries.
add_subdirectory( library )

# Create the targets for the entire app.
add_subdirectory( examples )
