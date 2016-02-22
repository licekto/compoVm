cmake_minimum_required(VERSION 3.3)
project(compoVm)

# Directories creation
#------------------------------
file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY doc)
file(MAKE_DIRECTORY build)
file(MAKE_DIRECTORY lib)
file(MAKE_DIRECTORY src/generated)
file(MAKE_DIRECTORY include/generated)
#------------------------------

# C++ flags
#------------------------------
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -std=c++11 -pedantic -Wall -Wextra -fno-inline -O0 -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wunreachable-code -Wuninitialized")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -pedantic -Wall -Wextra -Weffc++ -O3")
#------------------------------

# Include directories
#------------------------------
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/generated ${CMAKE_CURRENT_SOURCE_DIR}/include/nodes ${CMAKE_CURRENT_SOURCE_DIR}/include/parser ${CMAKE_CURRENT_SOURCE_DIR}/include/core)
include_directories(${INCLUDE_DIRS})
#------------------------------

# Tests and statistics
#------------------------------
# Enable tests
enable_testing()

# Memory check
set(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind")
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-reachable=yes --track-origins=yes --xml=yes --xml-file=valgrind.xml")
include(CTest)

# OCLint
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#------------------------------

# Boost settings
#------------------------------
set(Boost_ADDITIONAL_VERSIONS "1.60" "1.60.0")
find_package(Boost 1.60 REQUIRED COMPONENTS log log_setup thread date_time filesystem system unit_test_framework)
find_package(Threads)

if(Boost_FOUND)
  include_directories( ${Boost_INCLUDE_DIRS} )
  link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
else(Boost_FOUND)
  message(FATAL_ERROR "Cannot build Quantib Boost Log test without Boost. Please set Boost_DIR.")
endif(Boost_FOUND)
#------------------------------

# Bison settings
#------------------------------
find_package(BISON REQUIRED)
set(BISON_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/generated/parser.h)
set(BISON_SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/grammar.y)
if (BISON_FOUND)
    add_custom_command(
            OUTPUT ${BISON_OUTPUT}
            COMMAND ${BISON_EXECUTABLE}
            --token-table
            --no-lines
            --output=${CMAKE_CURRENT_SOURCE_DIR}/src/generated/parser.cpp
            --defines=${CMAKE_CURRENT_SOURCE_DIR}/include/generated/parser.h
            ${BISON_SPEC_FILE}
            DEPENDS ${BISON_SPEC_FILE}
            COMMENT "Generating ${BisonOutput}"
            VERBATIM
    )
endif ()
#------------------------------

# Flex settings
#------------------------------
find_package(FLEX REQUIRED)
set(FLEX_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/lexer.cpp)
set(FLEX_SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/grammar.l)
if (FLEX_FOUND)
    add_custom_command(
            OUTPUT ${FLEX_OUTPUT}
            COMMAND ${FLEX_EXECUTABLE}
            --noline
            --nounistd
            --outfile=${CMAKE_CURRENT_SOURCE_DIR}/src/generated/lexer.cpp
            ${FLEX_SPEC_FILE}
            DEPENDS ${FLEX_SPEC_FILE}
            COMMENT "Generating ${FlexOutput}"
            VERBATIM
    )
endif ()
#------------------------------

# Files preparation
#------------------------------
FILE(GLOB PARSER_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/parser/*.cpp)
FILE(GLOB NODES_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/nodes/*.cpp)
FILE(GLOB GENERATED_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/generated/*.cpp)
FILE(GLOB CORE_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/core/*.cpp)
FILE(GLOB MAIN_FILE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/main.cpp)

set(SOURCE_FILES_ALL ${PARSER_SOURCE_FILES} ${NODES_SOURCE_FILES} ${GENERATED_SOURCE_FILES} ${CORE_SOURCE_FILES} ${BISON_OUTPUT} ${FLEX_OUTPUT})

FILE(GLOB TEST_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" test/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#------------------------------

add_library(OBJECT_FILES OBJECT ${SOURCE_FILES_ALL})

# Executables preparation
#------------------------------
# Main binary
add_executable(compoVm ${MAIN_FILE} $<TARGET_OBJECTS:OBJECT_FILES>)
target_link_libraries(  compoVm
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                        ${Boost_LOG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT} )
target_compile_definitions(compoVm PRIVATE "BOOST_LOG_DYN_LINK=1")

# Tests
add_executable(tests ${TEST_FILES} $<TARGET_OBJECTS:OBJECT_FILES>)
target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(tests PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(tests ${nodes} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME compoTest COMMAND tests)
#------------------------------

# Doxygen
#------------------------------
FIND_PACKAGE(Doxygen)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    IF (DOXYGEN_FOUND)

        SET(DOXYGEN_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/resources/Doxyfile")
        SET(DOXYGEN_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/")

        ADD_CUSTOM_COMMAND(
            OUTPUT ${DOXYGEN_OUTPUT}
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${DOXYGEN_INPUT}    )

        ADD_CUSTOM_TARGET(doc ALL DEPENDS ${DOXYGEN_OUTPUT}  )

        ADD_CUSTOM_TARGET(doc_forced
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}   )

    ENDIF (DOXYGEN_FOUND)
endif()
#------------------------------