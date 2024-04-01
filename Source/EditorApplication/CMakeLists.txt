cmake_minimum_required (VERSION 3.26)

# INCLUDE 3RD PARTY LIBRARIES
include("${CMAKE_SOURCE_DIR}/Scripts/FetchLibraries.cmake")

# CREATE EXECUTABLE
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Source/EditorApplication/*.h" "${CMAKE_SOURCE_DIR}/Source/EditorApplication/*.cpp")
source_group("EditorApplication" "${CMAKE_SOURCE_DIR}/Source/EditorApplication" ${SUBDIRECTORIES})
add_executable("EditorApplication" main.cpp ${SUBDIRECTORIES})

# INCLUDE DIRECTORIES AND LINK LIBRARIES
target_include_directories(EditorApplication PRIVATE "${CMAKE_SOURCE_DIR}/Source")

# LINK LIBRARIES
target_link_libraries(EditorApplication PRIVATE Runtime)

# MACRO DEFINITIONS
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_definitions(EditorApplication PUBLIC EDITOR_API=__declspec\(dllexport\))
else()
	message(FATAL_ERROR "Unsupported Compiler")
endif()

# ROOT DIRECTORY
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders/")
add_compile_definitions("WORKING_ROOT=${CMAKE_SOURCE_DIR}")