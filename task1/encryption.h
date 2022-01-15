#pragma once

#include "characters_replacement_encryption.h"
#include "shift_encryption.h"
#include "number_encryption.h"

typedef struct Encryption {
    int type_id;
    union {
        CharactersReplacementEncryption *characters_replacement_encrypted;
        ShiftEncryption *shift_encrypted;
        NumberEncryption *number_encrypted;
    };
    double key;
} Encryption;

int parse_encrypted(FILE *f, Encryption *res);

void print_encrypted(Encryption encrypted, FILE *f);

double calculate_key_encrypted(Encryption encrypted);

void destruct_encrypted(Encryption encrypted);
