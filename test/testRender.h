#ifndef __DOPOOTESTRender__
#define __DOPOOTESTRender__

#include "../inc/Render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdPartyLibrary/stb_image_write.h"

#define HRESOLUTION 960
#define VRESOLUTION 720

static inline void 
dopoo_testRenderSphere()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(HRESOLUTION, VRESOLUTION, q, t, ORTHOGRAPHICCAMERA);

    // create sphere
    dopoo_vec3D c = {0, 0, 0};
    double r = 0.5;

    //render
    dopoo_render_sphere(camera, c, r);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/sphere.jpg";
    stbi_write_bmp(path, width, height, 4, pixel);
}

#endif