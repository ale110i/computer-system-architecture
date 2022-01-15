#include "encryption.h"
#include "common.h"


int parse_encrypted(FILE *f, Encryption *res) {
    int type_id;
    if (fscanf(f, "%d", &type_id) != 1 || type_id < 1 || type_id > 3) {
        invalid_input();
        return 0;
    }
    res->type_id = type_id;
    res->key = -1;
    if (type_id == 1) {
        CharactersReplacementEncryption *encrypted = parse_characters_replacement_encrypted(f);
        if (encrypted == NULL) {
            return 0;
        }
        res->characters_replacement_encrypted = encrypted;
    } else if (type_id == 2) {
        ShiftEncryption *encrypted = parse_shift_encrypted(f);
        if (encrypted == NULL) {
            return 0;
        }
        res->shift_encrypted = encrypted;
    } else if (type_id == 3) {
        NumberEncryption *encrypted = parse_number_encrypted(f);
        if (encrypted == NULL) {
            return 0;
        }
        res->number_encrypted = encrypted;
    }
    return 1;
}

void print_encrypted(Encryption encrypted, FILE *f) {
    if (encrypted.type_id == 1) {
        print_characters_replacement_encrypted(encrypted.characters_replacement_encrypted, f);
    } else if (encrypted.type_id == 2) {
        print_shift_encrypted(encrypted.shift_encrypted, f);
    } else if (encrypted.type_id == 3) {
        print_number_encrypted(encrypted.number_encrypted, f);
    }
}

double calculate_key_encrypted(Encryption encrypted) {
    if (encrypted.key != -1) {
        return encrypted.key;
    }
    double ans = 0;
    if (encrypted.type_id == 1) {
        ans = calculate_key_characters_replacement_encrypted(encrypted.characters_replacement_encrypted);
    } else if (encrypted.type_id == 2) {
        ans = calculate_key_shift_encrypted(encrypted.shift_encrypted);
    } else if (encrypted.type_id == 3) {
        ans = calculate_key_number_encrypted(encrypted.number_encrypted);
    }
    encrypted.key = ans;
    return ans;
}

void destruct_encrypted(Encryption encrypted) {
    if (encrypted.type_id == 1) {
        destruct_characters_replacement_encrypted(encrypted.characters_replacement_encrypted);
    } else if (encrypted.type_id == 2) {
        destruct_shift_encrypted(encrypted.shift_encrypted);
    } else if (encrypted.type_id == 3) {
        destruct_number_encrypted(encrypted.number_encrypted);
    }
}
