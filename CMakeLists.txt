cmake_minimum_required(VERSION 3.25)
project(StackwellCommunityPlugins VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(STACKWELL_PLUGIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/dist/plugins")

function(stackwell_add_plugin target source output_name)
    add_library(${target} SHARED ${source})

    target_include_directories(${target}
        PRIVATE "${PROJECT_SOURCE_DIR}/sdk/include"
    )

    target_compile_definitions(${target}
        PRIVATE STACKWELL_PLUGIN_BUILD
    )

    set_target_properties(${target} PROPERTIES
        PREFIX ""
        OUTPUT_NAME "${output_name}"
        RUNTIME_OUTPUT_DIRECTORY "${STACKWELL_PLUGIN_OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${STACKWELL_PLUGIN_OUTPUT_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

    foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${config} "${STACKWELL_PLUGIN_OUTPUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY_${config} "${STACKWELL_PLUGIN_OUTPUT_DIR}"
            ARCHIVE_OUTPUT_DIRECTORY_${config} "${CMAKE_BINARY_DIR}/lib"
        )
    endforeach()
endfunction()

stackwell_add_plugin(
    stackwell_diagnostics
    plugins/diagnostics/diagnostics.cpp
    stackwell-diagnostics
)

stackwell_add_plugin(
    stackwell_minimal_example
    examples/minimal/minimal.cpp
    stackwell-minimal-example
)

if(MSVC)
    foreach(target stackwell_diagnostics stackwell_minimal_example)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    endforeach()
else()
    foreach(target stackwell_diagnostics stackwell_minimal_example)
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endforeach()
endif()
