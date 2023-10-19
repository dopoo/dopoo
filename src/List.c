#include <stdlib.h>
#include "../inc/List.h"

dopoo_list*
dopoo_list_create(int32_t maxSize)
{
    dopoo_list* list = (dopoo_list*)malloc(sizeof(dopoo_list));
    list->size = 0;
    list->maxSize = maxSize;
    list->data = (void**)malloc(sizeof(void*) * maxSize);
}

void
dopoo_list_clear(dopoo_list* list)
{
    free(list->data);
    free(list);
}

void
dopoo_list_add(dopoo_list* list, void* node)
{
    if(list->size == list->maxSize)
    {
        list->maxSize *= 2;
        list->data = (void**)realloc(list->data, list->maxSize * sizeof(void*));
    }
    list->data[list->size] = node;
    list->size ++;
}

void*
dopoo_list_get(const dopoo_list* list, int32_t i)
{
    if(!list || i >= list->size)
        return NULL;
    
    return list->data[i];
}



