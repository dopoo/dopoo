#ifndef __DOPOOMATRIX__
#define __DOPOOMATRIX__
#include "Vec.h"

typedef enum{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2
}dopoo_axis;

void
dopoo_mat3D_createRotateMatrix(double mat[][3], dopoo_axis axis, double radians);

void
dopoo_mat3D_postMult(double this[][3], const double other[][3]);

void
dopoo_mat3D_inverse(double invMat[][3], double mat[][3]);

void
dopoo_mat3D_transpose(double mt[][3], double m[][3]);

dopoo_vec3D
dopoo_mat3D_postRotate(double m[][3], dopoo_vec3D v);

void
dopoo_mat3D_print(double m[][3], const char* label);

#endif
