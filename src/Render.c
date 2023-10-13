#include "../inc/Camera.h"


void
dopoo_render_sphere(const dopoo_camera* camera, dopoo_vec3D c, double r)
{
    dopoo_rayD ray;

    int32_t width = camera->film.width;
    int32_t height = camera->film.height;
    dopoo_rgbD rgb;
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
                rgb = (dopoo_rgbD){z, z, z};
            }
            else
            {
                rgb = (dopoo_rgbD){0, 0, 0};
            }
            
            (*(camera->film.pixel + j * width + i)) = dopoo_rgb_DtoI(rgb);
        }//loop over image height
    }//loop over image width
}