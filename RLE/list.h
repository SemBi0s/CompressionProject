#ifndef element_h
typedef struct{
    int vertex;
    int weight;
} element;
#endif  // element_h

#ifndef node_h
typedef struct node
{
    element data;
    struct node *next;
} node; 
#endif  // node_h

void Push(node**, element );
void PushEnd(node**, element);
void PrintList(node *);
void DeleteList(node **);