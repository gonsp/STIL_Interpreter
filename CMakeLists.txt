cmake_minimum_required(VERSION 3.7)
project(STIL_Converter)
enable_testing()

# Add Antlr runtime
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/antlr/antlr-4.7-complete.jar)
set(ANTLR4CPP_GENERATED_SRC_DIR ${PROJECT_SOURCE_DIR}/src/parser)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/antlr)
include(Antlr4cpp)

# Generate parser source code for STIL grammar
set(PARSER_NAMESPACE parser)
antlr4cpp_process_grammar(generate_parser ${PARSER_NAMESPACE} STIL ${PROJECT_SOURCE_DIR}/grammar/STIL.g)

# Default config
add_custom_command(
        OUTPUT
        ${PROJECT_SOURCE_DIR}/src/interpreter/program/definitions/DefaultConfig.h
        COMMAND
        xxd -i grammar/stil.config src/interpreter/program/definitions/DefaultConfig.h
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        DEPENDS ${PROJECT_SOURCE_DIR}/grammar/stil.config
)

add_custom_target(
        generate_default_config
        DEPENDS ${PROJECT_SOURCE_DIR}/src/interpreter/program/definitions/DefaultConfig.h
)

# Compiler settings
set(CMAKE_CXX_STANDARD 11)
#set(GCC_COVERAGE_COMPILE_FLAGS "-v")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ReleaseWithAsserts)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_RELEASEWITHASSERTS "-Wall -O3")

# Source files
set(SOURCE_FILES
        src/main.cpp
        ${antlr4cpp_src_files_${PARSER_NAMESPACE}} src/interpreter/program/STILProgramVisitor.cpp src/interpreter/program/STILProgramVisitor.h src/interpreter/program/STILProgram.h src/interpreter/program/definitions/Signal.cpp src/interpreter/program/definitions/Signal.h src/interpreter/STILInterpreter.cpp src/interpreter/STILInterpreter.h src/interpreter/program/definitions/PatternBurst.cpp src/interpreter/program/definitions/PatternBurst.h src/interpreter/program/definitions/PatternContext.cpp src/interpreter/program/definitions/PatternContext.h src/interpreter/program/definitions/SignalGroup.cpp src/interpreter/program/definitions/SignalGroup.h src/interpreter/program/definitions/Identifiable.h src/interpreter/program/definitions/WaveFormTable.cpp src/interpreter/program/definitions/WaveFormTable.h src/interpreter/STILCustomVisitor.cpp src/interpreter/STILCustomVisitor.h src/interpreter/program/definitions/WaveForm.cpp src/interpreter/program/definitions/WaveForm.h src/interpreter/STILState.cpp src/interpreter/STILState.h src/interpreter/program/definitions/STILConfig.cpp src/interpreter/program/definitions/STILConfig.h src/parser/STILFilePreprocessor.cpp src/parser/STILFilePreprocessor.h)
include_directories(
        ${ANTLR4CPP_INCLUDE_DIRS}
        ${antlr4cpp_include_dirs_${PARSER_NAMESPACE}})
link_directories(
        ${ANTLR4CPP_LIBS})

# Target
add_executable(stil_converter ${SOURCE_FILES})
add_dependencies(stil_converter antlr4cpp generate_parser generate_default_config)
target_link_libraries(stil_converter ${antlr4_static})
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Install stil_converter
install(TARGETS stil_converter
        RUNTIME DESTINATION bin)
message(STATUS "To install stil_converter under /usr/local/bin, type: make install")

# Tests
# Make sure you install the executable before (make install)
# Make sure all the tests were when you run cmake.
# To run the tests, type "make test"
file(GLOB input_test_files "${PROJECT_SOURCE_DIR}/test/input_files/*.stil")
foreach(file ${input_test_files})
    get_filename_component(name ${file} NAME)
    add_test(
            NAME
            ${name}
            COMMAND
            python3 test_driver.py $<TARGET_FILE:stil_converter> ${name}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    )
endforeach()