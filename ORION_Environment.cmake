# This file must be called first when using the CMake framework,
# and sets various environment and project-wide settings.

# Detect Operating System
if(WIN32)
	set(__OS "win")
	add_definitions(-DIBM=1)
elseif(APPLE)
	set(__OS "osx")
	add_definitions(-DAPL=1)
else()
	set(__OS "lin")
	add_definitions(-DLIN=1)
endif()

# Detect Platform
if(${CMAKE_GENERATOR} MATCHES "Win64$")
	set(__PLATFORM "64")
else()
	set(__PLATFORM "32")
endif()

# Restrict configurations to Debug and Release only.
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Use solutions folders (if supported by generator, usually for IDEs)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Build to "build" directory in the source tree (temporary)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${__OS}_${__PLATFORM})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${__OS}_${__PLATFORM})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${__OS}_${__PLATFORM})

# Some dependency-specific forced options
add_definitions(-DGEOGRAPHICLIB_SHARED_LIB=0)

# Reference Qt5
if(WIN32)
	if(__PLATFORM STREQUAL "64")
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:\\Qt\\5.8\\msvc2013_64\\lib\\cmake")
	else()
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:\\Qt\\5.8\\msvc2013\\lib\\cmake")
	endif()
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets OpenGL)