#ifndef __DOPOOMATRIX__
#define __DOPOOMATRIX__

typedef enum{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2
}dopoo_axis;

void
dopoo_matrix3F_createRotateMatrix(double mat[][3], dopoo_axis axis, double radians);

void
dopoo_matrix3F_postMult(double this[][3], const double other[][3]);

void
dopoo_matrix3F_inverse(double invMat[][3], double mat[][3]);

#endif
