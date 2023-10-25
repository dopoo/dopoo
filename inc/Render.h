#ifndef __DOPOORENDER__
#define __DOPOORENDER__

#include "Camera.h" 
#include "Link.h"

void
dopoo_render_sphere(const dopoo_camera* camera, dopoo_vec3D c, double r, dopoo_vec3D rgb);

void
dopoo_render_cylinder(const dopoo_camera* camera, double h, double r, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb);

void
dopoo_render_cone(const dopoo_camera* camera, double h, double r0, double r1, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb);

void
dopoo_render_pyra(const dopoo_camera* camera, double h, double w0, double w1, double d0, double d1, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb);

void
dopoo_render_link(const dopoo_camera* camera, const dopoo_link* link, dopoo_vec3D lineRgb);

#endif