cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(DGCU_GPA_Calculator LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(WINTOASTLIB_QT_ENABLED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    src/App.ui
    src/App.h
    src/App.cpp
    assets/rc.qrc
    assets/rc.rc
)

qt_add_executable(DGCU_GPA_Calculator ${PROJECT_SOURCES})

set(TARGET_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set_target_properties(DGCU_GPA_Calculator
    PROPERTIES
        WIN32_EXECUTABLE TRUE
        RUNTIME_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIRECTORY}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_OUTPUT_DIRECTORY}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_OUTPUT_DIRECTORY}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TARGET_OUTPUT_DIRECTORY}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TARGET_OUTPUT_DIRECTORY}
)
include_directories(vcpkg_installed/x64-windows/include)
link_directories(vcpkg_installed/x64-windows/lib)

file(COPY vcpkg_installed/x64-windows/lib/ DESTINATION ${CMAKE_BINARY_DIR})
file(COPY vcpkg_installed/x64-windows/bin/ DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(DGCU_GPA_Calculator
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        xlsxwriter
)

if (MSVC)
    target_compile_options(DGCU_GPA_Calculator PRIVATE /ZI)
    set_target_properties(DGCU_GPA_Calculator PROPERTIES LINK_FLAGS "/INCREMENTAL")
endif()

