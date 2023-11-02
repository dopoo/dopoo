#include <math.h>
#include <stdio.h>
#include <float.h>
#include "../inc/Render.h"
#include "../inc/Math.h"
#include "../inc/Primitive.h"

void
dopoo_render_scene(const dopoo_camera* camera, const dopoo_scene* scene)
{
    dopoo_rayD ray;

    int32_t width = camera->film.width;
    int32_t height = camera->film.height;
    dopoo_vec3D prgb;
    double t0;
    int32_t linkIndex;
    int32_t nodeIndex;

    for (int32_t j=0; j < height; ++j) {
        for (int32_t i=0; i < width; ++i) {
            double x = 0; 
            double y = 0;
            dopoo_camera_getRay(camera, &ray, i, j, x, y);
            dopoo_vec3D n;
            double t;
            if(dopoo_scene_intersect(scene, &ray, &linkIndex, &nodeIndex, &n, &t))
            {
                dopoo_link* link = dopoo_scene_getLink(scene, linkIndex);
                if(t < LINETIME)
                {
                    double z = dopoo_vec3D_getz(n);
                    dopoo_vec3D rgb = dopoo_link_getRgb(link, nodeIndex);
                    prgb = dopoo_vec3D_scale(rgb, z);
                }
                else
                    prgb = dopoo_link_getLineRgb(link);
            }
            else
            {
                prgb = scene->bg;
            }
            
            (*(camera->film.pixel + j * width + i)) = dopoo_rgbI_fromVec(prgb);
        }//loop over image height
    }//loop over image width
}