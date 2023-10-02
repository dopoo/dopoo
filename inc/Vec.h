#ifndef __DOPOOVEC__
#define __DOPOOVEC__

typedef struct{
    double x;
    double y;
    double z;
}dopoo_vec3D;

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


#endif
