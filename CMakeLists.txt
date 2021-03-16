# Intel oneAPI bug fixed in CMake 3.19.3, prior versions won't compile
cmake_minimum_required(VERSION 3.19.3)

project(ParallelAlgos LANGUAGES C)

# OpenMP
find_package(OpenMP REQUIRED)

# MPI
find_package(MPI REQUIRED)

message(STATUS "MPI_INCLUDE_PATH : ${MPI_INCLUDE_PATH}")
message(STATUS "MPI_LIBRARIES : ${MPI_LIBRARIES}")
message(STATUS "MPI_CXX_INCLUDE_PATH : ${MPI_CXX_INCLUDE_PATH}")
message(STATUS "MPI_CXX_INCLUDE_DIRS : ${MPI_CXX_INCLUDE_DIRS}")
message(STATUS "MPI_CXX_LIBRARIES : ${MPI_CXX_LIBRARIES}")
message(STATUS "MPI_CXX_FOUND : ${MPI_CXX_FOUND}")
message(STATUS "MPI_C_FOUND : ${MPI_C_FOUND}")
message(STATUS "MPI_C_INCLUDE_DIRS : ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MPI_C_COMPILER : ${CMAKE_C_COMPILER}")
message(STATUS "MPI_C_INCLUDE_PATH : ${MPI_C_INCLUDE_PATH}")
message(STATUS "MPI_C_LIBRARIES : ${MPI_C_LIBRARIES}")

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

# BLAS
set(BLA_VENDER Intel)
find_package(BLAS REQUIRED)
message(STATUS "BLAS_LIBRARIES : ${BLAS_LIBRARIES}")
include_directories(${BLAS_INCLUDE_DIRS})

#########################
# Usage demos           #
#########################

# Build OpenMP targets

add_executable(demo_omp_pi src/demo_usage/omp_pi.c)
target_link_libraries(demo_omp_pi PRIVATE OpenMP::OpenMP_C)
# Benchmark
file(COPY src/demo_usage/benchmark_omp_pi.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Build MPI targets

add_executable(demo_mpi_hello src/demo_usage/mpi_hello.c)
target_link_libraries(demo_mpi_hello ${MPI_C_LIBRARIES})

add_executable(demo_mpi_ring src/demo_usage/mpi_ring.c)
target_link_libraries(demo_mpi_ring ${MPI_C_LIBRARIES})

add_executable(demo_mpi_cy src/demo_usage/mpi_cy.c)
target_link_libraries(demo_mpi_cy ${MPI_C_LIBRARIES})

add_executable(demo_mpi_bcast src/demo_usage/mpi_coll_bcast.c)
target_link_libraries(demo_mpi_bcast ${MPI_C_LIBRARIES})

add_executable(demo_mpi_red src/demo_usage/mpi_coll_red.c)
target_link_libraries(demo_mpi_red ${MPI_C_LIBRARIES})

add_executable(demo_mpi_scan src/demo_usage/mpi_coll_scan.c)
target_link_libraries(demo_mpi_scan ${MPI_C_LIBRARIES})

add_executable(demo_mpi_sg src/demo_usage/mpi_coll_scatter_gather.c)
target_link_libraries(demo_mpi_sg ${MPI_C_LIBRARIES})

add_executable(demo_mpi_pi src/demo_usage/mpi_pi.c)
target_link_libraries(demo_mpi_pi ${MPI_C_LIBRARIES})
# Benchmark
file(COPY src/demo_usage/benchmark_mpi_pi.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#########################
# Dense linear algebra  #   
#########################



add_executable(dense_mm_blas src/dense_algebra/mm_blas.c)
target_link_libraries(dense_mm_blas ${BLAS_LIBRARIES})

add_executable(dense_mm_pblas src/dense_algebra/mm_pblas.c)
target_link_libraries(dense_mm_pblas ${BLAS_LIBRARIES} ${MPI_C_LIBRARIES})

# Copy script to run for all benchmarks
file(COPY src/demo_usage/run_all_benchmarks.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})