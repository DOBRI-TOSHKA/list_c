all: dz3

dz3: main_for_dyn.o                                                                             
	gcc main_for_dyn.o -L./lib_dynamic -lmy_list_two_forked -Wl,-rpath,./lib_dynamic/ -o dz3_for_dyn.out
	                                                               
	mv ./dz3_for_dyn.out ./out_result_files/dz3_for_dyn.out                                                                   
	rm -f *.o
	                                                                                           
main_for_dyn.o: ./main_for_dyn.c                                                                                              
	gcc -std=c99 -c -g ./main_for_dyn.c                                                                           

clean:                                                                                                        
	rm -rf *.o dz_1  
