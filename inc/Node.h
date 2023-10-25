#ifndef __DOPOONODE__
#define __DOPOONODE__

#include "DataType.h"

typedef struct
{
    dopoo_dataType type;
    void* prim;
    void* prev;
    void* next;
}dopoo_node2;

dopoo_node2*
dopoo_node2_create(void* prim, void* prev, void* next);

void
dopoo_node2_clear(dopoo_node2* node);


#endif