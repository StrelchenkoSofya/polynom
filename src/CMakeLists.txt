set(target ${MP2_LIBRARY})

file(GLOB_RECURSE srcs "*.cpp")
file(GLOB_RECURSE private_hdrs "*.h" "*.hpp")
file(GLOB_RECURSE public_hdrs "${MP2_INCLUDE}/*.h" "${MP2_INCLUDE}/*.hpp")

file(GLOB_RECURSE parser_hdrs "${MP2_INCLUDE}/parser/*.h")

message(STATUS "Library target: ${target}")
message(STATUS "Source files: ${srcs}")
message(STATUS "Private headers: ${private_hdrs}")
message(STATUS "Public headers: ${public_hdrs}")
message(STATUS "Parser headers: ${parser_hdrs}")

source_group("Source Files" FILES ${srcs})
source_group("Private Headers" FILES ${private_hdrs})
source_group("Public Headers" FILES ${public_hdrs})
source_group("Generated Parser Headers" FILES ${parser_hdrs})

add_library(${target} STATIC 
    ${srcs} 
    ${private_hdrs}
    ${public_hdrs}
    ${parser_hdrs}
)

target_include_directories(${target}
    PUBLIC
        ${MP2_INCLUDE} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ANTLR_ROOT}/include/antlr4-runtime
        ${MP2_INCLUDE}/parser 
)

if(TARGET antlr_parser)
    target_link_libraries(${target} 
        PUBLIC
            antlr_parser
    )
endif()

if(TARGET antlr4_runtime)
    target_link_libraries(${target} 
        PUBLIC
            antlr4_runtime
    )
endif()

target_compile_definitions(${target}
    PRIVATE
        ${ANTLR_DEFINITION}
)

if(WIN32)
    target_compile_options(${target} PRIVATE /bigobj)
    target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(MSVC)
    set_target_properties(${target} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        LINKER_LANGUAGE "CXX"
    )
endif()