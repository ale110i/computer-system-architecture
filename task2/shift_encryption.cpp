#include "shift_encryption.h"

#include <stdexcept>
#include <cstring>

void ShiftEncryption::Parse(FILE *f) {
    if (fscanf(f, "%hd", &shift) != 1) {
        throw std::invalid_argument("");
    }

    size_t len;
    if (fscanf(f, "%lu", &len) != 1 || !len) {
        throw std::invalid_argument("");
    }
    encrypted_string = new char[len + 1];
    try {
        if (fscanf(f, "%s", encrypted_string) != 1 || strlen(encrypted_string) != len) {
            throw std::invalid_argument("");
        }
        size_t code_sum = 0;
        for (size_t i = 0; i < len; ++i) {
            if (!is_valid_symbol(encrypted_string[i])) {
                throw std::invalid_argument("");
            }
            int replacement_id = shift_decryption_table.char_id[encrypted_string[i]];
            int original_id = ((replacement_id - shift) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
            code_sum += (size_t) shift_decryption_table.alphabet[original_id];
        }
        key = double(code_sum) / double(len);
    } catch (...) {
        delete[] encrypted_string;
        encrypted_string = nullptr;
        throw;
    }
}

void ShiftEncryption::Print(FILE *f) const {
    fprintf(f, "Shift Encryption\nShift: %d\nEncrypted string: %s", shift, encrypted_string);
}

ShiftEncryption::~ShiftEncryption() {
    delete[] encrypted_string;
}

ShiftEncryption::ShiftDecryptionTable::ShiftDecryptionTable() {
    for (int i = 0; i < 10; ++i) {
        char c = (char) ('0' + i);
        alphabet[i] = c;
        char_id[c] = i;
    }
    for (int i = 0; i < 26; ++i) {
        char c = (char) ('A' + i);
        alphabet[i + 10] = c;
        char_id[c] = i + 10;
        c = (char) ('a' + i);
        alphabet[i + 36] = c;
        char_id[c] = i + 36;
    }
}
