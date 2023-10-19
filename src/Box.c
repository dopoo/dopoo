#include "../inc/Box.h"

bool
dopoo_boxD_isZero(const dopoo_boxD* box)
{
    double minx = dopoo_vec3D_getx(box->min);
    double miny = dopoo_vec3D_gety(box->min);
    double minz = dopoo_vec3D_getz(box->min);
    double maxx = dopoo_vec3D_getx(box->max);
    double maxy = dopoo_vec3D_gety(box->max);
    double maxz = dopoo_vec3D_getz(box->max);

    return (minx >= maxx || miny >= maxy || minz >= maxz);
}