#ifndef __DOPOOMAP__
#define __DOPOOMAP__

#include "Quaternion.h"

typedef struct{
    dopoo_quatD r;  //rotation
    dopoo_vec3D t;  //transition
    double s;       // scale
}dopoo_mapD;

dopoo_vec3D
dopoo_mapD_applyR(const dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyRS(const dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyRST(const dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvR(const dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvRS(const dopoo_mapD* map, dopoo_vec3D v);

dopoo_vec3D
dopoo_mapD_applyInvRST(const dopoo_mapD* map, dopoo_vec3D v);

void
dopoo_mapD_addTransit(dopoo_mapD* map, dopoo_vec3D v);

void
dopoo_mapD_addRotate(dopoo_mapD* map, dopoo_quatD q);

void
dopoo_mapD_init(dopoo_mapD* map);


#endif