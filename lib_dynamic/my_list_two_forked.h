#ifndef MY_LIST_TWO_FORKED_H
#define MY_LIST_TWO_FORKED_H

#include <stdlib.h>

typedef struct CNode_List CNode;

typedef struct _List  List;

typedef void * voidptr;

//==============================================================

CNode *create_node();

List *create_list();

void push_back(List *list,  const voidptr data);

voidptr pop_back(List *list);

void push_front(List *list,  const voidptr data);

voidptr pop_front(List *list);

int get_size_list(List *list);

void union_list(List *list_first, List *list_second);

int index_of_data_in_list(List *list, const voidptr data);

CNode *find_node_in_list_by_data(const List *list, const voidptr data);

CNode *find_node_in_list_by_index(const List *list, const int index);

void delete_node(List *list, CNode *node);

void show_list(const List *list);

void free_list(List **list);

#endif // MY_LIST_TWO_FORKED_H
