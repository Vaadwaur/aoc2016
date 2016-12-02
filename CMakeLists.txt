cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME_STR aoc2017)
project(${PROJECT_NAME_STR} CXX)
# Common parameters for all subprojects stuff goes here

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(SEND_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_COLOR_MAKEFILE ON)

set(MY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY} )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MY_OUTPUT_DIRECTORY} )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MY_OUTPUT_DIRECTORY} )
#    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MY_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MY_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Remove 'lib' prefix for shared libraries on Windows
#if(WIN32)
#	set(CMAKE_SHARED_LIBRARY_PREFIX "")
#endif(WIN32)

if(MSVC)
	add_definitions(-DNOMINMAX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /std:c++latest /permissive-")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O0 -g -pedantic -Wextra")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -pedantic -Wextra")
endif(MSVC)

# When done tweaking, configure subprojects.
# NOTE: Order matters! The most independent ones should go first.
add_subdirectory(src)
