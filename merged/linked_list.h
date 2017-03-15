/* Author Greg Johnson */
/* 9.28.16 */
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node{
	void *data;
	struct node *parent, *child;
} node;

typedef int (*comparison_func) (void*, void*);
typedef void (*free_func) (void*);

typedef struct linked_list{
	comparison_func compare;
	free_func free_node, print;
	//char *print_format;
	node *head;
	unsigned int size;
} linked_list;

linked_list* create_linked_list(comparison_func, free_func, free_func);

node* create_node(void*);
node* get_node(linked_list*, void*);
node* get_node_at(linked_list*, int);

void add_node(linked_list*, node*);
void print_list(linked_list*);
void empty_list(linked_list*);

bool insert_node(linked_list*, node*, node*);
bool contains_node(linked_list*, node*);
bool delete_node(linked_list*, node*);

#endif