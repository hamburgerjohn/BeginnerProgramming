cmake_minimum_required(VERSION 3.4)
project(pybind_test)
add_subdirectory(pybind11)
pybind11_add_module(morse pyImport.cpp ../c++/MorseCodeDecipher.cpp ../c++/MorseCodePlayer.cpp ../c++/WaveMaker.cpp ../c++/WriteMorseCode.cpp)

