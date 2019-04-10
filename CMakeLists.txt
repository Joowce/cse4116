cmake_minimum_required(VERSION 3.13)
project(embeded C)

set(CMAKE_C_STANDARD 11)

add_executable(embeded main.c log/log.c log/log.h proc.h)