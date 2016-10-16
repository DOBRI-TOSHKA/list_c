all: dz3

dz3: main_for_stat.o                                                                             
	gcc main_for_stat.o -L./lib_static -lmy_list_two_forked -o dz3_for_stat.out                                                                
	mv ./dz3_for_stat.out ./out_result_files/dz3_for_stat.out                                                                   
	rm -f *.o
	                                                                                           
main_for_stat.o: ./main_for_stat.c                                                                                              
	gcc -std=c99 -c -g ./main_for_stat.c                                                                           

clean:                                                                                                        
	rm -rf *.o dz_1  
