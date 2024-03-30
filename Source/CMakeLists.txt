cmake_minimum_required(VERSION 3.26)

# Include 3rd party libraries
include("${CMAKE_SOURCE_DIR}/Scripts/FetchLibraries.cmake")

# Populate 3rd party libraries
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)

# Create executable
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Source/*.h" "${CMAKE_SOURCE_DIR}/Source/*.cpp")
add_executable(PlancksoftGameEngine main.cpp ${SOURCES})

# Include directories and link libraries
target_include_directories(PlancksoftGameEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source")

target_link_libraries(PlancksoftGameEngine PRIVATE glfw)
target_link_libraries(PlancksoftGameEngine PRIVATE d3d11.lib dxgi.lib d3dcompiler.lib dxguid.lib)

if (stbi_POPULATED)
    target_include_directories(PlancksoftGameEngine PRIVATE "${stbi_SOURCE_DIR}")
    target_compile_definitions(PlancksoftGameEngine PUBLIC STB_IMAGE_IMPLEMENTATION=1)
endif()

# Debug and release flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(PlancksoftGameEngine PUBLIC PlancksoftGameEngineDebug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(PlancksoftGameEngine PUBLIC PlancksoftGameEngineRelease)
endif()

# Macro definitions
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(PlancksoftGameEngine PUBLIC RUNTIME_API=__declspec(dllexport))
    target_compile_definitions(PlancksoftGameEngine PUBLIC FORCEINLINE=__forceinline)
else()
    message(FATAL_ERROR "Unsupported Compiler")
endif()
