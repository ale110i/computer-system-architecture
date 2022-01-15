from sys import argv
from os import path
from characters_replacement_encryption import CharactersReplacementEncryption
from shift_encryption import ShiftEncryption
from number_encryption import NumberEncryption

encryption_types = {
    1: CharactersReplacementEncryption,
    2: ShiftEncryption,
    3: NumberEncryption
}

max_container_size = 10000


def insertion_sort(a):
    for i in range(len(a)):
        j = i
        while j > 0 and a[j].get_key() < a[j - 1].get_key():
            a[j - 1], a[j] = a[j], a[j - 1]
            j -= 1


if __name__ == '__main__':
    if len(argv) != 3 or not path.exists(argv[1]):
        print("Invalid parameters")
    else:
        container = []
        try:
            with open(argv[1], 'r') as input_file:
                for line in input_file.readlines():
                    if len(container) >= max_container_size:
                        raise AttributeError
                    arr = line.split()
                    container.append(encryption_types[int(arr[0])](arr))
            with open(argv[2], 'w') as output_file:
                print('Container size:', str(len(container)), sep=' ', file=output_file)
                if len(container):
                    print('\nINITIAL ORDER:\n', file=output_file)
                    print(*container, sep="\n\n", file=output_file)
                    insertion_sort(container)
                    print('\nSORTED:\n', file=output_file)
                    print(*container, sep="\n\n", file=output_file)
        except:
            print('Invalid input')
