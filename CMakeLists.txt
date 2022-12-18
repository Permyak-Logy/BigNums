cmake_minimum_required(VERSION 3.23)
project(BigNum)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        BigNum src/main.cpp
        src/BigNums.h
        src/utils.cpp
        src/aliases.h

        src/BigInt.h
        src/Int/utils.cpp
        src/Int/arithmetic.cpp
        src/Int/compare.cpp
        src/Int/init.cpp

        src/BigDouble.h
        src/Double/utils.cpp
        src/Double/arithmetic.cpp
        src/Double/init.cpp
        src/Double/compare.cpp
        )
