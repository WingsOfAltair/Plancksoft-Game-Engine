cmake_minimum_required (VERSION 3.26)

# PROJECT NAME
project ("D3DTutorial")

# SETTING CMAKE OPTIONS
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

set(CMAKE_CXX_STANDARD 20)

# COMPILER VERSION CHECK
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(STATUS "Using MSVC Version, ${MSVC_VERSION}")
else()
	message(FATAL_ERROR "Compiler not supported")
endif()

# SETTING OUTPUT DIRECTORY
add_subdirectory ("Source/Runtime")
add_subdirectory ("Source/EditorApplication")