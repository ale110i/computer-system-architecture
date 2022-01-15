#include "number_encryption.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>

NumberEncryption *parse_number_encrypted(FILE *f) {
    int replacement_size;
    if (fscanf(f, "%d", &replacement_size) != 1 || replacement_size < 0) {
        invalid_input();
        return NULL;
    }
    char originals[1 << 16];
    for (size_t i = 0; i < (1 << 16); ++i) {
        originals[i] = ' ';
    }
    for (int i = 0; i < replacement_size; ++i) {
        char original;
        int replacement = 0;
        if (fscanf(f, " %c %d", &original, &replacement) != 2 || !is_valid_symbol(original) ||
            (short) replacement != replacement || originals[replacement += (1 << 15)] != ' ') {
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
    short *encrypted_string = (short *) malloc(sizeof(short) * len);
    if (encrypted_string == NULL) {
        allocation_error();
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        int replacement;
        fscanf(f, "%d", &replacement);
        if ((short) replacement != replacement || originals[replacement + (1 << 15)] == ' ') {
            invalid_input();
            free(encrypted_string);
            return NULL;
        }
        encrypted_string[i] = (short) replacement;
    }

    NumberReplacement *replacement = (NumberReplacement *) malloc(sizeof(NumberReplacement) * replacement_size);
    if (replacement == NULL) {
        allocation_error();
        free(encrypted_string);
        return NULL;
    }
    for (int i = 0, j = 0; i < (1 << 16); ++i) {
        if (originals[i] != ' ') {
            replacement[j].original = originals[i];
            replacement[j].replacement = (short) (i - (1 << 15));
            ++j;
        }
    }

    NumberEncryption *res = (NumberEncryption *) malloc(
            sizeof(NumberEncryption));
    if (res == NULL) {
        allocation_error();
        free(encrypted_string);
        free(replacement);
        return NULL;
    }
    res->replacement = replacement;
    res->encrypted_string = encrypted_string;
    res->replacement_size = replacement_size;
    res->string_len = len;
    return res;
}

void print_number_encrypted(NumberEncryption *encrypted, FILE *f) {
    fprintf(f, "Number Encryption\nReplacements: ");
    if (encrypted->replacement_size) {
        fprintf(f, "%c->%d", encrypted->replacement[0].original, encrypted->replacement[0].replacement);
        for (int i = 1; i < encrypted->replacement_size; ++i) {
            NumberReplacement *rpl = encrypted->replacement + i;
            fprintf(f, ", %c->%d", rpl->original, rpl->replacement);
        }
    }
    fprintf(f, "\nEncrypted string: ");
    fprintf(f, "%d", encrypted->encrypted_string[0]);
    for (size_t i = 1; i < encrypted->string_len; ++i) {
        fprintf(f, " %d", encrypted->encrypted_string[i]);
    }
}

double calculate_key_number_encrypted(NumberEncryption *encrypted) {
    char originals[1 << 16];
    for (int i = 0; i < encrypted->replacement_size; ++i) {
        NumberReplacement *rpl = encrypted->replacement + i;
        originals[((int) rpl->replacement) + (1 << 15)] = rpl->original;
    }
    size_t code_sum = 0;
    for (size_t i = 0; i < encrypted->string_len; ++i) {
        code_sum += (size_t) originals[((int) encrypted->encrypted_string[i]) + (1 << 15)];
    }
    return (double) code_sum / (double) encrypted->string_len;
}

void destruct_number_encrypted(NumberEncryption *encrypted) {
    free(encrypted->replacement);
    free(encrypted->encrypted_string);
    free(encrypted);
}