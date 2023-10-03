#ifndef __DOPOOMATRIX__
#define __DOPOOMATRIX__
#include "Vec.h"

typedef enum{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2
}dopoo_axis;

void
dopoo_matrix3D_createRotateMatrix(double mat[][3], dopoo_axis axis, double radians);

void
dopoo_matrix3D_postMult(double this[][3], const double other[][3]);

void
dopoo_matrix3D_inverse(double invMat[][3], double mat[][3]);

dopoo_vec3D
dopoo_matrix3D_rotate(double m[][3], dopoo_vec3D v);

#endif
