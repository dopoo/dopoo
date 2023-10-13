#ifndef __DOPOOBBOX__
#define __DOPOOBBOX__

#include "Vec.h" 
#include "stdbool.h"

typedef struct {
	dopoo_vec3D p, d, invD;
    double t0, t1;
} dopoo_rayD;

void 
dopoo_rayD_setP(dopoo_rayD* ray, dopoo_vec3D p);

void 
dopoo_rayD_setD(dopoo_rayD* ray, dopoo_vec3D d);

void 
dopoo_rayD_setT0(dopoo_rayD* ray, double t0);

void 
dopoo_rayD_setT1(dopoo_rayD* ray, double t1);

dopoo_vec3D 
dopoo_rayD_computeP(const dopoo_rayD* ray, double t);

bool 
dopoo_rayD_intersectSphere(const dopoo_rayD* ray, dopoo_vec3D c, double r, double* t0, double* t1);

#endif