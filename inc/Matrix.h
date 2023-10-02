#ifndef __DOPOOMATRIX__
#define __DOPOOMATRIX__

typedef enum{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2
}dopoo_axis;

void
dopoo_matrix3F_createRotateMatrix(float mat[][3], dopoo_axis axis, float radians);

void
dopoo_matrix3F_postMult(float this[][3], const float other[][3])

void
dopoo_matrix3F_inverse(float invMat[][3], float mat[][3]);

#endif
