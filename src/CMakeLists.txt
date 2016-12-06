cmake_minimum_required(VERSION 3.6)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(DAY01_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day01")
set(DAY01_SOURCE
	"${DAY01_DIR}/day01.cpp"
	"${DAY01_DIR}/position.h"
	"${DAY01_DIR}/direction.cpp" "${DAY01_DIR}/direction.h"
)

set(DAY02_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day02")
set(DAY02_SOURCE
	"${DAY02_DIR}/day02.cpp"
)

set(DAY03_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day03")
set(DAY03_SOURCE
	"${DAY03_DIR}/day03.cpp"
)

set(DAY04_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day04")
set(DAY04_SOURCE
	"${DAY04_DIR}/day04.cpp"
)

set(DAY05_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day05")
set(DAY05_SOURCE
	"${DAY05_DIR}/day05.cpp"
	"${DAY05_DIR}/md5.cpp" "${DAY05_DIR}/md5.h"
)

set(DAYS_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/days.h"
	"${DAY01_SOURCE}"
	"${DAY02_SOURCE}"
	"${DAY03_SOURCE}"
	"${DAY04_SOURCE}"
	"${DAY05_SOURCE}"
)
add_executable(aoc2017 
	"${CMAKE_CURRENT_SOURCE_DIR}/aoc2017.cpp"
	"${DAYS_SOURCE}"
)
