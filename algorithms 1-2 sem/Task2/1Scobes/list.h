#ifndef LIST
#define LIST


struct node{
   struct node* prev;
   struct node* next;
   char value;
};

typedef struct node node;


typedef struct {
    node* head;
    node* tail;
    int size;
} list;

list* list_new();

void list_delete(list* list);

void push_to_list(list* list, char val);

void pop_from_list(list* list, char* x);

void unshift(list* list, char val);

void shift(list* list, char* x);

void reverse(list* list);

#endif // LIST
