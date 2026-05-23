file(GLOB samples_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(sample_filename ${samples_list})
    get_filename_component(sample ${sample_filename} NAME_WE)

    add_executable(${sample} ${sample_filename})

    target_link_libraries(${sample}
        PRIVATE
            ${MP2_LIBRARY}
    )
    
    target_include_directories(${sample}
        PRIVATE
            ${MP2_INCLUDE}
            ${ANTLR_ROOT}/include/antlr4-runtime
            ${MP2_INCLUDE}/parser
    )
    
    target_compile_definitions(${sample}
        PRIVATE
            $<$<BOOL:WIN32>:_CRT_SECURE_NO_WARNINGS>
            ${ANTLR_DEFINITION}
    )

    if(WIN32)
        target_compile_options(${sample} PRIVATE /bigobj)
    endif()
    
    set_target_properties(${sample} PROPERTIES
        OUTPUT_NAME "${sample}"
        PROJECT_LABEL "${sample}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
    )
    
    if(WIN32 AND NOT ANTLR_USE_STATIC)
        set(ANTLR_DLL_PATH "${ANTLR_ROOT}/bin/antlr4-runtime.dll")
        
        if(NOT EXISTS ${ANTLR_DLL_PATH})
            set(ANTLR_DLL_PATH "${ANTLR_ROOT}/bin/${CMAKE_BUILD_TYPE}/antlr4-runtime.dll")
        endif()
        
        if(EXISTS ${ANTLR_DLL_PATH})
            add_custom_command(TARGET ${sample} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${ANTLR_DLL_PATH}
                    $<TARGET_FILE_DIR:${sample}>
                COMMENT "Copying ANTLR runtime DLL to ${sample} directory"
            )
            message(STATUS "Will copy ANTLR DLL from ${ANTLR_DLL_PATH} for ${sample}")
        else()
            message(WARNING "ANTLR DLL not found at ${ANTLR_DLL_PATH}")
        endif()
    endif()
    
    message(STATUS "Added sample: ${sample}")
    
endforeach()

message(STATUS "Configured ${CMAKE_CURRENT_LIST_FILE} with ${samples_list} samples")