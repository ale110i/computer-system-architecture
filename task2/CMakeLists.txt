cmake_minimum_required(VERSION 3.21)
project(task2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task2 main.cpp common.cpp common.h characters_replacement_encryption.cpp characters_replacement_encryption.h encryption.cpp encryption.h shift_encryption.cpp shift_encryption.h number_replacement_encryption.cpp number_replacement_encryption.h container.cpp container.h)
