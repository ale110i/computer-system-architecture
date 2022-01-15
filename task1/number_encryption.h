#pragma once

#include <stdio.h>

typedef struct NumberReplacement {
    char original;
    short replacement;
} NumberReplacement;

typedef struct NumberEncryption {
    NumberReplacement *replacement;
    short *encrypted_string;
    size_t string_len;
    int replacement_size;
} NumberEncryption;

NumberEncryption *parse_number_encrypted(FILE *f);

void print_number_encrypted(NumberEncryption *encrypted, FILE *f);

double calculate_key_number_encrypted(NumberEncryption *encrypted);

void destruct_number_encrypted(NumberEncryption *encrypted);
