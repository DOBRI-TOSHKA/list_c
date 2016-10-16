#!/bin/bash

gcc -c -fPIC ./lib_src/my_list_two_forked.c

gcc -shared -o ./libmy_list_two_forked.so  ./my_list_two_forked.o

rm -f *.o

mv ./libmy_list_two_forked.so ./lib_dynamic/libmy_list_two_forked.so

cp ./lib_src/my_list_two_forked.h ./lib_dynamic/my_list_two_forked.h
