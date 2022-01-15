#pragma once

#include "common.h"
#include "encryption.h"

class ShiftEncryption : public Encryption {
public:
    ShiftEncryption() = default;

    void Parse(FILE *f) override;

    void Print(FILE *f) const override;

    ~ShiftEncryption() override;

private:
    short shift = 0;
    char *encrypted_string = nullptr;

    struct ShiftDecryptionTable {
        ShiftDecryptionTable();

        char alphabet[ALPHABET_SIZE];
        int char_id[MAX_VALID_CHAR_CODE + 1];
    };

    ShiftDecryptionTable shift_decryption_table;
};
