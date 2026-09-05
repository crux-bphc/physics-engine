cmake_minimum_required(VERSION 3.30)

# CMake settings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE INTERNAL "")

project(physics-engine CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++26
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CPPM_SOURCES "src/*.cppm")

# std directory
set(LIBCXX_MODULE_DIR "/usr/share/libc++/v1")
set(LIBCXX_MODULE_PATH "${LIBCXX_MODULE_DIR}/std.cppm")

add_library(std_module)
target_sources(std_module
    PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES
    BASE_DIRS ${LIBCXX_MODULE_DIR}
    FILES ${LIBCXX_MODULE_PATH}
)

target_compile_options(std_module PRIVATE 
    -Wno-reserved-module-identifier 
    -Wno-reserved-identifier
)

# Executable
add_executable(physics-engine ${CPP_SOURCES})
target_link_libraries(physics-engine PRIVATE std_module)

# Enable modules
if(CPPM_SOURCES)
target_sources(physics-engine
  PUBLIC
        FILE_SET CXX_MODULES TYPE CXX_MODULES
        FILES ${CPPM_SOURCES}
      )
endif()


