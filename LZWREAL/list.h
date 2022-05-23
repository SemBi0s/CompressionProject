#ifndef element_h
typedef struct{
    char *value;
    int id;
} element;
#endif  // element_h

#ifndef node_h
typedef struct node
{
    element data;
    struct node *next;
} node; 
#endif  // node_h

void Push(node**, char *, int id);
void PushEnd(node**, char * , int id);
void PrintList(node *);
void DeleteList(node **);