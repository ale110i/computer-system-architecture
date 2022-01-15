#include "number_replacement_encryption.h"

#include <stdexcept>


void NumberReplacementEncryption::Parse(FILE *f) {
    if (fscanf(f, "%d", &replacement_size) != 1 || replacement_size < 0) {
        throw std::invalid_argument("");
    }
    char originals[1 << 16];
    for (char &original: originals) {
        original = ' ';
    }
    for (int i = 0; i < replacement_size; ++i) {
        char original;
        int rpl = 0;
        if (fscanf(f, " %c %d", &original, &rpl) != 2 || !is_valid_symbol(original) ||
            short(rpl) != rpl || originals[rpl += (1 << 15)] != ' ') {
            throw std::invalid_argument("");
        }
        originals[rpl] = original;
    }

    if (fscanf(f, "%lu", &string_len) != 1 || !string_len) {
        throw std::invalid_argument("");
    }

    encrypted_string = new short[string_len];
    try {
        size_t code_sum = 0;
        for (size_t i = 0; i < string_len; ++i) {
            int rpl;
            fscanf(f, "%d", &rpl);
            if (short(rpl) != rpl || originals[rpl + (1 << 15)] == ' ') {
                throw std::invalid_argument("");
            }
            code_sum += originals[rpl + (1 << 15)];
            encrypted_string[i] = short(rpl);
        }
        key = double(code_sum) / double(string_len);

        replacement = new NumberReplacement[replacement_size];

        for (int i = 0, j = 0; i < (1 << 16); ++i) {
            if (originals[i] != ' ') {
                replacement[j].original = originals[i];
                replacement[j].replacement = short(i - (1 << 15));
                ++j;
            }
        }
    } catch (...) {
        delete[] encrypted_string;
        encrypted_string = nullptr;
        throw;
    }
}

void NumberReplacementEncryption::Print(FILE *f) const {
    fprintf(f, "Number Encryption\nReplacements: ");
    if (replacement_size) {
        fprintf(f, "%c->%d", replacement[0].original, replacement[0].replacement);
        for (int i = 1; i < replacement_size; ++i) {
            NumberReplacement *rpl = replacement + i;
            fprintf(f, ", %c->%d", rpl->original, rpl->replacement);
        }
    }
    fprintf(f, "\nEncrypted string: ");

    fprintf(f, "%d", encrypted_string[0]);
    for (size_t i = 1; i < string_len; ++i) {
        fprintf(f, " %d", encrypted_string[i]);
    }
}

NumberReplacementEncryption::~NumberReplacementEncryption() {
    delete[] replacement;
    delete[] encrypted_string;
}
