#ifndef __DOPOOLIST__
#define __DOPOOLIST__

typedef struct
{
    int size;
    int maxSize;
    void** data;
}dopoo_list;

dopoo_list*
dopoo_list_create(int32_t maxSize);

void
dopoo_list_clear(dopoo_list* list);

void
dopoo_list_add(dopoo_list* list, void* node);

void*
dopoo_list_get(const dopoo_list* list, int32_t i);

#endif