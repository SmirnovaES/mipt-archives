#ifndef LIST
#define LIST


struct node{
   struct node* prev;
   struct node* next;
    int value;
};

typedef struct node node;


typedef struct {
    node* head;
    node* tail;
    int size;
} list;

list* list_new();

void list_delete(list* list);

void push(list* list, int val);

void pop(list* list, int* x);

void unshift(list* list, int val);

void shift(list* list, int* x);

void reverse(list* list);

#endif // LIST
