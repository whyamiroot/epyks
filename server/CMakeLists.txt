cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("epyks-server-static")

enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall --std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADERS )
set(SOURCES main.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_library(epyks-server-static STATIC ${HEADERS} ${SOURCES} ${PROTO_HEADERS} ${PROTO_SOURCES})
target_link_libraries(epyks-server-static ${PROTOBUF_LIBRARIES})

