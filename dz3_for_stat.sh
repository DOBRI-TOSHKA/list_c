#!/bin/bash                                                                                                   

echo "GENERATE LIBRARY STATIC"

./lib_static/dz3_create_stat_lib.sh

make -f ./make_files/dz3_for_stat.make                                                                                 

python3 ./dz3.py                                                                                              

./out_result_files/dz3_for_stat.out input.txt inv_input.txt
