cmake_minimum_required(VERSION 3.29)
project(SuperSerra64)

set(CMAKE_CXX_STANDARD 26)
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

include_directories(${INCLUDE_DIR})

add_library(Serra STATIC ${SOURCE_DIR}/Serra.cpp)
add_library(Impianto STATIC ${SOURCE_DIR}/Impianto.cpp)
add_library(Time STATIC ${SOURCE_DIR}/Time.cpp)
add_library(Manuale STATIC ${SOURCE_DIR}/Manuale.cpp)
add_library(Automatico STATIC ${SOURCE_DIR}/Automatico.cpp)
add_library(ConTermometro STATIC ${SOURCE_DIR}/ConTermometro.cpp)

add_executable(SuperSerra64 ${SOURCE_DIR}/main.cpp)