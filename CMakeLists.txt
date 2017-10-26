#
# CMakeLists.txt for the eProfile application
#
# Author: Stefano Takekawa s.takekawa_at_gmail.com
#
# Date: 2017
#
# Copyright: Apache Licence 2.0
#


#
# cmake version
#
cmake_minimum_required(VERSION 3.8)


#
# common include
#
include(support/common.cmake)


#
# variables
#
set(PROJECT_BASENAME "eprofile")
set(PROJECT_BASEDESCRIPTION "eProfile application")
set(PROJECT_BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}")
set(PROJECT_BASEVERSION_MAJOR "0")
set(PROJECT_BASEVERSION_MINOR "0")
set(PROJECT_BASEVERSION_PATCH "1")
set(PROJECT_BASEVERSION "${PROJECT_BASEVERSION_MAJOR}.${PROJECT_BASEVERSION_MINOR}.${PROJECT_BASEVERSION_PATCH}")
set(PROJECT_BASESOVERSION "0")
set(PROJECT_INCLUDE_DIR "${PROJECT_BASEDIR}/include")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}/src")
set(PROJECT_SUPPORT_DIR "${PROJECT_BASEDIR}/support")
set(PROJECT_FORMS_DIR "${PROJECT_BASEDIR}/forms")


#
# libtwo, QtTwo, QwtTwo
#
set(LIBTWO_DIR "../libtwo/install")
set(LIBQTTWO_DIR "../QtTwo/install")
set(LIBQWTTWO_DIR "../QwtTwo/install")

set(LIBTWO_LIB_DIR "${LIBTWO_DIR}/lib64/")
set(LIBTWO_INCLUDE_DIR "${LIBTWO_DIR}/include/")

set(LIBQTTWO_LIB_DIR "${LIBQTTWO_DIR}/lib64/")
set(LIBQTTWO_INCLUDE_DIR "${LIBQTTWO_DIR}/include/")

set(LIBQWTTWO_LIB_DIR "${LIBQWTTWO_DIR}/lib64/")
set(LIBQWTTWO_INCLUDE_DIR "${LIBQWTTWO_DIR}/include/")


#
# project
#
project(${PROJECT_BASENAME} LANGUAGES CXX)


#
# add GNU stuff
#
include(GNUInstallDirs)


#
# Qt stuff
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_FORMS_DIR} ${CMAKE_AUTOUIC_SEARCH_PATHS})
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)


#
# sources
#
set(PROJECT_SOURCES ${PROJECT_SRC_DIR}/${PROJECT_BASENAME}.cpp
                    ${PROJECT_SRC_DIR}/c_charcombination.cpp
                    ${PROJECT_SRC_DIR}/c_mainwindow_imp.cpp
                    ${PROJECT_SRC_DIR}/c_numbersselection.cpp
                    ${PROJECT_SRC_DIR}/c_numbersselector.cpp
                    ${PROJECT_SRC_DIR}/c_settings.cpp)


#
# headers
#
set(PROJECT_HEADERS ${PROJECT_INCLUDE_DIR}/c_mainwindow_imp.h
                    ${PROJECT_INCLUDE_DIR}/c_numbersselection.h
                    ${PROJECT_INCLUDE_DIR}/c_numbersselector.h
                    ${PROJECT_INCLUDE_DIR}/c_settings.h)



#
# forms
#
set(PROJECT_FORMS ${PROJECT_FORMS_DIR}/c_mainwindow.ui)


#
# generate ui_ files
#
qt5_wrap_ui(UI_GENERATED_HEADERS ${PROJECT_FORMS})


#
# includes
#
include_directories(/usr/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${LIBTWO_INCLUDE_DIR})
include_directories(${LIBQTTWO_INCLUDE_DIR})
include_directories(${LIBQWTTWO_INCLUDE_DIR})


#
# libraries
#
find_library(PROJECT_LIBRARY_TWO NAMES two HINTS "${LIBTWO_LIB_DIR}")
find_library(PROJECT_LIBRARY_QTTWO NAMES QtTwo HINTS "${LIBQTTWO_LIB_DIR}")
find_library(PROJECT_LIBRARY_QTTWO NAMES QtTwo HINTS "${LIBQWTTWO_LIB_DIR}")

set(PROJECT_LIBRARIES
    ${PROJECT_LIBRARY_TWO}
    ${PROJECT_LIBRARY_QTTWO}
    ${PROJECT_LIBRARY_QWTTWO}
)


#
# main target
#
add_executable(
    ${PROJECT_BASENAME}
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    ${UI_GENERATED_HEADERS}
)


#
# link libraries
#
target_link_libraries(${PROJECT_BASENAME}
                      ${PROJECT_LIBRARIES} 
                      Threads::Threads
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Widgets)


#
# configure files
#
configure_file(${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h.in ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h @ONLY)


#
# install
#
