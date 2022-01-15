#!/bin/bash

python3 unified_test_gen/main.py

echo 'testing task1'
cd task1
rm CMakeCache.txt
cmake CMakeLists.txt 1>/dev/null
make --silent
cd ..
touch program_output1.txt
./task1/task1 correct_input.txt program_output1.txt
python3 unified_test_check/main.py program_output1.txt correct_output.txt
# rm program_output.txt

echo 'testing task2'
cd task2
rm CMakeCache.txt
cmake CMakeLists.txt 1>/dev/null
make --silent
cd ..
touch program_output2.txt
./task2/task2 correct_input.txt program_output2.txt
python3 unified_test_check/main.py program_output2.txt correct_output.txt 
# rm program_output.txt

echo 'testing task3'
touch program_output3.txt
python3 task3/main.py correct_input.txt program_output3.txt
python3 unified_test_check/main.py program_output3.txt correct_output.txt 
# rm program_output.txt

echo 'testing finished'