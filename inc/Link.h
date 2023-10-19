#ifndef __DOPOOLINK__
#define __DOPOOLINK__

#include "Vec.h" 
#include "Spectrum.h"

typedef struct
{
    dopoo_vec3D c;
    double r;
    dopoo_rgbI rgb;
    void* prev;
    void* next;
}dopoo_joint;

typedef struct
{
    void* nodes;
    dopoo_joint* joints;
}dopoo_link;



#endif