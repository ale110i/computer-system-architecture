#include "characters_replacement_encryption.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>


CharactersReplacementEncryption *parse_characters_replacement_encrypted(FILE *f) {
    int replacement_size;
    if (fscanf(f, "%d", &replacement_size) != 1 || replacement_size < 0) {
        invalid_input();
        return NULL;
    }
    char originals[MAX_VALID_CHAR_CODE + 1];
    for (size_t i = 0; i <= MAX_VALID_CHAR_CODE; ++i) {
        originals[i] = ' ';
    }

    for (int i = 0; i < replacement_size; ++i) {
        char original, replacement;
        if (fscanf(f, " %c %c", &original, &replacement) != 2 || !is_valid_symbol(original) ||
            !is_valid_symbol(replacement) || originals[replacement] != ' ') {
            invalid_input();
            return NULL;
        }
        originals[replacement] = original;
    }
    size_t len;
    if (fscanf(f, "%lu", &len) != 1 || !len) {
        invalid_input();
        return NULL;
    }
    char *encrypted_string = (char *) malloc(len + 1);
    if (encrypted_string == NULL) {
        allocation_error();
        return NULL;
    }
    if (fscanf(f, "%s", encrypted_string) != 1 || strlen(encrypted_string) != len) {
        invalid_input();
        free(encrypted_string);
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (!is_valid_symbol(encrypted_string[i]) || originals[(int) encrypted_string[i]] == ' ') {
            invalid_input();
            free(encrypted_string);
            return NULL;
        }
    }
    CharReplacement *replacement = (CharReplacement *) malloc(sizeof(CharReplacement) * replacement_size);
    if (replacement == NULL) {
        allocation_error();
        free(encrypted_string);
        return NULL;
    }
    for (int i = 0, j = 0; i <= MAX_VALID_CHAR_CODE; ++i) {
        if (originals[i] != ' ') {
            replacement[j].original = originals[i];
            replacement[j].replacement = (char) i;
            ++j;
        }
    }

    CharactersReplacementEncryption *res = (CharactersReplacementEncryption *) malloc(
            sizeof(CharactersReplacementEncryption));
    if (res == NULL) {
        allocation_error();
        free(encrypted_string);
        free(replacement);
        return NULL;
    }
    res->replacement = replacement;
    res->encrypted_string = encrypted_string;
    res->replacement_size = replacement_size;
    return res;
}

void print_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted, FILE *f) {
    fprintf(f, "Characters Replacement Encryption\nReplacements: ");
    if (encrypted->replacement_size) {
        fprintf(f, "%c->%c", encrypted->replacement[0].original, encrypted->replacement[0].replacement);
        for (int i = 1; i < encrypted->replacement_size; ++i) {
            CharReplacement *rpl = encrypted->replacement + i;
            fprintf(f, ", %c->%c", rpl->original, rpl->replacement);
        }
    }
    fprintf(f, "\nEncrypted string: %s", encrypted->encrypted_string);
}

double calculate_key_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted) {
    char originals[MAX_VALID_CHAR_CODE + 1];
    for (int i = 0; i < encrypted->replacement_size; ++i) {
        CharReplacement *rpl = encrypted->replacement + i;
        originals[rpl->replacement] = rpl->original;
    }
    size_t code_sum = 0;
    size_t len = strlen(encrypted->encrypted_string);
    for (size_t i = 0; i < len; ++i) {
        code_sum += (size_t) originals[encrypted->encrypted_string[i]];
    }
    return (double) code_sum / (double) len;
}

void destruct_characters_replacement_encrypted(CharactersReplacementEncryption *encrypted) {
    free(encrypted->replacement);
    free(encrypted->encrypted_string);
    free(encrypted);
}
