cmake_minimum_required( VERSION 3.12 )

project( multiplots 
         VERSION 0.1 
         DESCRIPTION "Multi plots generators"
         LANGUAGES C CXX)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
       FORCE )
endif()

# Find dependencies
find_package(Python2 COMPONENTS Development NumPy)

## Load Qt5
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Core REQUIRED)

MESSAGE( STATUS "Using Qt5")

set(QT5_LIBRARIES Qt5::Widgets Qt5::PrintSupport Qt5::Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Library

# Sources
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE HDR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.inl")

add_library(${PROJECT_NAME} STATIC ${HDR_FILES} ${SRC_FILES})

target_sources( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../external/qt/qcustomplot.cpp")

# Include directories
target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_include_directories( ${PROJECT_NAME}  PUBLIC ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})

target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../external/matplotlib" ) 
target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../external/qt" ) 

# Link libraries
target_link_libraries( ${PROJECT_NAME} LINK_PUBLIC Python2::Python Python2::NumPy)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${QT5_LIBRARIES})

if(UNIX)
	target_link_libraries( ${PROJECT_NAME} LINK_PUBLIC pthread dl boost_system)
elseif(WIN32)

endif()

# List of definitions variables
list( APPEND MULTIPLOTS_DEFINITIONS "NDEBUG" )
list( APPEND MULTIPLOTS_DEFINITIONS "pthread" )

message(STATUS "MULTIPLOTS_DEFINITIONS: ${MULTIPLOTS_DEFINITIONS}")

# Compile definitions to target
target_compile_definitions( ${PROJECT_NAME} PUBLIC ${MULTIPLOTS_DEFINITIONS})