cmake_minimum_required(VERSION 3.3)
project(compoVm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra")

file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY src/generated)
file(MAKE_DIRECTORY include/generated)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/generated)

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

FILE(GLOB inFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" src/*.cpp src/generated/*.cpp include/*.h include/generated/*.h)
set(SOURCE_FILES ${inFiles} ${BisonOutput} ${FlexOutput})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(compoVm ${SOURCE_FILES})
target_link_libraries(compoVm)