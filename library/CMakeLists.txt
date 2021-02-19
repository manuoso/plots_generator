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
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/../external/qt/qcustomplot.cpp")
file(GLOB_RECURSE HDR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.inl" "${CMAKE_CURRENT_SOURCE_DIR}/../external/qt/*.h")

add_library(${PROJECT_NAME} SHARED ${HDR_FILES} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories( ${PROJECT_NAME}  PUBLIC ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})

# Link libraries
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

##################################################
######    Installation.                   ########
##################################################
include(CMakePackageConfigHelpers)

if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif() 

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets
	COMPONENT ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(EXPORT ${PROJECT_NAME}-targets
	FILE "${PROJECT_NAME}-targets.cmake"
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION lib/cmake/${PROJECT_NAME}
	COMPONENT ${PROJECT_NAME}
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/${PROJECT_NAME}-config.cmake.in"
	"${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	@ONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${version}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
    COMPONENT ${PROJECT_NAME}
)

# DESTINATION will be automatically prefixed by ${CMAKE_INSTALL_PREFIX}
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    COMPONENT ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# uninstall target 
if(NOT TARGET uninstall) 
    configure_file( 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/cmake_uninstall.cmake.in" 
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" 
        @ONLY) 
 
    add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake) 
endif() 