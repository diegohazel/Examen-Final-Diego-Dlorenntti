cmake_minimum_required(VERSION 3.30)
project(final_exam_ex)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(final_exam_ex
    constants.h
    main.cpp
    runner.cpp
    runner.h)
