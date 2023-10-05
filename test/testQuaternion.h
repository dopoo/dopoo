#ifndef __DOPOOTESTQUATERNION__
#define __DOPOOTESTQUATERNION__

#include <math.h>
#include "../inc/Quaternion.h"
#include "../inc/Vec.h"
#include "../inc/Matrix.h"

static inline void 
dopoo_testQuat()
{
  dopoo_vec3D v = {-1, 0, 0};
  dopoo_quatD q = {0, 1, 0, 1};
  dopoo_vec3D nv = dopoo_quatD_rotate(q, v);  
  dopoo_vec3D_print(nv, "nv");

  v = (dopoo_vec3D){-1, 1, 0};
  q = (dopoo_quatD){1, 1, 0, sqrt(2)};
  nv = dopoo_quatD_rotate(q, v);  
  dopoo_vec3D_print(nv, "nv");
}

static inline void 
dopoo_testQuatAndMat()
{
    dopoo_vec3D v = {0.5, -0.7, 1.2};
    dopoo_quatD q = {0.3, -1.2, 1.5, -1};
    dopoo_vec3D nv = dopoo_quatD_rotate(q, v);  
    dopoo_vec3D_print(nv, "quat rotate nv");

    double m[3][3];
    dopoo_quatD_q2m(m, q);
    nv = dopoo_mat3D_postRotate(m, v);
    dopoo_vec3D_print(nv, "matrix rotate nv");

    dopoo_quatD nq = dopoo_quatD_m2q(m);
    dopoo_quatD_print(q, "old q");
    dopoo_quatD_print(nq, "new q");
}

#endif