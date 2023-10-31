#include <assert.h>
#include <math.h>
#include <float.h>
#include "../inc/Ray.h"
#include "../inc/Math.h"
#include "../inc/Primitive.h"

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
dopoo_rayD_applyInverse(dopoo_rayD* ray, const dopoo_mapD* map)
{
    ray->p = dopoo_mapD_applyInvRST(map, ray->p);
    ray->d = dopoo_mapD_applyInvR(map, ray->d);
    ray->invD = dopoo_vec3D_inv(ray->d);
}

bool 
dopoo_rayD_intersectSphere(const dopoo_rayD* ray, double r, double* t0, double* t1)
{
    assert(fabs(dopoo_vec3D_lengthSqr(ray->d) - 1) < deltaD);
    dopoo_vec3D c = {0, 0, 0};
    dopoo_vec3D pc = dopoo_vec3D_minus(c, ray->p);
    double pp3 = dopoo_vec3D_dot(pc, ray->d);
    if(pp3 <0)
        return false;
    double distSqr = dopoo_vec3D_lengthSqr(pc) - pp3 * pp3;
    double rSqr = r * r;
    if(distSqr > rSqr)
        return false;

    double p1p3 = sqrt(rSqr - distSqr);
    double p2p3 = p1p3;
    double pp1 = pp3 - p1p3;
    double pp2 = pp3 + p2p3;
    *t0 = pp1;
    *t1 = pp2;
    *t0 = max(*t0, ray->t0);
    *t1 = min(*t1, ray->t1);
    if (*t0 > *t1) return false;

    return true;
}

bool
dopoo_rayD_intersectCylinder(const dopoo_rayD* ray, double h, double r, double* t0, double* t1)
{
    assert(fabs(dopoo_vec3D_lengthSqr(ray->d) - 1) < deltaD);
    dopoo_vec3D min = {-r, -h/2, -r};
    dopoo_vec3D max = { r,  h/2,  r};
    
    double tb0, tb1;
    bool interBox = dopoo_rayD_intersectBox(ray, min, max, &tb0, &tb1);
    if(!interBox)
        return false;

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

    dopoo_vec3D min = {-r1, -h/2, -r1};
    dopoo_vec3D max = { r1,  h/2, r1};
    
    double tb0, tb1;
    bool interBox = dopoo_rayD_intersectBox(ray, min, max, &tb0, &tb1);
    if(!interBox)
        return false;

    if(fabs(fabs(dy) - 1) < deltaD)  //case 1 parellel
    {
        double dist = sqrt(px * px + pz * pz);
        if(dist > r1)
            return false;
        else if (dist <= r0)
        {
            *t0 = (-h/2 - py) / dy;
        }
        else
        {
            *t0 = (-h/2 - py) / dy + (dist - r0) * h / ((r1 - r0) * dy);
        }
        *t1 = (h/2 - py) / dy;
        if (*t0 > *t1) 
            dopoo_double_swap(t0, t1); 
    }
    else if(fabs(dy) < deltaD)
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
        *t0 = max(*t0, ray->t0);
        *t1 = min(*t1, ray->t1);
        if (*t0 > *t1) return false;
    } 
    else
    {
        double tc0 = (-h/2 - py) / dy;
        double tc1 = ( h/2 - py) / dy;
        dopoo_vec3D pc0 = dopoo_rayD_computeP(ray, tc0);
        dopoo_vec3D pc1 = dopoo_rayD_computeP(ray, tc1);
        double pc0x = dopoo_vec3D_getx(pc0);
        double pc0z = dopoo_vec3D_getz(pc0);
        double pc1x = dopoo_vec3D_getx(pc1);
        double pc1z = dopoo_vec3D_getz(pc1);
        double rc0 = sqrt(pc0x * pc0x + pc0z * pc0z);
        double rc1 = sqrt(pc1x * pc1x + pc1z * pc1z);

        if(rc0 <= r0 && rc1 <= r1) // two on circle
        {
            if(tc0 > tc1)
                dopoo_double_swap(&tc0, &tc1); 
            *t0 = tc0;
            *t1 = tc1;
        }
        else if (rc0 <= r0)   // one on circle
        {
            dopoo_vec3D pmin = pc0;
            dopoo_vec3D pmax=  dopoo_rayD_computeP(ray, min(max(tc1, tb0), tb1));
            dopoo_vec3D pm = dopoo_cone_computeIntersect(h, r0, r1, pmin, pmax);
            double pmy = dopoo_vec3D_gety(pm);
            *t0 = tc0;
            *t1 = (pmy - py) / dy;
            if(*t0 > *t1)
                dopoo_double_swap(t0, t1);
        }
        else if (rc1 <= r1)     // one on circle
        {
            dopoo_vec3D pmin = pc1;
            dopoo_vec3D pmax = dopoo_rayD_computeP(ray, min(max(tc0, tb0), tb1));
            dopoo_vec3D pm = dopoo_cone_computeIntersect(h, r0, r1, pmin, pmax);
            double pmy = dopoo_vec3D_gety(pm);
            *t0 = tc1;
            *t1 = (pmy - py) / dy;
            if(*t0 > *t1)
                dopoo_double_swap(t0, t1);
        }
        else        // not on circle
        {
            dopoo_vec3D p0p1 = {0, h, 0};
            dopoo_vec3D n = dopoo_vec3D_norm(dopoo_vec3D_cross(p0p1, ray->d));
            dopoo_vec3D p0p = ray->p;
            double dist = dopoo_vec3D_dot(p0p, n);
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
            if(pp2 < 0)
                return false;

            dopoo_vec3D pi = dopoo_rayD_computeP(ray, pp2);
            double pix = dopoo_vec3D_getx(pi);
            double piy = dopoo_vec3D_gety(pi);
            double piz = dopoo_vec3D_getz(pi);
            double ri = sqrt(pix * pix + piz * piz);
            double r = r0 + (r1 - r0) * (piy + h/2) / h;
            if(ri > r || piy > h/2 || piy < -h/2)
                return false;
            if(fabs(ri - r) < deltaD)
            {
                *t0 = *t1 = (piy - py) / dy;
                if(*t0 < 0)
                    return false;
            }
            else
            {
                dopoo_vec3D pmin = pi;
                dopoo_vec3D pmax0 = dopoo_rayD_computeP(ray, min(max(tc0, tb0), tb1));
                dopoo_vec3D pmax1 = dopoo_rayD_computeP(ray, min(max(tc1, tb0), tb1));
                dopoo_vec3D pm0 = dopoo_cone_computeIntersect(h, r0, r1, pmin, pmax0);
                dopoo_vec3D pm1 = dopoo_cone_computeIntersect(h, r0, r1, pmin, pmax1);
                double pm0y = dopoo_vec3D_gety(pm0);
                double pm1y = dopoo_vec3D_gety(pm1);
                *t0 = (pm0y - py) / dy;
                *t1 = (pm1y - py) / dy;
                if(*t0 > *t1)
                    dopoo_double_swap(t0, t1);
            }
        }   
    }

    return true;
}

bool
dopoo_rayD_intersectPyra(const dopoo_rayD* ray, double h, double w0, double w1, double d0, double d1, double* t0, double* t1)
{
    double w = max(w0, w1);
    double d = max(d0, d1);
    dopoo_vec3D min = {-w/2, -h/2, -d/2};
    dopoo_vec3D max = { w/2,  h/2, d/2};
    
    double tb0, tb1;
    bool interBox = dopoo_rayD_intersectBox(ray, min, max, &tb0, &tb1);
    if(!interBox)
        return false;

    dopoo_vec3D n0 = {0, -1, 0};
    dopoo_vec3D p0 = {0, -h/2, 0};
    dopoo_vec3D n1 = {0, 1, 0};
    dopoo_vec3D p1 = {0, h/2, 0};
    dopoo_vec3D v0 = {0, 0, -1};
    dopoo_vec3D v1 = {(w1 - w0) / 2, -h, (d0 - d1) / 2};  
    dopoo_vec3D n2 = dopoo_vec3D_norm(dopoo_vec3D_cross(v0, v1));
    dopoo_vec3D p2 = {-w0/2, -h/2, d0/2};
    v1 = (dopoo_vec3D){(w1 - w0) / 2, h, (d1 - d0) / 2};  
    dopoo_vec3D n3 = dopoo_vec3D_norm(dopoo_vec3D_cross(v0, v1));
    dopoo_vec3D p3 = {w0/2, -h/2, d0/2};
    v0 = (dopoo_vec3D){1, 0, 0};
    v1 = (dopoo_vec3D){(w1 - w0) / 2, -h, (d0 - d1) / 2};  
    dopoo_vec3D n4 = dopoo_vec3D_norm(dopoo_vec3D_cross(v0, v1));
    dopoo_vec3D p4 = {-w0/2, -h/2, d0/2};
    v1 = (dopoo_vec3D){(w1 - w0) / 2, -h, (d1 - d0) / 2};  
    dopoo_vec3D n5 = dopoo_vec3D_norm(dopoo_vec3D_cross(v0, v1));
    dopoo_vec3D p5 = {-w0/2, -h/2, -d0/2};

    double _d0 = dopoo_vec3D_dot(n0, p0);
    double _d1 = dopoo_vec3D_dot(n1, p1);
    double _d2 = dopoo_vec3D_dot(n2, p2);
    double _d3 = dopoo_vec3D_dot(n3, p3);
    double _d4 = dopoo_vec3D_dot(n4, p4);
    double _d5 = dopoo_vec3D_dot(n5, p5);

    double t;
    bool intersect = false;
    *t0 = DBL_MAX;
    *t1 = -DBL_MAX;
    if(dopoo_rayD_intersectPlane(ray, n0, _d0, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2x = dopoo_vec3D_getx(p2);
        double p2z = dopoo_vec3D_getz(p2);
        if(p2x >= -w0/2 && p2x <= w0/2 && p2z >= -d0/2 && p2z <= d0/2)
        {
            *t0 = min(*t0, t);
            *t1 = max(*t1, t);
            intersect = true;
        }
    }

    if(dopoo_rayD_intersectPlane(ray, n1, _d1, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2x = dopoo_vec3D_getx(p2);
        double p2z = dopoo_vec3D_getz(p2);
        if(p2x >= -w1/2 && p2x <= w1/2 && p2z >= -d1/2 && p2z <= d1/2)
        {
            *t0 = min(*t0, t);
            *t1 = max(*t1, t);
            intersect = true;
        }
    }

    if(dopoo_rayD_intersectPlane(ray, n2, _d2, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2y = dopoo_vec3D_gety(p2);
        if(p2y >= -h / 2 && p2y <= h / 2)
        {
            double p2z = dopoo_vec3D_getz(p2);
            double zm = d0/2 + (d1 - d0) * (p2y + h/2) / (2 * h);
            if(p2z >= -zm && p2z <= zm)
            {
                *t0 = min(*t0, t);
                *t1 = max(*t1, t);
                intersect = true;
            }
        }
    }

    if(dopoo_rayD_intersectPlane(ray, n3, _d3, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2y = dopoo_vec3D_gety(p2);
        if(p2y >= -h / 2 && p2y <= h / 2)
        {
            double p2z = dopoo_vec3D_getz(p2);
            double zm = d0/2 + (d1 - d0) * (p2y + h/2) / (2 * h);
            if(p2z >= -zm && p2z <= zm)
            {
                *t0 = min(*t0, t);
                *t1 = max(*t1, t);
                intersect = true;
            }
        }
    }

    if(dopoo_rayD_intersectPlane(ray, n4, _d4, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2y = dopoo_vec3D_gety(p2);
        if(p2y >= -h / 2 && p2y <= h / 2)
        {
            double p2x = dopoo_vec3D_getx(p2);
            double xm = w0/2 + (w1 - w0) * (p2y + h/2) / (2 * h);
            if(p2x >= -xm && p2x <= xm)
            {
                *t0 = min(*t0, t);
                *t1 = max(*t1, t);
                intersect = true;
            }
        }
    }

    if(dopoo_rayD_intersectPlane(ray, n5, _d5, &t))
    {
        dopoo_vec3D p2 = dopoo_rayD_computeP(ray, t);
        double p2y = dopoo_vec3D_gety(p2);
        if(p2y >= -h / 2 && p2y <= h / 2)
        {
            double p2x = dopoo_vec3D_getx(p2);
            double xm = w0/2 + (w1 - w0) * (p2y + h/2) / (2 * h);
            if(p2x >= -xm && p2x <= xm)
            {
                *t0 = min(*t0, t);
                *t1 = max(*t1, t);
                intersect = true;
            }
        }
    }

    return intersect;
}

