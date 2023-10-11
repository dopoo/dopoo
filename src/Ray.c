#include "../inc/Ray.h"

void 
dopoo_rayD_setP(dopoo_rayD* ray, dopoo_vec3D p)
{ ray->p = p; }

void 
dopoo_rayD_setD(dopoo_rayD* ray, dopoo_vec3D d) 
{ 
	ray->d = d;
	ray->invD = dopoo_vec3D_inv(ray->d);
}

void 
dopoo_rayD_setT0(dopoo_rayD* ray, double t0) { ray->t0 = t0; }

void 
dopoo_rayD_setT1(dopoo_rayD* ray, double t1) { ray->t1 = t1; } 

bool
dopoo_rayD_test(const dopoo_rayD* ray, double t) 
{
    return ( t >= ray->t0 && t <= ray->t1 );
}