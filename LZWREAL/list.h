#ifndef element_h
typedef struct{
    char *value;
} element;
#endif  // element_h

#ifndef node_h
typedef struct node
{
    element data;
    struct node *next;
} node; 
#endif  // node_h

void Push(node**, char *);
void PushEnd(node**, char * );
void PrintList(node *);
void DeleteList(node **);