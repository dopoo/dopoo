#include <math.h>
#include "../inc/Vec.h"
#include "../inc/Common.h"
#include "../inc/Math.h"


double 
dopoo_vec3D_dot(dopoo_vec3D v0, dopoo_vec3D v1)
{
    return (v0.x * v1.x +
            v0.y * v1.y +
            v0.z * v1.z);
}

dopoo_vec3D
dopoo_vec3D_cross(dopoo_vec3D v0, dopoo_vec3D v1)
{
    dopoo_vec3D dst;
    dst.x = v0.y * v1.z - v0.z * v1.y;
    dst.y = v0.z * v1.x - v0.x * v1.z;
    dst.z = v0.x * v1.y - v0.y * v1.x;
    return dst;
}

double
dopoo_vec3D_length(dopoo_vec3D v)
{
    return sqrt(v.x * v.x +
                v.y * v.y +
                v.z * v.z);
}

double
dopoo_vec3D_lengthSqr(dopoo_vec3D v)
{
    return v.x * v.x + 
           v.y * v.y + 
           v.z * v.z;
}

dopoo_vec3D
dopoo_vec3D_scale(dopoo_vec3D v, double scale)
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
    return v;
}

dopoo_vec3D
dopoo_vec3D_add(dopoo_vec3D v0, dopoo_vec3D v1)
{
    return (dopoo_vec3D){v0.x + v1.x,
                         v0.y + v1.y,
                         v0.z + v1.z};
}

dopoo_vec3D
dopoo_vec3D_minus(dopoo_vec3D v0, dopoo_vec3D v1)
{
    return (dopoo_vec3D){v0.x - v1.x,
                         v0.y - v1.y,
                         v0.z - v1.z};
}

dopoo_vec3D 
dopoo_vec3D_inv(dopoo_vec3D v)
{
    v.x = 1. / v.x;
    v.y = 1. / v.y;
    v.z = 1. / v.z;
    return v;
}

dopoo_vec3D
dopoo_vec3D_norm(dopoo_vec3D v)
{
    double l = dopoo_vec3D_length(v);
    return dopoo_vec3D_scale(v, 1./ l);
}

double
dopoo_vec3D_getz(dopoo_vec3D v)
{
    return v.z;
}

double
dopoo_vec3D_gety(dopoo_vec3D v)
{
    return v.y;
}

double
dopoo_vec3D_getx(dopoo_vec3D v)
{
    return v.x;
}

dopoo_vec3D
dopoo_vec3D_clamp(dopoo_vec3D v)
{
    v.x = dopoo_double_clamp(v.x, 0, 1.0);
    v.y = dopoo_double_clamp(v.y, 0, 1.0);
    v.z = dopoo_double_clamp(v.z, 0, 1.0);
    return v;
}

void
dopoo_vec3D_print(dopoo_vec3D v, const char* label)
{
    dopoo_print(true, "%s:\t %f %f %f\n", label, v.x, v.y, v.z);
}

