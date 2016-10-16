import random

file_name = "input.txt"
gen_file = open(file_name, "w")

str_list = ['Hello', 'TEST', 'my_progs', 'life', 'study', 'sport', 'love', 'hard', 'level', 'mail.ru', 'Parallels', 'G']

for i in range(0, 10):
    ind_rand = random.randint(0, len(str_list)-1)
    gen_file.write(str_list[ind_rand])
    gen_file.write(' ')

ind_rand = random.randint(0, len(str_list) - 1)
gen_file.write(str_list[ind_rand])
gen_file.write('\n')

gen_file.close()
