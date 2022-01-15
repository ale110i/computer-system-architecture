#include "characters_replacement_encryption.h"

#include <stdexcept>
#include <cstring>

void CharactersReplacementEncryption::Parse(FILE *f) {
    if (fscanf(f, "%d", &replacement_size) != 1 || replacement_size < 0) {
        throw std::invalid_argument("");
    }
    char originals[MAX_VALID_CHAR_CODE + 1];
    for (char & original : originals) {
        original = ' ';
    }

    for (int i = 0; i < replacement_size; ++i) {
        char original, rpl;
        if (fscanf(f, " %c %c", &original, &rpl) != 2 || !is_valid_symbol(original) ||
            !is_valid_symbol(rpl) || originals[rpl] != ' ') {
            throw std::invalid_argument("");
        }
        originals[rpl] = original;
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
            if (!is_valid_symbol(encrypted_string[i]) || originals[encrypted_string[i]] == ' ') {
                throw std::invalid_argument("");
            }
            code_sum += originals[encrypted_string[i]];
        }
        key = double(code_sum) / double(len);
        replacement = new CharReplacement[replacement_size];
        for (int i = 0, j = 0; i <= MAX_VALID_CHAR_CODE; ++i) {
            if (originals[i] != ' ') {
                replacement[j].original = originals[i];
                replacement[j].replacement = (char) i;
                ++j;
            }
        }
    } catch (...) {
        delete[] encrypted_string;
        encrypted_string = nullptr;
        throw;
    }
}

void CharactersReplacementEncryption::Print(FILE *f) const {
    fprintf(f, "Characters Replacement Encryption\nReplacements: ");
    if (replacement_size) {
        fprintf(f, "%c->%c", replacement[0].original, replacement[0].replacement);
        for (int i = 1; i < replacement_size; ++i) {
            CharReplacement *rpl = replacement + i;
            fprintf(f, ", %c->%c", rpl->original, rpl->replacement);
        }
    }
    fprintf(f, "\nEncrypted string: %s", encrypted_string);
}

CharactersReplacementEncryption::~CharactersReplacementEncryption() {
    delete[] replacement;
    delete[] encrypted_string;
}
