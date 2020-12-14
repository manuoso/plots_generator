cmake_minimum_required( VERSION 3.12 )

project( Test_Matplotlib 
         VERSION 0.1 
         DESCRIPTION "Matplotlib test"
         LANGUAGES C CXX)

# Executable
add_executable( Test_Matplotlib )

# Compiler flags to VS
# if(WIN32)
# 	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# endif()

# ####################################################################################################
# Add
target_sources( Test_Matplotlib PRIVATE src/main.cpp )

# Link library
target_link_libraries( Test_Matplotlib PUBLIC multiplots ) 

# List of definitions variables
list( APPEND Test_Matplotlib_DEFINITIONS "NDEBUG" )

# Compile definitions to target
target_compile_definitions( Test_Matplotlib PUBLIC ${Test_Matplotlib_DEFINITIONS} )
