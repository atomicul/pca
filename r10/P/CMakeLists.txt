cmake_minimum_required(VERSION 3.27)
project(P)

include_directories(include)
set(CMAKE_CXX_STANDARD 20)

add_executable(P main.cpp
        src/time/Time.cpp
        src/time/Duration.cpp
        src/time/DateTime.cpp
        include/time/TimeInterval.h
        src/cdvii/Fares.cpp
        include/cdvii/Fares.h
        src/cdvii/Record.cpp
        include/cdvii/Record.h
        src/cdvii/Bill.cpp
        include/cdvii/Bill.h)
