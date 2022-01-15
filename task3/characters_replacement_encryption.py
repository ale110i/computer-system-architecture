from encryption import Encryption
from common import *


class CharactersReplacementEncryption(Encryption):
    def __init__(self, arr):
        super().__init__()
        replacement_size = int(arr[1])
        if len(arr) != 4 + replacement_size * 2:
            raise AttributeError
        replacements = arr[2: 2 + 2 * replacement_size]
        if not all(map(is_valid_symbol, replacements)):
            raise AttributeError
        self.replacement = list(zip(replacements[::2], replacements[1::2]))
        self.replacement.sort(key=lambda x: x[1])

        self.encrypted_string = arr[-1]
        if int(arr[-2]) <= 0 or len(self.encrypted_string) != int(arr[-2]):
            raise AttributeError

        decryption = {}
        for x, y in self.replacement:
            if y in decryption.keys():
                raise AttributeError
            decryption[y] = x
        code_sum = 0
        for c in self.encrypted_string:
            if c not in decryption.keys():
                raise AttributeError
            code_sum += ord(decryption[c])
        self.key = code_sum / int(arr[-2])

    def __str__(self):
        return 'Characters Replacement Encryption\nReplacements:\n' + ', '.join(
            map(lambda x: x[0] + '->' + x[1], self.replacement)) + '\nEncrypted string: ' + self.encrypted_string
