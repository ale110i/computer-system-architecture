from random import randint
from container_generator import ContainerGenerator
from input_generator import generate_input
from output_generator import generate_output

max_container_size = 2

if __name__ == '__main__':
    container_size = randint(0, max_container_size - 1)
    # container_size = 0
    container_gen = ContainerGenerator()
    container, sorted_container = container_gen.generate_container(container_size)
    correct_input_path = 'correct_input.txt'
    correct_output_path = 'correct_output.txt'
    with open(correct_input_path, 'w') as input_file:
        correct_input = generate_input(container)
        for i in range(len(correct_input) - 1):
            print(correct_input[i], file=input_file)
        if len(correct_input):
            print(correct_input[-1], end='', file=input_file)
    with open(correct_output_path, 'w') as output_file:
        correct_output = generate_output(container, sorted_container)
        for i in range(len(correct_output) - 1):
            print(correct_output[i], file=output_file)
        if len(correct_output):
            print(correct_output[-1], end='', file=output_file)
