cmake_minimum_required(VERSION 3.1)
project(spmv_benchmarking)

set(SOURCE_FILES
    main.cpp)

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

