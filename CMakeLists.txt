cmake_minimum_required(VERSION 3.5.0)
project(cppatch CXX)

include(CMakeUtils.txt)

# OS tagging
if (UNIX)
  if (APPLE)
    c_message(STATUS "[OS] Apple flag ON" YELLOW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DAPPLE_MACRO=1")
  else()
    c_message(STATUS "[OS] Linux flag ON" YELLOW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DLINUX_MACRO=1")
  endif()
endif()


# cppatch constants
set(cppatch_VERSION_MAJOR 0)
set(cppatch_VERSION_MINOR 1)
set(cppatch_VERSION_PATCH 0)
set(cppatch_VERSION ${cppatch_VERSION_MAJOR}.${cppatch_VERSION_MINOR}.${cppatch_VERSION_PATCH})
set(CPPATCH_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# cppatch variables & functions
define_property(GLOBAL PROPERTY CPPATCH_LIBRARIES
  BRIEF_DOCS "List of cppatch libraries"
  FULL_DOCS "List of cppatch libraries"
  )
set_property(GLOBAL PROPERTY CPPATCH_LIBRARIES "")

# compilation options
option(ASAN OFF)
option(TSAN OFF)
option(MSAN OFF)
option(GTEST OFF)
option(DEBUG_MODE OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fblocks")

# includes
include_directories(${CPPATCH_INCLUDE})

if (DEBUG_MODE)
  c_message(STATUS "[OPTION] DEBUG mode activated" YELLOW)
  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG_MACRO=1")
endif()

# project sources
add_subdirectory(src)

# testing
if (GTEST)
  c_message(STATUS "[OPTION] GTESTING compilation activated" YELLOW)
  add_subdirectory(tests)
endif()


# end
c_message(STATUS "Preparing compilation for cppatch version ${Bold}${cppatch_VERSION}" GREEN)
