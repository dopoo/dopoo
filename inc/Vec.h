#ifndef __DOPOOVEC__
#define __DOPOOVEC__

#include <stdint.h>

typedef struct{
    double x;
    double y;
    double z;
}dopoo_vec3D;

typedef struct{
    int32_t i;
    int32_t j;
    int32_t k;
}dopoo_vec3I;

double 
dopoo_vec3D_dot(dopoo_vec3D v0, dopoo_vec3D v1);

dopoo_vec3D
dopoo_vec3D_cross(dopoo_vec3D v0, dopoo_vec3D v1);

double
dopoo_vec3D_lengthSqr(dopoo_vec3D v);

dopoo_vec3D
dopoo_vec3D_scale(dopoo_vec3D v, double scale);

dopoo_vec3D
dopoo_vec3D_add(dopoo_vec3D v0, dopoo_vec3D v1);

dopoo_vec3D
dopoo_vec3D_minus(dopoo_vec3D v0, dopoo_vec3D v1);

dopoo_vec3D 
dopoo_vec3D_inv(dopoo_vec3D v);

void
dopoo_vec3D_print(dopoo_vec3D v, const char* label);

dopoo_vec3D
dopoo_vec3D_norm(dopoo_vec3D v);

double
dopoo_vec3D_getz(dopoo_vec3D v);

dopoo_vec3D
dopoo_vec3D_clamp(dopoo_vec3D v);

double
dopoo_vec3D_getx(dopoo_vec3D v);

double
dopoo_vec3D_gety(dopoo_vec3D v);

#endif
