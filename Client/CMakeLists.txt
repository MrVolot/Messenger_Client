cmake_minimum_required(VERSION 3.14)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "D:/Boost/boost_1_78_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/Boost/boost_1_78_0/lib")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

set(PROJECT_SOURCES
        qml.qrc
        register.h
        register.cpp
        ../Json/jsoncpp.cpp
        ../Json/json/json.h
        main.cpp
        windowManager.h
        windowmanager.cpp
        ioserviceworker.cpp
        ioserviceworker.h
        commands.h
        contact.h
        contact.cpp
        messenger.h
        messenger.cpp
)

set(BOOST_LIBRARYDIR D:/Boost/boost-build/lib)
set(BOOST_ROOT D:/Boost/boost_1_78_0)

set (Boost_USE_STATIC_LIBS ON)

set (Boost_USE_MULTITHREADED ON)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
    message("boost found")
else()
    message("Boost not found")
ENDIF()

set (BOOST_COMPONENTS system thread)

find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Client
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(Client
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
message ("Version")
message (${QT_VERSION_MAJOR})
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
target_link_libraries(Client
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2)

set_target_properties(Client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Client)
    qt_finalize_executable(Client)
endif()
