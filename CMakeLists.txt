cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("epyks")

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.58
             REQUIRED
             system
             )
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OpenSSL_INCLUDE_DIRS})

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
set(PROTOBUF_LIBRARIES ${PROTOBUF_LIBRARIES})

set(UPNPC_BUILD_TESTS FALSE CACHE BOOL "Build test executables"  FORCE)
set(UPNPC_BUILD_SHARED FALSE CACHE BOOL "Build shared library" FORCE)
set(UPNPC_BUILD_SAMPLE FALSE CACHE BOOL "Build test executables" FORCE)
set(UPNPC_NO_INSTALL TRUE CACHE BOOL "Disable installation" FORCE)
add_subdirectory(lib/miniupnp/miniupnpc)
include_directories(lib/miniupnp/miniupnpc)

set(JRTPLIB_COMPILE_STATIC TRUE CACHE BOOL "Flag indicating if a static library should be built, or a dynamic one" FORCE)
set(JRTPLIB_COMPILE_TESTS OFF CACHE BOOL "Compile jrtplib tests" FORCE)
# default configuration is missing [u]int[size]_t types, so force additional header
set(JRTPLIB_STDINT ON CACHE BOOL "Force std int types to be accepted" FORCE)
set(RTP_INTTYPE_HEADERS "#include <cstdint>\n${RTP_INTTYPE_HEADERS}" CACHE STRING "Force cstdint header" FORCE)
add_subdirectory(lib/jrtplib-3.11.1)
include_directories(${JRTPLIB_INCLUDE_DIRS})

enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall --std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(epyks-static STATIC epyks.h epyks.cpp)
target_link_libraries(epyks-static ${Boost_LIBRARIES}
                                   ${OPENSSL_LIBRARIES}
                                   jrtplib-static
                                   libminiupnpc-static)

add_subdirectory(proto)
add_subdirectory(client)
add_subdirectory(server)

add_executable(epyks-server server/main.cpp)
target_link_libraries(epyks-server epyks-static epyks-server-static)

add_executable(epyks-client client/main.cpp)
target_link_libraries(epyks-client epyks-static epyks-client-static)

add_custom_target(epyks-bin ALL DEPENDS epyks-static epyks-client epyks-server)
add_custom_command(TARGET epyks-bin POST_BUILD
                   COMMAND cp ARGS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${PROJECT_SOURCE_DIR})


