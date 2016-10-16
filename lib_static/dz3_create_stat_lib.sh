#!/bin/bash

gcc -std=c99 -c -g ./lib_src/my_list_two_forked.c

ar rc libmy_list_two_forked.a  my_list_two_forked.o

rm -f ./my_list_two_forked.o

ranlib libmy_list_two_forked.a

mv ./libmy_list_two_forked.a ./lib_static/libmy_list_two_forked.a
cp ./lib_src/my_list_two_forked.h ./lib_static/my_list_two_forked.h
 
