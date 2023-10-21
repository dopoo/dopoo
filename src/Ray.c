#include <assert.h>
#include <math.h>
#include "../inc/Ray.h"
#include "../inc/Math.h"

void 
dopoo_rayD_setP(dopoo_rayD* ray, dopoo_vec3D p)
{ 
    ray->p = p; 
}

void 
dopoo_rayD_setD(dopoo_rayD* ray, dopoo_vec3D d) 
{ 
    ray->d = d;
    ray->invD = dopoo_vec3D_inv(ray->d);
}

void 
dopoo_rayD_setT0(dopoo_rayD* ray, double t0) 
{ 
    ray->t0 = t0; 
}

void 
dopoo_rayD_setT1(dopoo_rayD* ray, double t1) 
{ 
    ray->t1 = t1; 
} 

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

void
dopoo_rayD_applyInverse(dopoo_rayD* ray, dopoo_mapD* map)
{
    ray->p = dopoo_mapD_applyInvRST(map, ray->p);
    ray->d = dopoo_mapD_applyInvR(map, ray->d);
    ray->invD = dopoo_vec3D_inv(ray->d);
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
    if (*t0 > *t1) return false;

    return true;
}

bool
dopoo_rayD_intersectCylinder(const dopoo_rayD* ray, double h, double r, double* t0, double* t1)
{
    assert(fabs(dopoo_vec3D_lengthSqr(ray->d) - 1) < deltaD);
    double px = dopoo_vec3D_getx(ray->p);
    double py = dopoo_vec3D_gety(ray->p);
    double pz = dopoo_vec3D_getz(ray->p);
    double dx = dopoo_vec3D_getx(ray->d);
    double dy = dopoo_vec3D_gety(ray->d);
    double dz = dopoo_vec3D_getz(ray->d);
    if(fabs(fabs(dy) - 1) < deltaD)  //case 1 parellel
    {
        double dist = sqrt(px * px + pz * pz);
        if(dist > r)
            return false;
        *t0 = (-h/2 - py) / dy;
        *t1 = (h/2 - py) / dy;
        if (*t0 > *t1) 
            dopoo_double_swap(t0, t1); 
    }
    else if (fabs(dy) < deltaD)      //case2 perpendicular
    {
        if(py > h/2 || py < -h/2)
            return false;
        dopoo_vec3D c = {0, py, 0};
        dopoo_vec3D cp = dopoo_vec3D_minus(ray->p, c);
        double distSqr = dopoo_vec3D_lengthSqr(dopoo_vec3D_cross(cp, ray->d));
        double rSqr = r * r;
        if(distSqr > rSqr)
            return false;
        double pp2 = sqrt(dopoo_vec3D_lengthSqr(cp) - distSqr);
        double p3p2 = sqrt(rSqr - distSqr);
        double p4p2 = p3p2;
        *t0 = pp2 - p3p2;
        *t1 = pp2 + p4p2;
        if (*t0 > *t1) return false;
    }
    else                            // case3 other
    {
        double t00 = (-h/2 - py) / dy;
        double t10 = (h/2 - py) / dy;
        if(t00 > t10)
            dopoo_double_swap(&t00, &t10); 
        dopoo_vec3D p0p1 = {0, h, 0};
        dopoo_vec3D n = dopoo_vec3D_norm(dopoo_vec3D_cross(p0p1, ray->d));
        dopoo_vec3D p0p = ray->p;
        double dist = dopoo_vec3D_dot(p0p, n);
        if(fabs(dist) > r)
            return false;
        dopoo_vec3D _p = dopoo_vec3D_minus(ray->p, dopoo_vec3D_scale(n, dist));
        double pp2;
        if(fabs(dx) > deltaD)
        {
            double _px = dopoo_vec3D_getx(_p);
            pp2 = -_px/dx; 
        }
        else
        {
            double _pz = dopoo_vec3D_getz(_p);
            pp2 = -_pz/dz; 
        }
		
        double p3p2 = sqrt(r * r - dist * dist) / sqrt(dx * dx + dz * dz);
        double p4p2 = p3p2;
        double t01 = pp2 - p3p2;
        double t11 = pp2 + p4p2;

        *t0 = max(t00, t01);
        *t1 = min(t10, t11);
        if (*t0 > *t1) return false;
    }

    return true;
}

bool 
dopoo_rayD_intersectBox(const dopoo_rayD* ray, dopoo_vec3D min, dopoo_vec3D max, double* t0, double* t1)
{
    double minx = dopoo_vec3D_getx(min);
    double miny = dopoo_vec3D_gety(min);
    double minz = dopoo_vec3D_getz(min);
    double maxx = dopoo_vec3D_getx(max);
    double maxy = dopoo_vec3D_gety(max);
    double maxz = dopoo_vec3D_getz(max);

    if (minx >= maxx || miny >= maxy || minz >= maxz)
        return false;

    *t0 = ray->t0;
    *t1 = ray->t1;
    double _min[3] = {minx, miny, minz};
    double _max[3] = {maxx, maxy, maxz};
    double p[3]   = {dopoo_vec3D_getx(ray->p), dopoo_vec3D_gety(ray->p), dopoo_vec3D_getz(ray->p)};
    double d[3]   = {dopoo_vec3D_getx(ray->d), dopoo_vec3D_gety(ray->d), dopoo_vec3D_getz(ray->d)};

    for (int32_t i = 0; i < 3; ++i) {
        double a = (_min[i] - p[i]) / d[i];
        double b = (_max[i] - p[i]) / d[i];
        if (a > b) dopoo_double_swap(&a, &b);
        if (a > *t0) *t0 = a;
        if (b < *t1) *t1 = b;
        if (*t0 > *t1) return false;
    }
    return true;
}

bool 
dopoo_rayD_intersectPlane(const dopoo_rayD* ray, dopoo_vec3D n, double d, double* t)
{
    const double cos = dopoo_vec3D_dot(ray->d, n);
    if (fabs(cos) < deltaD)   //parallel
        return false;
    *t = (d - dopoo_vec3D_dot(ray->p, n))/cos;
    return dopoo_rayD_test(ray, *t);
}

bool
dopoo_rayD_intersectCone(const dopoo_rayD* ray, double h, double r0, double r1, double* t0, double* t1)
{
    double px = dopoo_vec3D_getx(ray->p);
    double py = dopoo_vec3D_gety(ray->p);
    double pz = dopoo_vec3D_getz(ray->p);
    double dx = dopoo_vec3D_getx(ray->d);
    double dy = dopoo_vec3D_gety(ray->d);
    double dz = dopoo_vec3D_getz(ray->d);
    if(fabs(dy) < deltaD)
    {
        if(py > h/2 || py < -h/2)
            return false;
        dopoo_vec3D c = {0, py, 0};
        dopoo_vec3D cp = dopoo_vec3D_minus(ray->p, c);
        double distSqr = dopoo_vec3D_lengthSqr(dopoo_vec3D_cross(cp, ray->d));
        double r = r0 + (r1 - r0) * (py + h/2) / h;
        double rSqr = r * r;
        if(distSqr > rSqr)
            return false;
        double pp2 = sqrt(dopoo_vec3D_lengthSqr(cp) - distSqr);
        double p3p2 = sqrt(rSqr - distSqr);
        double p4p2 = p3p2;
        *t0 = pp2 - p3p2;
        *t1 = pp2 + p4p2;
        if (*t0 > *t1) return false;
    } 
    else
    {

    }

    return true;
}
