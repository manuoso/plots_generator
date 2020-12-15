cmake_minimum_required( VERSION 3.12 )

project( Test_Qt 
         VERSION 0.1 
         DESCRIPTION "Qt test"
         LANGUAGES C CXX)

# Executable
add_executable( Test_Qt )

# Compiler flags to VS
# if(WIN32)
# 	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# endif()

# ####################################################################################################
# Add
target_sources( Test_Qt PRIVATE src/main.cpp )

# Link library
target_link_libraries( Test_Qt PUBLIC multiplots ) 

# List of definitions variables
list( APPEND Test_Qt_DEFINITIONS "NDEBUG" )

# Compile definitions to target
target_compile_definitions( Test_Qt PUBLIC ${Test_Qt_DEFINITIONS} )
