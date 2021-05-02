cmake_minimum_required(VERSION 3.19)
project(Laboratorio1_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratorio1_1
        pregunta1.cpp
        pregunta1.h main.cpp pregunta2.cpp pregunta2.h pregunta3.cpp pregunta3.h pregunta4.cpp pregunta4.h)
