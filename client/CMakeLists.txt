cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("epyks-client-static")

enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall --std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
message(STATUS "Using Qt5::Core v${Qt5Core_VERSION}")

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
message(STATUS "Using Qt5::Widgets v${Qt5Widgets_VERSION}")

set(QT_FILE_NAMES logindialog
                  mainwindow)

# for each qt file name, try to include header, sources and ui files
foreach(name ${QT_FILE_NAMES})
    file(GLOB qt_header "qt/${name}.h")
    file(GLOB qt_source "qt/${name}.cpp")
    file(GLOB qt_ui "qt/${name}.ui")
    list(APPEND QT_FILES ${qt_header} ${qt_source} ${qt_ui})
endforeach()

set(CLIENT_SOURCES main.cpp ${QT_FILES})

include_directories(${CMAKE_SOURCE_DIR})

add_library(epyks-client-static STATIC ${CLIENT_SOURCES} ${PROTO_HEADERS} ${PROTO_SOURCES})
target_link_libraries(epyks-client-static ${Qt5Core_LIBRARIES}
                                          ${Qt5Widgets_LIBRARIES}
                                          ${PROTOBUF_LIBRARIES})

