#include "shift_encryption.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>


typedef struct ShiftDecryptionTable {
    char alphabet[ALPHABET_SIZE];
    int char_id[MAX_VALID_CHAR_CODE + 1];
} ShiftDecryptionTable;

ShiftDecryptionTable *shift_decryption_table = NULL;

void create_shift_decryption_table() {
    if (shift_decryption_table != NULL) {
        return;
    }
    shift_decryption_table = (ShiftDecryptionTable *) malloc(sizeof(ShiftDecryptionTable));
    if (shift_decryption_table == NULL) {
        allocation_error();
        return;
    }
    for (int i = 0; i < 10; ++i) {
        char c = (char) ('0' + i);
        shift_decryption_table->alphabet[i] = c;
        shift_decryption_table->char_id[c] = i;
    }
    for (int i = 0; i < 26; ++i) {
        char c = (char) ('A' + i);
        shift_decryption_table->alphabet[i + 10] = c;
        shift_decryption_table->char_id[c] = i + 10;
        c = (char) ('a' + i);
        shift_decryption_table->alphabet[i + 36] = c;
        shift_decryption_table->char_id[c] = i + 36;
    }
}

void destruct_shift_decryption_table() {
    if (shift_decryption_table == NULL) {
        return;
    }
    free(shift_decryption_table);
    shift_decryption_table = NULL;
}

ShiftEncryption *parse_shift_encrypted(FILE *f) {
    create_shift_decryption_table();
    if (shift_decryption_table == NULL) {
        return NULL;
    }

    int shift;
    if (fscanf(f, "%d", &shift) != 1 || (short) shift != shift) {
        invalid_input();
        return NULL;
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
        if (!is_valid_symbol(encrypted_string[i])) {
            invalid_input();
            free(encrypted_string);
            return NULL;
        }
    }

    ShiftEncryption *res = (ShiftEncryption *) malloc(sizeof(ShiftEncryption));
    if (res == NULL) {
        allocation_error();
        free(encrypted_string);
        return NULL;
    }
    res->shift = (short) shift;
    res->encrypted_string = encrypted_string;
    return res;
}

void print_shift_encrypted(ShiftEncryption *encrypted, FILE *f) {
    fprintf(f, "Shift Encryption\nShift: %d\nEncrypted string: %s", encrypted->shift, encrypted->encrypted_string);
}

double calculate_key_shift_encrypted(ShiftEncryption *encrypted) {
    size_t code_sum = 0;
    size_t len = strlen(encrypted->encrypted_string);
    for (size_t i = 0; i < len; ++i) {
        int replacement_id = shift_decryption_table->char_id[encrypted->encrypted_string[i]];
        int original_id = ((replacement_id - encrypted->shift) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
        code_sum += (size_t) shift_decryption_table->alphabet[original_id];
    }
    return (double) code_sum / (double) len;
}

void destruct_shift_encrypted(ShiftEncryption *encrypted) {
    destruct_shift_decryption_table();
    free(encrypted->encrypted_string);
    free(encrypted);
}
