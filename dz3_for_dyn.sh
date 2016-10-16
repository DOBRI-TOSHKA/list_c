#!/bin/bash

echo "GENERATE LIBRARY DYNAMIC"

./lib_dynamic/dz3_create_dyn_lib.sh

make -f ./make_files/dz3_for_dyn.make

./out_result_files/dz3_for_dyn.out input.txt inv_input.txt
