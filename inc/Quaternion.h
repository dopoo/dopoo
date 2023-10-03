#ifndef __DOPOOQUATERNION__
#define __DOPOOQUATERNION__

#include "Vec.h"

typedef struct{
    double x;
    double y;
    double z;
    double w;
}dopoo_quatD;

dopoo_vec3D
dopoo_quatD_rotate(dopoo_quatD q, dopoo_vec3D v);

void
dopoo_quatD_print(dopoo_quatD q, const char* label);

dopoo_quatD
dopoo_quatD_m2q(double m[][3]);

void
dopoo_quatD_q2m(double m[][3], dopoo_quatD q);

#endif
