cmake_minimum_required(VERSION 2.8)
project(compoVm)
enable_testing()

set(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind")
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-reachable=yes --track-origins=yes --xml=yes --xml-file=test.xml")
include(CTest)

#-Weffc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wunreachable-code -Wuninitialized")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_ADDITIONAL_VERSIONS "1.55" "1.55.0")

file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY src/generated)
file(MAKE_DIRECTORY include/generated)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/generated)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/nodes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/core)

find_package(Boost 1.55 REQUIRED COMPONENTS log log_setup thread date_time filesystem system unit_test_framework)
find_package(Threads)

if(Boost_FOUND)
  include_directories( ${Boost_INCLUDE_DIRS} )
  link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
else(Boost_FOUND)
  message(FATAL_ERROR "Cannot build Quantib Boost Log test without Boost. Please set Boost_DIR.")
endif(Boost_FOUND)

find_package(BISON REQUIRED)
set(BisonOutput ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/generated/parser.h)
set(BisonSpecFile ${CMAKE_CURRENT_SOURCE_DIR}/resources/grammar.y)
if (BISON_FOUND)
    add_custom_command(
            OUTPUT ${BisonOutput}
            COMMAND ${BISON_EXECUTABLE}
            --token-table
            --no-lines
            --output=${CMAKE_CURRENT_SOURCE_DIR}/src/generated/parser.cpp
            --defines=${CMAKE_CURRENT_SOURCE_DIR}/include/generated/parser.h
            ${BisonSpecFile}
            DEPENDS ${BisonSpecFile}
            COMMENT "Generating ${BisonOutput}"
            VERBATIM
    )
endif ()

find_package(FLEX REQUIRED)
set(FlexOutput ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/lexer.cpp)
set(FlexSpecFile ${CMAKE_CURRENT_SOURCE_DIR}/resources/grammar.l)
if (FLEX_FOUND)
    add_custom_command(
            OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
            --noline
            --nounistd
            --outfile=${CMAKE_CURRENT_SOURCE_DIR}/src/generated/lexer.cpp
            ${FlexSpecFile}
            DEPENDS ${FlexSpecFile}
            COMMENT "Generating ${FlexOutput}"
            VERBATIM
    )
endif ()

FILE(GLOB inFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/parser/*.cpp src/nodes/*.cpp src/generated/*.cpp src/core/*.cpp include/*.h include/parser/*.h include/nodes/*.h  include/generated/*.h include/core/*.h)
set(SOURCE_FILES ${inFiles} ${BisonOutput} ${FlexOutput})

FILE(GLOB testFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" test/*.cpp)
set(TEST_FILES ${testFiles})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(compoVm ${SOURCE_FILES} src/main.cpp)
add_executable(tests ${TEST_FILES} ${SOURCE_FILES})

target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(tests PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

target_compile_definitions(compoVm PRIVATE "BOOST_LOG_DYN_LINK=1")
target_link_libraries(  compoVm
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                        ${Boost_LOG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT} )
add_test(NAME compoTest COMMAND tests)