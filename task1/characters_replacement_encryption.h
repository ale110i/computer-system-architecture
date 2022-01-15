#pragma once

#include <stdio.h>

typedef struct CharReplacement {
    char original;
    char replacement;
} CharReplacement;

typedef struct CharactersReplacementEncryption {
    CharReplacement *replacement;
    char *encrypted_string;
    int replacement_size;
} CharactersReplacementEncryption;

CharactersReplacementEncryption *parse_characters_replacement_encrypted(FILE *f);

void print_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted, FILE *f);

double calculate_key_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted);

void destruct_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted);
