# Copyright AStarship <https://astarship.net>.
cmake_minimum_required (VERSION 3.10)
project (CrabsBed)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CRABS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ASCIICrabs)

add_executable(CrabsBed _Seams/_Main.cpp)

target_include_directories(CrabsBed PRIVATE
  "${PROJECT_SOURCE_DIR}/_Seams"
  "${PROJECT_SOURCE_DIR}"
  "${CRABS_DIR}"
  "${CRABS_DIR}/_Seams")

# Seam selection: CORE (default, runs the unit tests) or RELEASE (the demo).
# Override on the command line: -DCRABS_BED_SEAM=CRABS_BED_RELEASE
set (CRABS_BED_SEAM "CRABS_BED_CORE" CACHE STRING "CrabsBed seam: CRABS_BED_CORE or CRABS_BED_RELEASE")
target_compile_definitions(CrabsBed PRIVATE CRABS_BED_SEAM=${CRABS_BED_SEAM})
