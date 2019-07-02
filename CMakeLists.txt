cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
option(USE_AVX2 "USE AVX2 instuctions" OFF)
find_package(eigen3 REQUIRED CONFIG)
message(STATUS "Eigen3 found, version ${eigen3_VERSION}")

add_executable(eigen_perf_test eigen_perf_test.cpp)
target_link_libraries(eigen_perf_test Eigen3::Eigen)

if (USE_AVX2 AND MSVC )
    target_compile_options(eigen_perf_test PRIVATE /arch:AVX2)
    target_compile_definitions(eigen_perf_test PRIVATE -D__FMA__)
endif()


