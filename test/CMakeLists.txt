set(target ${MP2_TESTS})

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.h*")

message(STATUS "Test target: ${target}")
message(STATUS "Test sources: ${srcs}")

add_executable(${target} ${srcs} ${hdrs})

target_include_directories(${target}
    PUBLIC
        ${googletest_SOURCE_DIR}/googletest/include
        ${googletest_SOURCE_DIR}/googlemock/include
    PRIVATE
        ${MP2_INCLUDE}
        ${ANTLR_ROOT}/include/antlr4-runtime
        ${MP2_INCLUDE}/parser
)

get_target_property(INCLUDE_DIRS ${target} INCLUDE_DIRECTORIES)
message(STATUS "Final include directories for ${target}: ${INCLUDE_DIRS}")

target_link_libraries(${target}
    PRIVATE
        gtest_main
        gtest
        ${MP2_LIBRARY}
)

target_compile_definitions(${target}
    PRIVATE
        $<$<BOOL:WIN32>:_CRT_SECURE_NO_WARNINGS>
        ${ANTLR_DEFINITION}
)

if(WIN32)
    target_compile_options(${target} PRIVATE /bigobj)
endif()

set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

add_test(NAME ${target} COMMAND ${target})