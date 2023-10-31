#ifndef __DOPOOJOINT__
#define __DOPOOJOINT__

#include "Vec.h" 
#include "Spectrum.h"
#include "Primitive.h"
#include "DataType.h"

typedef struct
{
    dopoo_dataType type;
    dopoo_sphere* s;
    void* prev;
    void* next;
}dopoo_joint2;

dopoo_joint2*
dopoo_joint2_create(dopoo_sphere* s, void* prev, void* next);

void
dopoo_joint2_clear(dopoo_joint2* joint);


#endif