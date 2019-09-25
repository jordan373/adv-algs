cmake_minimum_required(VERSION 3.13)
project(Project5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(tests)

add_executable(Project5
        tests/t01.in
        tests/t01.out
        tests/t02.in
        tests/t02.out
        tests/t03.in
        tests/t03.out
        tests/t04.in
        tests/t04.out
        tests/t05.in
        tests/t05.out
        tests/t06.in
        tests/t06.out
        tests/t07.in
        tests/t07.out
        tests/t08.in
        tests/t08.out
        item.h
        main.cpp
        Makefile
        priorityqueue.cpp
        priorityqueue.h
        timestamp.h
        ugraph.cpp
        ugraph.h)
