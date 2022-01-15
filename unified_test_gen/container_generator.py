from random import randint, sample, choices
from copy import deepcopy

class ContainerGenerator(object):
    def __init__(self):
        self.generators = [self.cr_encryption, self.shift_encryption, self.num_encryption]

    @staticmethod
    def cr_encryption():
        input_line = '1 '
        alphabet = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
        alphabet_size = randint(1, len(alphabet))
        input_line += f'{alphabet_size} '
        what_to_replace_alphabet = sample(alphabet, alphabet_size)
        replace_with_alphabet = sample(alphabet, alphabet_size)
        encryption_table = dict(zip(what_to_replace_alphabet, replace_with_alphabet))
        message_length = randint(1, 100)
        message = choices(what_to_replace_alphabet, k=message_length)
        key = 0.
        for symbol in encryption_table:
            input_line += f'{symbol} {encryption_table[symbol]} '
        input_line += f'{message_length} '
        encrypted_message = ''
        for symbol in message:
            key += ord(symbol)
            encrypted_message += f'{encryption_table[symbol]}'
        input_line += encrypted_message
        output_string = 'Characters Replacement Encryption\nReplacements:\n'
        et_sorted = list(map(lambda k: (k, encryption_table[k]), encryption_table))
        et_sorted.sort(key=lambda element: element[1])
        output_string += ', '.join(map(lambda x: x[0] + '->' + x[1], et_sorted))
        output_string += '\nEncrypted string: ' + encrypted_message
        return input_line, output_string, key/message_length

    @staticmethod
    def shift_encryption():
        input_line = '2 '
        alphabet = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
        alphabet_size = len(alphabet)
        shift = randint(0, 1000)
        encryption_table = dict(zip(alphabet, map(lambda i: alphabet[(i + shift) % alphabet_size], range(alphabet_size))))
        message_length = randint(1, 100)
        message = choices(alphabet, k=message_length)
        key = 0.
        input_line += f'{shift} '
        input_line += f'{message_length} '
        encrypted_message = ''
        for symbol in message:
            key += ord(symbol)
            encrypted_message += f'{encryption_table[symbol]}'
        input_line += encrypted_message
        output_string = 'Shift Encryption\nShift: ' + str(shift) + '\nEncrypted string: ' + encrypted_message
        return input_line, output_string, key/message_length

    @staticmethod
    def num_encryption():
        input_line = '3 '
        alphabet = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
        alphabet_size = randint(1, len(alphabet))
        input_line += f'{alphabet_size} '
        what_to_replace_alphabet = sample(alphabet, alphabet_size)
        replace_with_alphabet = sample(range(0, 100), alphabet_size)
        encryption_table = dict(zip(what_to_replace_alphabet, replace_with_alphabet))
        message_length = randint(1, 100)
        message = choices(what_to_replace_alphabet, k=message_length)
        key = 0.
        for symbol in encryption_table:
            input_line += f'{symbol} {str(encryption_table[symbol])} '
        input_line += f'{message_length}'
        encrypted_message = ''
        for symbol in message:
            key += ord(symbol)
            encrypted_message += f' {str(encryption_table[symbol])}'
        input_line += encrypted_message
        output_string = 'Number Encryption\nReplacements:\n'
        et_sorted = list(map(lambda k: (k, encryption_table[k]), encryption_table))
        et_sorted.sort(key=lambda element: element[1])
        output_string += ', '.join(map(lambda x: x[0] + '->' + str(x[1]), et_sorted))
        output_string += '\nEncrypted string:' + encrypted_message
        return input_line, output_string, key / message_length

    def generate_container(self, container_size):
        container = []
        for i in range(container_size):
            item_type = randint(0, 2)
            container.append(self.generators[item_type]())
        sorted_container = deepcopy(container)
        sorted_container.sort(key=lambda element: element[2])
        return container, sorted_container
