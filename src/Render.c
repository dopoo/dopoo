#include <math.h>
#include <stdio.h>
#include <float.h>
#include "../inc/Render.h"
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

void
dopoo_render_cone(const dopoo_camera* camera, double h, double r0, double r1, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb)
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
            if(dopoo_rayD_intersectCone(&ray, h, r0, r1, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&ray, t0);
                dopoo_vec3D n = dopoo_cone_computeNorm(h, r0, r1, p0);
                n = dopoo_vec3D_norm(dopoo_mapD_applyRS(map, n));
                double z = dopoo_vec3D_getz(n);
                prgb = dopoo_vec3D_scale(rgb, z);
            }
            else if(dopoo_rayD_intersectCone(&ray, h+2*lineWidth, r0+lineWidth, r1 + lineWidth, &t0, &t1))
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

void
dopoo_render_pyra(const dopoo_camera* camera, double h, double w0, double w1, double d0, double d1, dopoo_mapD* map, dopoo_vec3D rgb, dopoo_vec3D lineRgb)
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
            if(dopoo_rayD_intersectPyra(&ray, h, w0, w1, d0, d1, &t0, &t1))
            {
                dopoo_vec3D p0 = dopoo_rayD_computeP(&ray, t0);
                dopoo_vec3D n = dopoo_pyra_computeNorm(h, w0, w1, d0, d1, p0);
                n = dopoo_vec3D_norm(dopoo_mapD_applyRS(map, n));
                double z = dopoo_vec3D_getz(n);
                prgb = dopoo_vec3D_scale(rgb, z);
            }
            else if(dopoo_rayD_intersectPyra(&ray, h+2*lineWidth, w0+lineWidth, w1 + lineWidth, d0 + lineWidth, d1 + lineWidth, &t0, &t1))
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

void
dopoo_render_link(const dopoo_camera* camera, const dopoo_link* link, dopoo_vec3D lineRgb)
{
    dopoo_rayD ray;

    int32_t width = camera->film.width;
    int32_t height = camera->film.height;
    dopoo_vec3D prgb;
    double t0;
    int32_t num;

    for (int32_t j=0; j < height; ++j) {
        for (int32_t i=0; i < width; ++i) {
            double x = 0; 
            double y = 0;
            dopoo_camera_getRay(camera, &ray, i, j, x, y);
            dopoo_vec3D n;
            double t;
            if(dopoo_link_intersect(link, &ray, &num, &n, &t))
            {
                if(t < DBL_MAX)
                {
                    double z = dopoo_vec3D_getz(n);
                    dopoo_vec3D rgb = dopoo_link_getRgb(link, num);
                    prgb = dopoo_vec3D_scale(rgb, z);
                }
                else
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