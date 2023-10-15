#include <assert.h>
#include <math.h>
#include "../inc/Ray.h"
#include "../inc/Math.h"

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

dopoo_vec3D 
dopoo_rayD_computeP(const dopoo_rayD* ray, double t)
{
	return dopoo_vec3D_add(ray->p, dopoo_vec3D_scale(ray->d, t));
}

bool 
dopoo_rayD_intersectSphere(const dopoo_rayD* ray, dopoo_vec3D c, double r, double* t0, double* t1)
{
	assert(fabs(dopoo_vec3D_lengthSqr(ray->d) - 1) < deltaD);
    dopoo_vec3D cp = dopoo_vec3D_minus(ray->p, c);
	double distSqr = dopoo_vec3D_lengthSqr(dopoo_vec3D_cross(cp, ray->d));
    double rSqr = r * r;
	if(distSqr > rSqr)
	    return false;
	double pp3 = sqrt(dopoo_vec3D_lengthSqr(cp) - distSqr);
	double p1p3 = sqrt(rSqr - distSqr);
	double p2p3 = p1p3;
	double pp1 = pp3 - p1p3;
	double pp2 = pp3 + p2p3;
	*t0 = pp1;
	*t1 = pp2;

    return true;
}
