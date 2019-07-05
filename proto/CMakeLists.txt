cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("epyks-proto")

set(PROTO_FILE_NAMES msg)

execute_process(COMMAND protoc --cpp_out . ${PROTO_FILES} --proto_path=${PROJECT_SOURCE_DIR} OUTPUT_QUIET)
# add proto files and compiles sources to the corresponding variables
foreach(name ${PROTO_FILE_NAMES})
    file(GLOB proto_files "${name}.proto")
    list(APPEND PROTO_FILES ${proto_files})
    file(GLOB header "${name}.pb.h")
    list(APPEND PROTO_HEADER ${header})
    file(GLOB source "${name}.pb.cc")
    list(APPEND PROTO_SOURCE ${source})
    file(GLOB proto_files "${name}.proto")
endforeach()

set(PROTO_HEADERS ${PROTO_HEADER} PARENT_SCOPE)
set(PROTO_SOURCES ${PROTO_SOURCE} PARENT_SCOPE)

add_custom_target(epyks-proto ALL)

