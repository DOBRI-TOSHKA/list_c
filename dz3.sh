#!/bin/bash

make -f ./make_files/dz3.make

python3 ./dz3.py

./out_result_files/dz3.out input.txt inv_input.txt 
