cmake_minimum_required(VERSION 3.14)
project(glad)

ADD_LIBRARY(glad src/glad.c)

TARGET_INCLUDE_DIRECTORIES(glad PUBLIC include/)

SET_TARGET_PROPERTIES(glad PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_COMPILE_FEATURES(glad PUBLIC cxx_std_20)

