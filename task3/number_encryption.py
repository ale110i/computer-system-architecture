from encryption import Encryption
from common import *


class NumberEncryption(Encryption):
    def __init__(self, arr):
        super().__init__()

        replacement_size = int(arr[1])
        replacements = arr[2: 2 + 2 * replacement_size]
        if not all(map(is_valid_symbol, replacements[::2])) or not all(map(is_short, replacements[1::2])):
            raise AttributeError
        self.replacement = list(zip(replacements[::2], map(int, replacements[1::2])))
        self.replacement.sort(key=lambda x: x[1])

        decryption = {}
        for x, y in self.replacement:
            if y in decryption.keys():
                raise AttributeError
            decryption[y] = x

        length = int(arr[2 + 2 * replacement_size])
        if length <= 0 or len(arr) != 3 + 2 * replacement_size + length:
            raise AttributeError
        self.encrypted_string = list(map(int, arr[-length:]))
        code_sum = 0
        for x in self.encrypted_string:
            if x not in decryption.keys():
                raise AttributeError
            code_sum += ord(decryption[x])
        self.key = code_sum / length

    def __str__(self):
        return 'Number Encryption\nReplacements:\n' + ', '.join(
            map(lambda x: x[0] + '->' + str(x[1]), self.replacement)) + '\nEncrypted string: ' + ' '.join(
            map(str, self.encrypted_string))
