#include "../inc/Primitive.h"

#include "stdlib.h"

dopoo_sphere*
dopoo_sphere_create(dopoo_vec3D c, double r, dopoo_rgbI rgb)
{
    dopoo_sphere* sphere = (dopoo_sphere*)malloc(sizeof(dopoo_sphere));
    sphere->type = SPHERE;
    sphere->c = c;
    sphere->r = r;
    sphere->rgb = rgb;
    return sphere;
}

dopoo_cylinder*
dopoo_cylinder_create(double h, double r, dopoo_rgbI rgb)
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
dopoo_cuboid_create(dopoo_vec3D min, dopoo_vec3D max, dopoo_rgbI rgb)
{
    dopoo_cuboid* cuboid = (dopoo_cuboid*)malloc(sizeof(dopoo_cuboid));
    cuboid->type = CUBOID;
    cuboid->min = min;
    cuboid->max = max;
    cuboid->rgb = rgb;
    dopoo_mapD_init(&(cuboid->map));
    return cuboid;
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