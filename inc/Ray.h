#ifndef __DOPOOBBOX__
#define __DOPOOBBOX__

#include <stdbool.h>
#include "Vec.h" 
#include "Map.h"
#include "Box.h"

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

bool
dopoo_rayD_intersectCylinder(const dopoo_rayD* ray, double h, double r, double* t0, double* t1);

void
dopoo_rayD_applyInverse(dopoo_rayD* ray, dopoo_mapD* map);

bool 
dopoo_rayD_intersectBox(const dopoo_rayD* ray, dopoo_vec3D min, dopoo_vec3D max, double* t0, double* t1);

#endif