#
# Copyright (C) 2020 Adrian Carpenter
#
# This file is part of the Nedrysoft SettingsDialog. (https://github.com/nedrysoft/SettingsDialog)
#
# A cross-platform settings dialog
#
# Created by Adrian Carpenter on 07/12/2020.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

ADD_DEFINITIONS(-DNEDRYSOFT_LIBRARY_SETTINGSDIALOG_EXPORT)

# create the settings dialog library

project(SettingsDialog)

set(library_SOURCES
    src/ISettingsPage.h
    src/SettingsDialog.h
    src/SettingsDialogSpec.h
    src/SettingsDialog.cpp
)

if(WIN32)
    configure_file("Version.h.in" "Version.h")
    list(APPEND library_SOURCES "version.rc")
    add_definitions("-DNEDRYSOFT_MODULE_FILENAME=\"${PROJECT_NAME}.dll\"")
    add_definitions("-DNEDRYSOFT_MODULE_NAME=\"${PROJECT_NAME}\"")
endif()

# discover which Qt version is available

if (NOT DEFINED QT_VERSION_MAJOR)
    if (DEFINED USE_QT_VERSION)
        set(QT_VERSION_MAJOR ${USE_QT_VERSION})
        message(STATUS "Qt${QT_VERSION_MAJOR} has been manually selected")
    else()
        message(STATUS "Detecting Qt version")

        find_package(Qt6 COMPONENTS Core QUIET)
        find_package(Qt5 COMPONENTS Core QUIET)

        if (Qt6_FOUND)
            set(QT_VERSION_MAJOR 6)
        elseif(Qt5_FOUND)
            set(QT_VERSION_MAJOR 5)
        else()
            message(FATAL_ERROR "No valid Qt version was set, and none could be found")
        endif()
        message(STATUS "Detecting Qt version - done")
    endif()

    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)

    if (NOT Qt${QT_VERSION_MAJOR}_FOUND)
        message(FATAL_ERROR "Qt${QT_VERSION_MAJOR} could not be found")
    endif()

    message(STATUS "Qt major version: ${QT_VERSION_MAJOR}")
endif()

# end of qt selection/detection

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

set(Qt_LIBS Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

if(APPLE)
    list(APPEND library_SOURCES
        src/SeparatorWidget.cpp
        src/SeparatorWidget.h
        src/TransparentWidget.cpp
        src/TransparentWidget.h
    )
endif()

include_directories("src" "includes")

add_library(${PROJECT_NAME} SHARED
    ${library_SOURCES}
)

if(DEFINED NEDRYSOFT_SETTINGSDIALOG_LIBRARY_DIR)
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${NEDRYSOFT_SETTINGSDIALOG_LIBRARY_DIR}")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${NEDRYSOFT_SETTINGSDIALOG_LIBRARY_DIR}")
else()
    message(STATUS "Set NEDRYSOFT_SETTINGSDIALOG_LIBRARY_DIR to set the binary output dir.")
endif()

target_link_libraries(${PROJECT_NAME} ${Qt_LIBS})
target_link_libraries(${PROJECT_NAME} ComponentSystem)

if(APPLE)
    target_link_directories(${PROJECT_NAME} PRIVATE ${NEDRYSOFT_MACHELPER_LIBRARY_DIR})
    target_include_directories(${PROJECT_NAME} PRIVATE "${NEDRYSOFT_MACHELPER_INCLUDE_DIR}")

    target_link_libraries(${PROJECT_NAME} MacHelper)
    target_link_libraries(${PROJECT_NAME} "-framework AppKit" "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} stdc++ objc)
endif()

target_link_directories(${PROJECT_NAME} PRIVATE ${NEDRYSOFT_THEMESUPPORT_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} "ThemeSupport")
target_include_directories(${PROJECT_NAME} PRIVATE "${NEDRYSOFT_THEMESUPPORT_INCLUDE_DIR}")