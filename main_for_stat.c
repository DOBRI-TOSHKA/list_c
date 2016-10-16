#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include "lib_static/my_list_two_forked.h"


static void generate_list_with_data(List *list, FILE *file, size_t max_size_buff){

    size_t cnt_read_byte = 0;

    while(!feof(file)){
        int c = fgetc(file);
        ++cnt_read_byte;

        if(isspace(c)){

           if(cnt_read_byte > max_size_buff){
               cnt_read_byte = 0;
               continue;
           }

           fpos_t cur_pos;
           fgetpos(file, &cur_pos);

           char *data = malloc(sizeof(char) * cnt_read_byte);

           fseek(file, -cnt_read_byte, SEEK_CUR );
           fread(data, sizeof(char), cnt_read_byte, file);

           data[cnt_read_byte-1] = '\0';

           push_back(list, data);

           cnt_read_byte = 0;
           fsetpos(file, &cur_pos);
        }

        if(c == '\n' || c == '\0'){
            break;
        }
    }
}

static void inverse_write_data_from_list(List *list, FILE *file){
    while(get_size_list(list) != 0) {
        char *str = pop_back(list);
        printf("INV DATA: %s\n", str);
        fputs(str, file);
        if(get_size_list(list) == 0){
            fputc('\n', file);
        }
        fputc(' ', file);
    }
}

int main(int argc, char **argv){

    FILE *file = NULL;
    FILE *file_inv = NULL;

    if(argc == 3){

        file = fopen(argv[1], "rb");
        file_inv = fopen(argv[2], "w+");

        if(!file){
            printf("[BAD OPEN FILE FOR READING:%d] %s\n", __LINE__, argv[1]);
            return -1;
        }

        if(!file_inv){
            printf("[BAD OPEN FILE FOR WRITTING:%d] %s\n", __LINE__, argv[1]);
            const char *new_filename = "inverse_input.txt";
            printf("[GENERANT NEW NAME FOR WRITTING FILE = %s]\n", new_filename);
            file_inv = fopen(new_filename, "w+");

            if(!file_inv){
                printf("[BAD OPEN FILE FOR WRITTING:%d] %s\n", __LINE__, new_filename);
                return -1;
            }
        }
    }
    else if(argc == 2){

        file = fopen(argv[1], "rb");
        file_inv = NULL;

        if(!file){
            printf("[BAD OPEN FILE FOR READING:%d] %s\n", __LINE__, argv[1]);
            return -1;
        }

        const char *new_filename = "inverse_input.txt";
        printf("[GENERANT NEW NAME FOR WRITTING FILE = %s]\n", new_filename);
        file_inv = fopen(new_filename, "w+");

        if(!file_inv){
            printf("[BAD OPEN FILE FOR WRITTING:%d] %s\n", __LINE__, new_filename);
            return -1;
        }

    }
    else{
        puts("BAD INPUT ARGUMENTS");
        return -1;
    }

//    FILE *file = fopen("/home/anton/_programming/mail/course/c_plus_plus/dz3/project/dz3/input.txt", "rb");
//    if(!file){
//        printf("BAD OPEN\n");
//        return -1;
//    }

//    FILE *file_inv = fopen("/home/anton/_programming/mail/course/c_plus_plus/dz3/project/dz3/inv_input.txt", "w+");

    size_t max_size_buff = 1024;

    List *list = create_list();
	
    generate_list_with_data(list, file, max_size_buff);

    show_list(list);
    puts("======================================");

    inverse_write_data_from_list(list, file_inv);

    free_list(&list);
    fclose(file_inv);
    fclose(file);
    return 0;
}
