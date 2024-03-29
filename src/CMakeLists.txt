cmake_minimum_required(VERSION 3.6)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/utils")
set(MD5_SOURCE
	"${UTILS_DIR}/md5.cpp" "${UTILS_DIR}/md5.h"
)
set(ASSEMBUNNY_SOURCE
	"${UTILS_DIR}/assembunny.cpp" "${UTILS_DIR}/assembunny.h"
)

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
	"${MD5_SOURCE}"
)

set(DAY06_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day06")
set(DAY06_SOURCE
	"${DAY06_DIR}/day06.cpp"
)

set(DAY07_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day07")
set(DAY07_SOURCE
	"${DAY07_DIR}/day07.cpp"
)

set(DAY08_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day08")
set(DAY08_SOURCE
	"${DAY08_DIR}/day08.cpp"
)
option(WITH_DAY08_DISPLAY_PIXELS "Display result as pixels" OFF)
if(WITH_DAY08_DISPLAY_PIXELS)
	add_definitions(-DDAY08_DISPLAY_PIXELS)
endif()

set(DAY09_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day09")
set(DAY09_SOURCE
	"${DAY09_DIR}/day09.cpp"
)

set(DAY10_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day10")
set(DAY10_SOURCE
	"${DAY10_DIR}/day10.cpp"
)

set(DAY11_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day11")
set(DAY11_SOURCE
	"${DAY11_DIR}/day11.cpp"
)

set(DAY12_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day12")
set(DAY12_SOURCE
	"${DAY12_DIR}/day12.cpp"
	"${ASSEMBUNNY_SOURCE}"
)

set(DAY13_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day13")
set(DAY13_SOURCE
	"${DAY13_DIR}/day13.cpp"
)
option(WITH_DAY13_SHOW_DUNGEON "Show dungeon" OFF)
if(WITH_DAY13_SHOW_DUNGEON)
	add_definitions(-DDAY13_SHOW_DUNGEON)
endif()

set(DAY14_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day14")
set(DAY14_SOURCE
	"${DAY14_DIR}/day14.cpp"
	"${MD5_SOURCE}"
)

set(DAY15_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day15")
set(DAY15_SOURCE
	"${DAY15_DIR}/day15.cpp"
)

set(DAY16_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day16")
set(DAY16_SOURCE
	"${DAY16_DIR}/day16.cpp"
)

set(DAY17_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day17")
set(DAY17_SOURCE
	"${DAY17_DIR}/day17.cpp"
	"${MD5_SOURCE}"
)

set(DAY18_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day18")
set(DAY18_SOURCE
	"${DAY18_DIR}/day18.cpp"
)

set(DAY19_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day19")
set(DAY19_SOURCE
	"${DAY19_DIR}/day19.cpp"
)

set(DAY20_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day20")
set(DAY20_SOURCE
	"${DAY20_DIR}/day20.cpp"
)

set(DAY21_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day21")
set(DAY21_SOURCE
	"${DAY21_DIR}/day21.cpp"
	"${DAY21_DIR}/scrambler.cpp" "${DAY21_DIR}/scrambler.h"
)

set(DAY22_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day22")
set(DAY22_SOURCE
	"${DAY22_DIR}/day22.cpp"
)

set(DAY23_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day23")
set(DAY23_SOURCE
	"${DAY23_DIR}/day23.cpp"
	"${ASSEMBUNNY_SOURCE}"
)

set(DAY24_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day24")
set(DAY24_SOURCE
	"${DAY24_DIR}/day24.cpp"
)

set(DAY25_DIR "${CMAKE_CURRENT_SOURCE_DIR}/day25")
set(DAY25_SOURCE
	"${DAY25_DIR}/day25.cpp"
	"${ASSEMBUNNY_SOURCE}"
)

set(DAYS_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/days.h"
	"${DAY01_SOURCE}"
	"${DAY02_SOURCE}"
	"${DAY03_SOURCE}"
	"${DAY04_SOURCE}"
	"${DAY05_SOURCE}"
	"${DAY06_SOURCE}"
	"${DAY07_SOURCE}"
	"${DAY08_SOURCE}"
	"${DAY09_SOURCE}"
	"${DAY10_SOURCE}"
	"${DAY11_SOURCE}"
	"${DAY12_SOURCE}"
	"${DAY13_SOURCE}"
	"${DAY14_SOURCE}"
	"${DAY15_SOURCE}"
	"${DAY16_SOURCE}"
	"${DAY17_SOURCE}"
	"${DAY18_SOURCE}"
	"${DAY19_SOURCE}"
	"${DAY20_SOURCE}"
	"${DAY21_SOURCE}"
	"${DAY22_SOURCE}"
	"${DAY23_SOURCE}"
	"${DAY24_SOURCE}"
	"${DAY25_SOURCE}"
)
add_executable(aoc2016 
	"${CMAKE_CURRENT_SOURCE_DIR}/aoc2016.cpp"
	"${DAYS_SOURCE}"
)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	target_compile_options(aoc2016 PRIVATE "-march=native")
endif()
