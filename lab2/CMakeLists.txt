cmake_minimum_required(VERSION 3.10)
project(AOIS_Lab2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

include_directories(include)

add_library(logic_lib STATIC 
    src/forms.cpp 
    src/opz.cpp 
    src/table.cpp
    src/menu.cpp
    src/main.cpp
)

add_executable(main src/main.cpp)
target_link_libraries(main logic_lib)

add_executable(run_tests tests/test_logic.cpp)

target_link_libraries(run_tests logic_lib)

add_custom_target(coverage
    COMMAND ./run_tests
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

