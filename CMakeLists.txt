cmake_minimum_required(VERSION 3.24)
project(FxCSVParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(FxCSVParser main.cpp src/CSVParser.cpp src/CSVParser.h src/CSVCell.cpp src/CSVCell.h)
