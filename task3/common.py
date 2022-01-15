def is_valid_symbol(c):
    if len(c) != 1:
        return False
    return ord('a') <= ord(c) <= ord('z') or ord('A') <= ord(c) <= ord('Z') or ord('0') <= ord(c) <= ord('9')


def is_short(x):
    return -(2**15) <= int(x) <= 2**15 - 1
