cmake_minimum_required(VERSION 3.1)
project(spmv_benchmarking)


message(STATUS "Build type is " ${CMAKE_BUILD_TYPE})
message(STATUS "System is " ${CMAKE_SYSTEM_NAME})
message(STATUS "Compiler is " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Source dir is " ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "Linker Flags: " ${CMAKE_EXE_LINKER_FLAGS})
set(dir ${CMAKE_CURRENT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}")


set(SOURCE_FILES
    main.cpp
    spmv_registry.cpp
    parse_options.cpp
    plain_csr.cpp
    stub_spmv.cpp)


set(HEADER_FILES
    spmv.h
    spmv_registry.h
    plain_csr.h
    parse_options.h)


add_executable(spmv_benchmarking ${SOURCE_FILES})
target_sources(spmv_benchmarking PUBLIC ${HEADER_FILES})

##
## MMMatrixIO library
##
find_library(MMMatrixIO
  mmmatrixio
  PATHS ${CMAKE_SOURCE_DIR}/../lib/mmmatrixio
)
target_link_libraries(spmv_benchmarking ${MMMatrixIO})
target_include_directories(spmv_benchmarking PUBLIC ${CMAKE_SOURCE_DIR}/../MMMatrixIO/src)

#
# docopt library
#
include_directories(${CMAKE_SOURCE_DIR}/../docopt.cpp)
find_library(docopt
        docopt
        PATHS ${CMAKE_SOURCE_DIR}/../lib/docopt.cpp
        )
target_link_libraries(spmv_benchmarking ${docopt})

##
## OpenMP
##
find_package(OpenMP)
if (OPENMP_FOUND)
    add_definitions(-DOPENMP_EXISTS)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    message(STATUS "System is " ${CMAKE_SYSTEM_NAME})
endif()