cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME polynom)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(MP2_LIBRARY "${PROJECT_NAME}")
set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(ANTLR_ROOT "C:/Users/1/gits/lab_polynom/antlr/antlr_4.13.2" CACHE PATH "Path to installed ANTLR runtime")
set(ANTLR_PARSER_DIR "C:/Users/1/gits/lab_polynom/antlr/parser" CACHE PATH "Path to generated ANTLR parser files")

option(ANTLR_USE_STATIC "Use static ANTLR runtime library" ON)

if(NOT EXISTS ${ANTLR_ROOT})
    message(FATAL_ERROR "ANTLR runtime not found at ${ANTLR_ROOT}. Please set correct ANTLR_ROOT path.")
else()
    message(STATUS "Found ANTLR runtime: ${ANTLR_ROOT}")
    
    if(ANTLR_USE_STATIC)
        set(ANTLR_LIB_NAMES 
            "antlr4-runtime.lib"
            "antlr4-runtime-static.lib"
            "libantlr4-runtime.a"
        )
        set(ANTLR_DEFINITION "ANTLR4CPP_STATIC")
    else()
        set(ANTLR_LIB_NAMES "antlr4-runtime.lib")
        set(ANTLR_DEFINITION "ANTLR4CPP_EXPORTS")
    endif()
    
    set(ANTLR_LIB_PATH "ANTLR_LIB_PATH-NOTFOUND")
    set(ANTLR_LIB_NAME "NOTFOUND")
    
    foreach(LIB_NAME ${ANTLR_LIB_NAMES})
        if(EXISTS "${ANTLR_ROOT}/lib/${LIB_NAME}")
            set(ANTLR_LIB_PATH "${ANTLR_ROOT}/lib/${LIB_NAME}")
            set(ANTLR_LIB_NAME ${LIB_NAME})
            break()
        endif()
    endforeach()
    
    if(NOT ANTLR_LIB_PATH)
        message(FATAL_ERROR "ANTLR library not found. Tried names: ${ANTLR_LIB_NAMES} in ${ANTLR_ROOT}/lib/")
    endif()
    
    message(STATUS "Found ANTLR library: ${ANTLR_LIB_PATH}")
    message(STATUS "Using ANTLR library name: ${ANTLR_LIB_NAME}")
    
    add_library(antlr4_runtime UNKNOWN IMPORTED)
    set_target_properties(antlr4_runtime PROPERTIES
        IMPORTED_LOCATION "${ANTLR_LIB_PATH}"
        INTERFACE_INCLUDE_DIRECTORIES "${ANTLR_ROOT}/include/antlr4-runtime"
    )
endif()

if(NOT EXISTS ${ANTLR_PARSER_DIR})
    message(FATAL_ERROR "ANTLR parser files not found at ${ANTLR_PARSER_DIR}. Please set correct ANTLR_PARSER_DIR path.")
else()
    message(STATUS "Found ANTLR parser files: ${ANTLR_PARSER_DIR}")
    
    file(GLOB ANTLR_PARSER_SRCS "${ANTLR_PARSER_DIR}/*.cpp")
    file(GLOB ANTLR_PARSER_HDRS "${ANTLR_PARSER_DIR}/*.h")
    
    file(COPY ${ANTLR_PARSER_HDRS} DESTINATION ${MP2_INCLUDE}/parser)
endif()

if(ANTLR_PARSER_SRCS)
    add_library(antlr_parser STATIC ${ANTLR_PARSER_SRCS})
    
    target_include_directories(antlr_parser
        PUBLIC
            ${ANTLR_PARSER_DIR}
        PRIVATE
            ${ANTLR_ROOT}/include/antlr4-runtime
    )
    
    target_compile_definitions(antlr_parser PRIVATE ${ANTLR_DEFINITION})
    
    if(WIN32)
        target_compile_options(antlr_parser PRIVATE /bigobj)
    endif()
endif()

add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(test)

message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}")
message(STATUS "======================================")
message(STATUS "")
message(STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "   ANTLR Runtime: ${ANTLR_ROOT}")
message(STATUS "   ANTLR Parser:  ${ANTLR_PARSER_DIR}")
message(STATUS "   ANTLR Library: ${ANTLR_LIB_NAME}")
message(STATUS "   ANTLR Definition: ${ANTLR_DEFINITION}")
message(STATUS "   Google Test:   ${googletest_SOURCE_DIR}")
message(STATUS "")