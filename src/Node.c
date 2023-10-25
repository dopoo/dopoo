#include "stdlib.h"
#include "../inc/Node.h"
#include "../inc/Primitive.h"


dopoo_node2*
dopoo_node2_create(void* prim, void* prev, void* next)
{
    dopoo_node2* node = (dopoo_node2*)malloc(sizeof(dopoo_node2));
    node->type = NODE2;
    node->prim = prim;
    node->prev = prev;
    node->next = next;
    return node;
}

void
dopoo_node2_clear(dopoo_node2* node)
{
    dopoo_prim_clear(node->prim);
    free(node);
}