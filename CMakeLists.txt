cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("epyks")

enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall --std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.58
             REQUIRED
             system
             )
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OpenSSL_INCLUDE_DIRS})

set(UPNPC_BUILD_TESTS FALSE CACHE BOOL "Build test executables"  FORCE)
set(UPNPC_BUILD_SHARED FALSE CACHE BOOL "Build shared library" FORCE)
set(UPNPC_BUILD_SAMPLE FALSE CACHE BOOL "Build test executables" FORCE)
set(UPNPC_NO_INSTALL TRUE CACHE BOOL "Disable installation" FORCE)
add_subdirectory(miniupnp/miniupnpc)

add_library(epyks-static STATIC epyks.h epyks.cpp)
target_link_libraries(epyks-static ${Boost_LIBRARIES}
                                   ${OPENSSL_LIBRARIES}
                                   libminiupnpc-static)

add_subdirectory(client)
add_subdirectory(server)

add_executable(epyks-server server/main.cpp)
target_link_libraries(epyks-server epyks-static epyks-server-static)

add_executable(epyks-client client/main.cpp)
target_link_libraries(epyks-client epyks-static epyks-client-static)

add_custom_target(epyks-bin ALL DEPENDS epyks-static epyks-client epyks-server)
add_custom_command(TARGET epyks-bin POST_BUILD
                   COMMAND cp ARGS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${PROJECT_SOURCE_DIR})


