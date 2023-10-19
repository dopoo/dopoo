#include <math.h>
#include <stdio.h>
#include "../inc/Camera.h"
#include "../inc/Math.h"
#include "../inc/Primitive.h"


void
dopoo_render_sphere(const dopoo_camera* camera, dopoo_vec3D c, double r, dopoo_vec3D rgb)
{
    dopoo_rayD ray;

    int32_t width = camera->film.width;
    int32_t height = camera->film.height;
    dopoo_vec3D prgb;
    double t0, t1;

    for (int32_t j=0; j < height; ++j) {
        for (int32_t i=0; i < width; ++i) {
            double x = 0; 
            double y = 0;
            dopoo_camera_getRay(camera, &ray, i, j, x, y);
            if(dopoo_rayD_intersectSphere(&ray, c, r, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&ray, t0);
                dopoo_vec3D n = dopoo_vec3D_norm(dopoo_vec3D_minus(p0, c));
                double z = dopoo_vec3D_getz(n);
                prgb = dopoo_vec3D_scale(rgb, z);
            }
            else
            {
                prgb = (dopoo_vec3D){0, 0, 0};
            }
            
            (*(camera->film.pixel + j * width + i)) = dopoo_rgbI_fromVec(prgb);
        }//loop over image height
    }//loop over image width
}

void
dopoo_render_cylinder(const dopoo_camera* camera, double h, double r, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb)
{
    dopoo_rayD ray;

    int32_t width = camera->film.width;
    int32_t height = camera->film.height;
    dopoo_vec3D prgb;
    double t0, t1;
    double lineWidth = 0.01;

    for (int32_t j=0; j < height; ++j) {
        for (int32_t i=0; i < width; ++i) {
            double x = 0; 
            double y = 0;
            dopoo_camera_getRay(camera, &ray, i, j, x, y);
            dopoo_rayD_applyInverse(&ray, map);
            if(dopoo_rayD_intersectCylinder(&ray, h, r, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&ray, t0);
                dopoo_vec3D n = dopoo_cylinder_computeNorm(h, r, p0);
                n = dopoo_vec3D_norm(dopoo_mapD_applyRS(map, n));
                double z = dopoo_vec3D_getz(n);
                prgb = dopoo_vec3D_scale(rgb, z);
            }
            else if(dopoo_rayD_intersectCylinder(&ray, h+2*lineWidth, r+lineWidth, &t0, &t1))
            {
                prgb = lineRgb;
            }
            else
            {
                prgb = (dopoo_vec3D){0, 0, 0};
            }
            
            (*(camera->film.pixel + j * width + i)) = dopoo_rgbI_fromVec(prgb);
        }//loop over image height
    }//loop over image width
}