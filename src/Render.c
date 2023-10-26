#include <math.h>
#include <stdio.h>
#include <float.h>
#include "../inc/Render.h"
#include "../inc/Math.h"
#include "../inc/Primitive.h"


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