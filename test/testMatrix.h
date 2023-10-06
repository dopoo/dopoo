#ifndef __DOPOOTESTMATRIX__
#define __DOPOOTESTMATRIX__

#include <math.h>
#include "../inc/Quaternion.h"
#include "../inc/Vec.h"
#include "../inc/Matrix.h"

static inline void 
dopoo_testMat()
{
    dopoo_quatD q = dopoo_quatD_create(0.3, -1.2, 1.5, -1);
    double m[3][3];
    dopoo_quatD_q2m(m, q);
    
    double im[3][3];
    dopoo_mat3D_inverse(im, m);

    double mt[3][3];
    dopoo_mat3D_transpose(mt, m);

    dopoo_mat3D_print(m, "M");
    dopoo_mat3D_print(im, "IM");
    dopoo_mat3D_print(mt, "MT");
}



#endif