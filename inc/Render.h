#ifndef __DOPOORENDER__
#define __DOPOORENDER__

#include "Camera.h" 

void
dopoo_render_sphere(const dopoo_camera* camera, dopoo_vec3D c, double r, dopoo_vec3D rgb);

void
dopoo_render_cylinder(const dopoo_camera* camera, double h, double r, dopoo_mapD* map, dopoo_vec3D rgb);


#endif