#ifndef __DOPOOMAP__ 
#define __DOPOOMAP__

#include "Quaternion.h"

typedef struct{
    dopoo_quatD r;
    dopoo_vec3D t;
    double s;
}dopoo_mapD;

dopoo_vec3D
dopoo_mapD_applyR(dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyRS(dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyRST(dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvR(dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvRS(dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvRST(dopoo_mapD* map, dopoo_vec3D v);

#endif