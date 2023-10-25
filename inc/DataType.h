#ifndef __DOPOODATATYPE__
#define __DOPOODATATYPE__

typedef enum {
    NODE2 = 0,
    JOINT2 = 1,
    OTHER
} dopoo_dataType;

void
dopoo_dataType_clear(void* d);

#endif