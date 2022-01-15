from sys import argv
from os import path

if __name__ == '__main__':
    if len(argv) != 3 or not path.exists(argv[1]) or not path.exists(argv[2]):
        print("Invalid file paths")
    else:
        with open(argv[1], 'r') as program_output:
            with open(argv[2], 'r') as correct_output:
                program_out_lines = program_output.readlines()
                correct_out_lines = correct_output.readlines()
                is_good = True
                for i in range(min(len(program_out_lines), len(correct_out_lines))):
                    if program_out_lines[i] != correct_out_lines[i]:
                        print(f'FAIL: {argv[1]} vs {argv[2]}: lines differ from {i} line')
                        is_good = False
                        break
                if is_good and len(program_out_lines) != len(correct_out_lines):
                    is_good = False
                    print(f'FAIL: {argv[1]} vs {argv[2]}: one file is cut')
                if is_good:
                    print(f'OK: {argv[1]} vs {argv[2]}')