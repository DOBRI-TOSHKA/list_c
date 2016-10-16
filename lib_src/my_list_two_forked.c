#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "my_list_two_forked.h"


struct CNode_List{
    voidptr Data;
    struct CNode_List *Next;
    struct CNode_List *Prev;
};

struct _List{
    CNode *Head;
    CNode *Tail;
    size_t size_list;
};


typedef enum dz2_err{
    DZ3_OK = 0,
    DZ3_ENOMEM = -1,
    DZ3_BAD_FILE = -2,
    DZ3_NULL_POINTER = -3,
    DZ3_BAD_HEAD = -4,
    DZ3_BAD_TAIL = -5,
    DZ3_BAD_INP_ARG = -6
}dz2_err_t;

static const char* const dz2_err_str[] = {
    "DZ3_OK",
    "DZ3_ENOMEM",
    "DZ3_BAD_FILE",
    "DZ3_NULL_POINTER",
    "DZ3_BAD_HEAD",
    "DZ3_BAD_TAIL",
    "DZ3_BAD_INP_ARG",
    0
};

static void print_err_dz3(const char *func, const char *filename, int line_in_code, dz2_err_t scode_err){
    printf("[%s:%d] %s %d: %s\n ", filename, line_in_code, func, scode_err, dz2_err_str[-scode_err]);
}

static bool list_node_cmp(List *list, CNode *node){

    if(list == NULL || node == NULL){
        print_err_dz3("delete_node", __FILE__, __LINE__, DZ3_NULL_POINTER);
        false;
    }

    CNode *cur = list->Head;

    while(cur){
        if(cur == node){
            return true;
        }
        cur = cur->Next;
    }

    return false;
}

List *create_list(){

    List *new_list = malloc(sizeof(List));

    if(!new_list){
        print_err_dz3("create_node", __FILE__, __LINE__, DZ3_ENOMEM);
        return NULL;
    }

    new_list->Head = NULL;
    new_list->Tail = NULL;
    new_list->size_list = 0;

    return new_list;
}

CNode *create_node(){

    CNode *new_node = malloc(sizeof(CNode));

    if(!new_node){
        print_err_dz3("create_node", __FILE__, __LINE__, DZ3_ENOMEM);
        return NULL;
    }

    new_node->Data = NULL;
    new_node->Next = NULL;
    new_node->Prev = NULL;

    return new_node;
}

void push_back(List *list, const voidptr data){

    if(!list){
        print_err_dz3("push_back", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    CNode *new_node = create_node();
    if(!new_node){
        print_err_dz3("push_back", __FILE__, __LINE__, DZ3_ENOMEM);
        return;
    }

    new_node->Data = data;
    new_node->Next = NULL;
    new_node->Prev = list->Tail;

    if (list->Tail) {
         list->Tail->Next = new_node;
    }

    list->Tail = new_node;

    if (list->Head == NULL) {
         list->Head = new_node;
    }

    list->size_list++;
}

voidptr pop_back(List *list){

    voidptr data = NULL;
    CNode *node_tail = NULL;

    if(!list){
        print_err_dz3("pop_back", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return NULL;
    }

    if(list->Tail == NULL){
        print_err_dz3("pop_back", __FILE__, __LINE__, DZ3_BAD_TAIL);
        return NULL;
    }

    node_tail = list->Tail;         //присваиваем в node_tail текущий хвост
    list->Tail = list->Tail->Prev;  //присваваем хвосту предыдущий узел, в случае если prev == NULL, то хвост
                                    // указывет на NULL. То есть голова и хвост указывали на один и тот же узел

    if(list->Tail){
        list->Tail->Next = NULL;    //в хорошем случае, в next записываем NULL
    }
    else{
        list->Head = NULL;          //в противном, голове присваиваем тоже NULL (список пуст)
//        list->Tail = NULL;        //хвост уже указывает на NULL
    }

    data = node_tail->Data;         //вытаскиваем данные
    free(node_tail);                //освобождаем память, выделенную под бывший хвост
    list->size_list--;              //уменьшаем размер списка

    return data;                    //возвращаем данные
}

void push_front(List *list,  const voidptr data){

    if(!list){
        print_err_dz3("push_front", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    CNode *new_node = create_node();
    if(!new_node){
        print_err_dz3("push_front", __FILE__, __LINE__, DZ3_ENOMEM);
        return;
    }

    new_node->Data = data;
    new_node->Next = list->Head;
    new_node->Prev = NULL;

    if(list->Head){
        list->Head->Prev = new_node;
    }

    list->Head = new_node;

    if(list->Tail == NULL){
        list->Tail = new_node;
    }

    list->size_list++;
}

voidptr pop_front(List *list){

    voidptr data = NULL;
    CNode *node_head = NULL;

    if(!list){
        print_err_dz3("pop_front", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return NULL;
    }

    if(list->Head == NULL){
        print_err_dz3("pop_back", __FILE__, __LINE__, DZ3_BAD_HEAD);
        return NULL;
    }

    node_head = list->Head;

    list->Head = list->Head->Next;
    if(list->Head){
        list->Head->Prev = NULL;
    }
    else{
//        list->Head = NULL;    //голова и так уже указывает на NULL
        list->Tail = NULL;      //Хвост теперь тоже указывает на NULL(список пуст)
    }

    data = node_head->Data;
    free(node_head);

    list->size_list--;
    return data;
}

int get_size_list(const List *list){

    if(!list){
        print_err_dz3("get_size", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return -1;
    }

    return list->size_list;
}

void union_list(List *list_first, List *list_second){

    if(list_first == NULL || list_second == NULL){
        print_err_dz3("union_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    list_first->Tail->Next = list_second->Head;
    list_second->Head->Prev = list_first->Tail;
    list_first->Tail = list_second->Tail;
    list_first->size_list += list_second->size_list;

    list_second->Head = NULL;       //после объединения отсутствует информация о втором списке,
    list_second->Tail = NULL;       //но данные лежат в первом
    list_second->size_list = 0;
}

//возвращает индекс в списке необходимого значения, если такого значения нет возвращает -1
int index_of_data_in_list(const List *list, const voidptr data){

    int index = -1;
    if(!list){
        print_err_dz3("index_of_data_in_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return 0;
    }

    CNode *cur = list->Head;
    while(cur){
        ++index;
        if(data == cur->Data){
            return index;
        }
        cur = cur->Next;
    }

    return -1;
}

//возвращает узел из списка с необходимиым значением, если такого значения нет возвращает NULL
CNode *find_node_in_list_by_data(const List *list, const voidptr data){

    if(!list){
        print_err_dz3("cnode_of_data_in_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return NULL;
    }

    CNode *cur = list->Head;
    while(cur){
        if(data == cur->Data){
            return cur;
        }
        cur = cur->Next;
    }

    return NULL;
}

CNode *find_node_in_list_by_index(const List *list, const int index){

    int index_cnt = -1;

    if(!list){
        print_err_dz3("find_node_in_list_by_index", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return NULL;
    }

    if((size_t)index >= list->size_list || index < 0){
        print_err_dz3("find_node_in_list_by_index", __FILE__, __LINE__, DZ3_BAD_INP_ARG);
        printf("Current size = %zu\n",list->size_list);
        return NULL;
    }

    CNode *cur = list->Head;

    while(cur) {
        index_cnt++;
        if(index_cnt == index){
            return cur;
        }
        cur = cur->Next;
    }

    return NULL;
}

void delete_node(List *list, CNode *node){

    if(list == NULL || node == NULL){
        print_err_dz3("delete_node", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    if(!list_node_cmp(list, node)){
         print_err_dz3("delete_node", __FILE__, __LINE__, DZ3_BAD_INP_ARG);
         puts("current node is not in list");
         return;
    }

    CNode *cur = node;

    if(node->Prev && node->Next){       //случай, когда удаляем из середины
        node->Prev->Next = cur->Next;
        node->Next->Prev = cur->Prev;
    }

    else if(!(node->Prev) && node->Next){    //случай, когда удаляем с головы, но дальше есть узлы
        list->Head = cur->Next;
        list->Head->Prev = NULL;
    }

    else if(node->Prev && !(node->Next)){    //случай, когда удаляем с хвоста, но перед ним есть узлы
        list->Tail = cur->Prev;
        list->Tail->Next = NULL;
    }

    else if(!(node->Prev) && !(node->Next)){    //случай, когда в списке один элемент
        list->Head = NULL;
        list->Tail = NULL;
    }

    list->size_list--;
    free(cur);
}

void show_list(const List *list){

    if(!list){
        print_err_dz3("show_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    CNode *cur = list->Head;

    if(cur == NULL){
        puts("[!!!ATTENTION!!!] List is empty");
        return;
    }

    while (cur) {
        printf("Data = %s\n",(char*)cur->Data);
        cur = cur->Next;
    }
}

void free_list(List **list){

    if(!list){
        print_err_dz3("free_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        return;
    }

    if(!(*list)){
        print_err_dz3("free_list", __FILE__, __LINE__, DZ3_NULL_POINTER);
        free(*list);
        return;
    }

    CNode *cur = (*list)->Head;
    CNode *next = NULL;

    while(cur){
        next = cur->Next;
        free(cur->Data);
        free(cur);
        cur = next;
    }

    free(*list);
    (*list) = NULL;
}
