cmake_minimum_required( VERSION 3.12 )

project( Multiplots_Qt 
         VERSION 0.1 
         DESCRIPTION "Qt plots main"
         LANGUAGES C CXX)

# Executable
add_executable( Multiplots_Qt )

# Compiler flags to VS
# if(WIN32)
# 	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# endif()

# ####################################################################################################
# Add
target_sources( Multiplots_Qt PRIVATE src/main.cpp )

# Link library
target_link_libraries( Multiplots_Qt PUBLIC multiplots ) 

# List of definitions variables
list( APPEND Multiplots_Qt_DEFINITIONS "NDEBUG" )

# Compile definitions to target
target_compile_definitions( Multiplots_Qt PUBLIC ${Multiplots_Qt_DEFINITIONS} )
