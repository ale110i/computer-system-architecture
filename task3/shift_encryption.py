from encryption import Encryption
from common import *


class ShiftEncryption(Encryption):
    def __init__(self, arr):
        super().__init__()
        if len(arr) != 4:
            raise AttributeError
        self.alphabet = ''
        self.char_id = {}
        self.build_alphabet()
        self.shift = int(arr[1])
        self.encrypted_string = arr[3]
        if len(self.encrypted_string) != int(arr[2]) or not all(map(is_valid_symbol, self.encrypted_string)):
            raise AttributeError
        code_sum = 0
        for c in self.encrypted_string:
            code_sum += ord(self.alphabet[(self.char_id[c] - self.shift) % len(self.alphabet)])
        self.key = code_sum / int(arr[2])

    def build_alphabet(self):
        for i in range(ord('0'), ord('9') + 1):
            self.char_id[chr(i)] = len(self.alphabet)
            self.alphabet += chr(i)
        for i in range(ord('A'), ord('Z') + 1):
            self.char_id[chr(i)] = len(self.alphabet)
            self.alphabet += chr(i)
        for i in range(ord('a'), ord('z') + 1):
            self.char_id[chr(i)] = len(self.alphabet)
            self.alphabet += chr(i)

    def __str__(self):
        return 'Shift Encryption\nShift: ' + str(self.shift) + '\nEncrypted string: ' + self.encrypted_string
