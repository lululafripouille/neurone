cmake_minimum_required(VERSION 3.7.2)
project(neurones)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
       	principalNeurone3.cpp
        Reseau.cpp
        Reseau.hpp
        Neurone.cpp
        Neurone.hpp)


include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_FILES})

add_executable(neurones ${SOURCE_FILES})
add_executable(neurones_unittest Neurone.cpp neurones_unittest.cpp)

target_link_libraries(neurones_unittest gtest gtest_main)
add_test(neurones_unittest neurones_unittest)