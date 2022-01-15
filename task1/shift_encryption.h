#pragma once

#include <stdio.h>

typedef struct ShiftEncryption {
    short shift;
    char *encrypted_string;
} ShiftEncryption;

ShiftEncryption *parse_shift_encrypted(FILE *f);

void print_shift_encrypted(ShiftEncryption *encrypted, FILE *f);

double calculate_key_shift_encrypted(ShiftEncryption *encrypted);

void destruct_shift_encrypted(ShiftEncryption *encrypted);
