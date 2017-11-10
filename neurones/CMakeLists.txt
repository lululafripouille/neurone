cmake_minimum_required(VERSION 3.7.2)
project(neurones)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
       	principalNeurone4.cpp
        Reseau.cpp
        Reseau.hpp
        Neurone.cpp
        Neurone.hpp)


include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_FILES})

add_executable(neurones ${SOURCE_FILES})
add_executable(neurones_unittest Neurone.cpp Reseau.cpp neurones_unittest.cpp)

target_link_libraries(neurones_unittest gtest gtest_main)
add_test(neurones_unittest neurones_unittest)


###### Doxygen generation ######

find_package(Doxygen)
if(DOXYGEN_FOUND)

        IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
