cmake_minimum_required(VERSION 3.21)
project(task1 C)

set(CMAKE_C_STANDARD 99)

add_executable(task1 main.c common.h common.c characters_replacement_encryption.h characters_replacement_encryption.c shift_encryption.c shift_encryption.h number_encryption.c number_encryption.h encryption.c encryption.h container.c container.h)
