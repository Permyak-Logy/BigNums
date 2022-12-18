cmake_minimum_required(VERSION 3.23)
project(BigNum)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        BigNum src/main.cpp
        src/BigNums.h

        src/BigInt.h
        src/BigInt.cpp

        src/BigDouble.h
        src/BigDouble.cpp

        src/utils.cpp
        src/aliases.h
)
