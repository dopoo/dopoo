#ifndef __DOPOOJOINT__
#define __DOPOOJOINT__

#include "Vec.h" 
#include "Spectrum.h"

typedef struct
{
    dopoo_vec3D c;
    double r;
    dopoo_rgbI rgb;
    void* prev;
    void* next;
}dopoo_joint2;


#endif