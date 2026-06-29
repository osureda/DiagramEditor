cmake_minimum_required(VERSION 3.16)

project(DiagramEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DiagramEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Resources/resources.qrc
        wizard.h wizard.cpp wizard.ui
        jsonfile.h jsonfile.cpp
        selectabledatabutton.h selectabledatabutton.cpp

        diagramelement.h diagramelement.cpp
        diagramconnection.h diagramconnection.cpp
        diagram.h diagram.cpp
        scrollabledatabuttonsselector.h scrollabledatabuttonsselector.cpp
        jsonserializable.h jsonserializable.cpp
        diagramtypegroup.h diagramtypegroup.cpp
        diagramtype.h diagramtype.cpp
        diagramresizer.h diagramresizer.cpp
        diagramcomponent.h diagramcomponent.cpp
        diagramspecification.h diagramspecification.cpp

        shorttextspecification.h shorttextspecification.cpp
        listspecification.h listspecification.cpp

        connectionspecifications.h connectionspecifications.cpp

        elementspecifications.h elementspecifications.cpp
        selectablespecification.h selectablespecification.cpp
        longtextspecification.h longtextspecification.cpp
        diagramitem.h diagramitem.cpp
        geometryutils.h geometryutils.cpp
        connectableresizer.h connectableresizer.cpp
        specificationsgroup.h specificationsgroup.cpp
        specificationsform.h specificationsform.cpp







    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DiagramEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DiagramEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DiagramEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DiagramEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DiagramEditor)
endif()
set_target_properties(DiagramEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DiagramEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DiagramEditor)
endif()
