all: dz3
                                                                                                      
dz3: main.o my_list_two_forked.o                                                                                          
	gcc main.o my_list_two_forked.o -o dz3.out
	mv ./dz3.out ./out_result_files/dz3.out
	rm -rf *.o dz_1
	                                                                        
main.o: ./main.c                                                                                                
	gcc -std=c99 -c -g ./main.c 
	                                                                             
my_list_two_forked.o: ./lib_src/my_list_two_forked.c 
	gcc -std=c99 -c -g ./lib_src/my_list_two_forked.c

clean:                                                                                                        
	rm -rf *.o dz_1  
