#ifndef __DOPOOPRIMITIVE__
#define __DOPOOPRIMITIVE__

#include <stdbool.h>
#include "Map.h"
#include "Spectrum.h"
#include "Ray.h"


typedef enum {
    SPHERE = 0,
    CYLINDER = 1,
    CUBOID   = 2,
    OTHER
} dopoo_primitiveType;


typedef struct
{
    dopoo_primitiveType type;
    double r;
    dopoo_vec3D c;
    dopoo_rgbI rgb;
}dopoo_sphere;

typedef struct
{
    dopoo_primitiveType type;
    double h;
    double r;
    dopoo_rgbI rgb;
    dopoo_mapD map;
}dopoo_cylinder;

typedef struct
{
    dopoo_primitiveType type;
    dopoo_vec3D min;
    dopoo_vec3D max;
    dopoo_rgbI rgb;
    dopoo_mapD map;
}dopoo_cuboid;

dopoo_sphere*
dopoo_sphere_create(dopoo_vec3D c, double r, dopoo_rgbI rgb);

dopoo_cylinder*
dopoo_cylinder_create(double h, double r, dopoo_rgbI rgb);

dopoo_cuboid*
dopoo_cuboid_create(dopoo_vec3D min, dopoo_vec3D max, dopoo_rgbI rgb);

void
dopoo_sphere_clear(dopoo_sphere* sphere);

void
dopoo_cylinder_clear(dopoo_cylinder* cylinder);

void
dopoo_cuboid_clear(dopoo_cuboid* cuboid);

dopoo_vec3D
dopoo_cylinder_computeNorm(double h, double r, dopoo_vec3D p);


#endif