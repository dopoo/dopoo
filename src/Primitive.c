#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "../inc/Math.h"
#include "../inc/Primitive.h"

dopoo_sphere*
dopoo_sphere_create(dopoo_vec3D c, double r, dopoo_vec3D rgb)
{
    dopoo_sphere* sphere = (dopoo_sphere*)malloc(sizeof(dopoo_sphere));
    sphere->type = SPHERE;
    sphere->c = c;
    sphere->r = r;
    sphere->rgb = rgb;
    return sphere;
}

dopoo_cylinder*
dopoo_cylinder_create(double h, double r, dopoo_vec3D rgb)
{
    dopoo_cylinder* cylinder = (dopoo_cylinder*)malloc(sizeof(dopoo_cylinder));
    cylinder->type = CYLINDER;
    cylinder->h = h;
    cylinder->r = r;
    cylinder->rgb = rgb;
    dopoo_mapD_init(&(cylinder->map));
    return cylinder;
}

dopoo_cuboid*
dopoo_cuboid_create(dopoo_vec3D min, dopoo_vec3D max, dopoo_vec3D rgb)
{
    dopoo_cuboid* cuboid = (dopoo_cuboid*)malloc(sizeof(dopoo_cuboid));
    cuboid->type = CUBOID;
    cuboid->min = min;
    cuboid->max = max;
    cuboid->rgb = rgb;
    dopoo_mapD_init(&(cuboid->map));
    return cuboid;
}

dopoo_cone*
dopoo_cone_create(double h, double r0, double r1, dopoo_vec3D rgb)
{
    dopoo_cone* cone = (dopoo_cone*)malloc(sizeof(dopoo_cone));
    cone->type = CONE;
    cone->h = h;
    cone->r0 = r0;
    cone->r1 = r1;
    cone->rgb = rgb;
    dopoo_mapD_init(&(cone->map));
    return cone;
}

dopoo_pyra*
dopoo_pyra_create(double h, double w0, double w1, double d0, double d1, dopoo_vec3D rgb)
{
    dopoo_pyra* pyra = (dopoo_pyra*)malloc(sizeof(dopoo_pyra));
    pyra->type = PYRA;
    pyra->h = h;
    pyra->w0 = w0;
    pyra->w1 = w1;
    pyra->d0 = d0;
    pyra->d1 = d1;
    pyra->rgb = rgb;
    dopoo_mapD_init(&(pyra->map));
    return pyra;
}

void
dopoo_sphere_clear(dopoo_sphere* sphere)
{
    free(sphere);
}

void
dopoo_cylinder_clear(dopoo_cylinder* cylinder)
{
    free(cylinder);
}

void
dopoo_cuboid_clear(dopoo_cuboid* cuboid)
{
    free(cuboid);
}

void
dopoo_cone_clear(dopoo_cone* cone)
{
    free(cone);
}

void
dopoo_pyra_clear(dopoo_pyra* pyra)
{
    free(pyra);
}

dopoo_vec3D
dopoo_cone_computeIntersect(double h, double r0, double r1, dopoo_vec3D pmin, dopoo_vec3D pmax)
{
    int32_t iter = 0;
    const int32_t maxIter = 10;
    double delta = 1e-3;
    do{
        dopoo_vec3D pm = dopoo_vec3D_scale(dopoo_vec3D_add(pmin, pmax), 0.5);
        double pmx = dopoo_vec3D_getx(pm);
        double pmy = dopoo_vec3D_gety(pm);
        double pmz = dopoo_vec3D_getz(pm);
        double rm = sqrt(pmx * pmx + pmz * pmz);
        double r = r0 + (r1 - r0) * (pmy + h/2) / h;
        if(fabs(rm - r) < delta || iter > maxIter)
        {
            return pm;
        }
        else if (rm > r) // outside
        {
            pmax = pm;
        }
        else if (rm < r) // inside
        {
            pmin = pm;
        }
        iter++;
    }while(true);

    return (dopoo_vec3D){0, 0, 0};
}

dopoo_vec3D
dopoo_cuboid_computeNorm(dopoo_vec3D min, dopoo_vec3D max, dopoo_vec3D p)
{
    dopoo_vec3D n = {0, 0, 0};
    double px = dopoo_vec3D_getx(p);
    double py = dopoo_vec3D_gety(p);
    double pz = dopoo_vec3D_getz(p);
    double minx = dopoo_vec3D_getx(min);
    double miny = dopoo_vec3D_gety(min);
    double minz = dopoo_vec3D_getz(min);
    double maxx = dopoo_vec3D_getx(max);
    double maxy = dopoo_vec3D_gety(max);
    double maxz = dopoo_vec3D_getz(max);
    if(fabs(px - minx) < deltaD)
    {
        n = (dopoo_vec3D){-1, 0, 0};
    }
    else if(fabs(px - maxx) < deltaD)
    {
        n = (dopoo_vec3D){1, 0, 0};
    }
    else if(fabs(py - miny) < deltaD)
    {
        n = (dopoo_vec3D){0, -1, 0};
    }
    else if(fabs(py - maxy) < deltaD)
    {
        n = (dopoo_vec3D){0, 1, 0};
    }
    else if(fabs(pz - minz) < deltaD)
    {
        n = (dopoo_vec3D){0, 0, -1};
    }
    else if(fabs(pz - maxz) < deltaD)
    {
        n = (dopoo_vec3D){0, 0, 1};
    }

    return n;
}

dopoo_vec3D
dopoo_cylinder_computeNorm(double h, double r, dopoo_vec3D p)
{
    double px = dopoo_vec3D_getx(p);
    double py = dopoo_vec3D_gety(p);
    double pz = dopoo_vec3D_getz(p);
    dopoo_vec3D n;
    
    if(fabs(px * px + pz * pz - r * r) < deltaD)
        n = (dopoo_vec3D){px, 0, pz};
    else if(py > 0)
        n = (dopoo_vec3D){0, 1, 0};
    else
        n = (dopoo_vec3D){0, -1, 0};
    
    //n = dopoo_vec3D_minus(p0, (dopoo_vec3D){0, h/2, 0});
    return n;
}

dopoo_vec3D
dopoo_cone_computeNorm(double h, double r0, double r1, dopoo_vec3D p)
{
    double px = dopoo_vec3D_getx(p);
    double py = dopoo_vec3D_gety(p);
    double pz = dopoo_vec3D_getz(p);
    dopoo_vec3D n;
    
    if(fabs(py - h/2) < deltaD)
    {
        n = (dopoo_vec3D){0, 1, 0};
    }
    else if (fabs(py + h/2) < deltaD)
    {
        n = (dopoo_vec3D){0, -1, 0};
    }
    else
    {
        dopoo_vec3D p0p1 = {0, h, 0};
        dopoo_vec3D p2 = {0, -h/2 - (h * r0)/(r1 - r0), 0};
        dopoo_vec3D pp2 = dopoo_vec3D_minus(p2, p);
        dopoo_vec3D np = dopoo_vec3D_cross(p0p1, pp2);
        n = dopoo_vec3D_cross(np, pp2);
        n = dopoo_vec3D_norm(n);
    }

    return n;
}

dopoo_vec3D
dopoo_pyra_computeNorm(double h, double w0, double w1, double d0, double d1, dopoo_vec3D p)
{
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
    dopoo_vec3D n4 = dopoo_vec3D_norm(dopoo_vec3D_cross(v1, v0));
    dopoo_vec3D p4 = {-w0/2, -h/2, d0/2};
    v1 = (dopoo_vec3D){(w1 - w0) / 2, -h, (d1 - d0) / 2};  
    dopoo_vec3D n5 = dopoo_vec3D_norm(dopoo_vec3D_cross(v0, v1));
    dopoo_vec3D p5 = {-w0/2, -h/2, -d0/2};

    double py = dopoo_vec3D_gety(p);
    if(fabs(py + h/2) < deltaD)
        return n0;
    else if (fabs(py - h/2) < deltaD)
        return n1;
    else if(fabs(dopoo_vec3D_dot(dopoo_vec3D_minus(p, p2), n2)) < deltaD)
        return n2;
    else if(fabs(dopoo_vec3D_dot(dopoo_vec3D_minus(p, p3), n3)) < deltaD)
        return n3;
    else if(fabs(dopoo_vec3D_dot(dopoo_vec3D_minus(p, p4), n4)) < deltaD)
        return n4;
    else if(fabs(dopoo_vec3D_dot(dopoo_vec3D_minus(p, p5), n5)) < deltaD)
        return n5;

    return (dopoo_vec3D){0,0,0};
}

bool
dopoo_prim_intersect(const void* prim, dopoo_rayD* ray, dopoo_vec3D* n, double* t)
{
    dopoo_primitiveType type = *((dopoo_primitiveType*)prim);
    double t0 = 0;
    double t1 = DBL_MAX;
    double lineWidth = 0.01;
    dopoo_rayD lRay = *ray;
    switch(type)
    {
        case SPHERE:
        {
            dopoo_sphere* sphere = (dopoo_sphere*)(prim);
            if(dopoo_rayD_intersectSphere(&lRay, sphere->c, sphere->r, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&lRay, t0);
                *n = dopoo_vec3D_norm(dopoo_vec3D_minus(p0, sphere->c));
                *t = t0;
                return true;
            }
            else if (dopoo_rayD_intersectSphere(&lRay, sphere->c, sphere->r + lineWidth, &t0, &t1))
            {
                *t = DBL_MAX;
                return true;
            }
            else
            {
                return false;
            }
        }
        case CYLINDER:
        {
            dopoo_cylinder* cylinder = (dopoo_cylinder*)(prim);
            dopoo_rayD_applyInverse(&lRay, &(cylinder->map));
            if(dopoo_rayD_intersectCylinder(&lRay, cylinder->h, cylinder->r, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&lRay, t0);
                *n = dopoo_cylinder_computeNorm(cylinder->h, cylinder->r, p0);
                *n = dopoo_vec3D_norm(dopoo_mapD_applyRS(&(cylinder->map), *n));
                *t = t0;
                return true;
            }
            else if (dopoo_rayD_intersectCylinder(&lRay, cylinder->h + 2 * lineWidth, cylinder->r + lineWidth, &t0, &t1))
            {
                *t = DBL_MAX;
                return true;
            }
            else
            {
                return false;
            }
        }
        
        case CUBOID:
        {
            dopoo_cuboid* cuboid = (dopoo_cuboid*)(prim);
            dopoo_rayD_applyInverse(&lRay, &(cuboid->map));
            dopoo_vec3D minl = dopoo_vec3D_minus(cuboid->min, (dopoo_vec3D){lineWidth, lineWidth, lineWidth});
            dopoo_vec3D maxl = dopoo_vec3D_add(cuboid->max, (dopoo_vec3D){lineWidth, lineWidth, lineWidth});
            if(dopoo_rayD_intersectBox(&lRay, cuboid->min, cuboid->max, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&lRay, t0);
                *n = dopoo_cuboid_computeNorm(cuboid->min, cuboid->max, p0);
                *n = dopoo_vec3D_norm(dopoo_mapD_applyRS(&(cuboid->map), *n));
                *t = t0;
                return true;
            }
            else if (dopoo_rayD_intersectBox(&lRay, minl, maxl, &t0, &t1))
            {
                *t = DBL_MAX;
                return true;
            }
            else
            {
                return false;
            }
        }

        case CONE:
        {
            dopoo_cone* cone = (dopoo_cone*)(prim);
            dopoo_rayD_applyInverse(&lRay, &(cone->map));
            if(dopoo_rayD_intersectCone(&lRay, cone->h, cone->r0, cone->r1, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&lRay, t0);
                *n = dopoo_cone_computeNorm(cone->h, cone->r0, cone->r1, p0);
                *n = dopoo_vec3D_norm(dopoo_mapD_applyRS(&(cone->map), *n));
                *t = t0;
                return true;
            }
            else if (dopoo_rayD_intersectCone(&lRay, cone->h + 2 * lineWidth, cone->r0 + lineWidth, cone->r1 + lineWidth, &t0, &t1))
            {
                *t = DBL_MAX;
                return true;
            }
            else
            {
                return false;
            }
        }

        case PYRA:
        {
            dopoo_pyra* pyra = (dopoo_pyra*)(prim);
            dopoo_rayD_applyInverse(&lRay, &(pyra->map));
            if(dopoo_rayD_intersectPyra(&lRay, pyra->h, pyra->w0, pyra->w1, pyra->d0, pyra->d1, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&lRay, t0);
                *n = dopoo_pyra_computeNorm(pyra->h, pyra->w0, pyra->w1, pyra->d0, pyra->d1, p0);
                *n = dopoo_vec3D_norm(dopoo_mapD_applyRS(&(pyra->map), *n));
                *t = t0;
                return true;
            }
            else if (dopoo_rayD_intersectPyra(&lRay, pyra->h + 2 * lineWidth, pyra->w0  + 2 * lineWidth, pyra->w1 + 2 * lineWidth, 
                                              pyra->d0 + 2 * lineWidth, pyra->d1 + 2 * lineWidth, &t0, &t1))
            {
                *t = DBL_MAX;
                return true;
            }
            else
            {
                return false;
            }
        }

        default:
        return false;
    }
}

void
dopoo_prim_clear(void* prim)
{
    dopoo_primitiveType type = *((dopoo_primitiveType*)prim);
    switch(type)
    {
        case SPHERE:
            return dopoo_sphere_clear((dopoo_sphere*)(prim));
        case CYLINDER:
            return dopoo_cylinder_clear((dopoo_cylinder*)(prim));
        case CUBOID:
            return dopoo_cuboid_clear((dopoo_cuboid*)(prim));
        case CONE:
            return dopoo_cone_clear((dopoo_cone*)(prim));
        case PYRA:
            return dopoo_pyra_clear((dopoo_pyra*)(prim));
        default:
            break;
    }
}

dopoo_vec3D
dopoo_prim_getRgb(void* prim)
{
    dopoo_primitiveType type = *((dopoo_primitiveType*)prim);
    switch(type)
    {
        case SPHERE:
            return ((dopoo_sphere*)(prim))->rgb;
        case CYLINDER:
            return ((dopoo_cylinder*)(prim))->rgb;
        case CUBOID:
            return ((dopoo_cuboid*)(prim))->rgb;
        case CONE:
            return ((dopoo_cone*)(prim))->rgb;
        case PYRA:
            return ((dopoo_pyra*)(prim))->rgb;
        default:
            return (dopoo_vec3D){0, 0, 0};
    }
}