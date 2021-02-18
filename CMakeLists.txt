cmake_minimum_required(VERSION 3.10)

project(ParallelAlgos LANGUAGES C)

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

# OpenMP
find_package(OpenMP REQUIRED)

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

#########################
# Dense linear algebra  #
#########################

# To do