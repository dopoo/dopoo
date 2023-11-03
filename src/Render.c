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

    dopoo_vec3D cameraPos = camera->map.t;
    for (int32_t j=0; j < height; ++j) {
        for (int32_t i=0; i < width; ++i) {
            double x = 0; 
            double y = 0;
            dopoo_camera_getRay(camera, &ray, i, j, x, y);
            dopoo_vec3D p;
            dopoo_vec3D n;
            double t;
            if(dopoo_scene_intersect(scene, &ray, &linkIndex, &nodeIndex, &p, &n, &t))
            {
                dopoo_link* link = dopoo_scene_getLink(scene, linkIndex);
                if(t < LINETIME)
                {
                    dopoo_vec3D rgb = dopoo_link_getRgb(link, nodeIndex);
                    //double z = dopoo_vec3D_getz(n);
                    //prgb = dopoo_vec3D_scale(rgb, z);
                    
                    dopoo_vec3D wi = dopoo_vec3D_norm(dopoo_vec3D_minus(cameraPos, p));
                    double cosTheta = dopoo_vec3D_dot(wi, n);
                    prgb = dopoo_vec3D_scale(rgb, cosTheta);
                }
                else if (link->drawBorderLine)
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