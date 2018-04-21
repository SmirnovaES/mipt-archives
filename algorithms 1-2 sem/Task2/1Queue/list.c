#include <stdio.h>
#include "list.h"

list* list_new() {
    list* l = (list*) malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void list_delete(list* l) {
    int i;
    node* curr_node = l->head;
    for (i = 0; i < l->size - 1; i++) {
        curr_node = curr_node->next;
        free(curr_node->prev);
    }
    free(l);
}

void push_to_list(list* l, int val) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->value = val;
    if (l->size == 0) {
        new_node->prev = NULL;
        l->head = new_node;
        l->tail = new_node;
    } else {
        new_node->prev = l->tail;
        l->tail->next = new_node;
        l->tail = new_node;
    }
    new_node->next = NULL;
    l->size++;
}

void pop_from_list(list* l, int* x) {
    *x = l->tail->value;
    if (l->size > 1) {
        l->tail = l->tail->prev;
        free(l->tail->next);
        l->size--;
    } else {
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    }
}

void unshift(list* l, int val) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->value = val;
    if (l->size == 0) {
        new_node->next = NULL;
        l->head = new_node;
        l->tail = new_node;
    } else {
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
    }
    new_node->prev = NULL;
    l->size++;
}

void shift(list* l, int* x) {
    *x = l->head->value;
    if (l->size > 1) {
        l->head = l->head->next;
        free(l->head->prev);
        l->size--;
    } else {
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    }
}

void reverse(list* l) {
    node* curr_node = l->head;
    int i;
    for (i = 0; i < l->size; i++) {
        node* binder_node = curr_node->next;
        curr_node->next = curr_node->prev;
        curr_node->prev = binder_node;
        curr_node = curr_node->prev;
    }
    node* binder_node = l->head;
    l->head = l->tail;
    l->tail = binder_node;
}
