#ifndef __DOPOOTESTRENDER__
#define __DOPOOTESTRENDER__

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
    dopoo_vec3D rgb = {1, 1, 1};

    //render
    dopoo_render_sphere(camera, c, r, rgb);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/sphere.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

static inline void 
dopoo_testRenderCylinder()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(HRESOLUTION, VRESOLUTION, q, t, ORTHOGRAPHICCAMERA);

    // create cylinder
    double h = 1;
    double r = 0.5;
    dopoo_mapD map;
    dopoo_mapD_init(&map);
    map.r = dopoo_quatD_create(1,1,1,2);
    map.t = (dopoo_vec3D){0, 0, 0};
    dopoo_vec3D rgb = {1, 0, 1};
    dopoo_vec3D lineRgb = {0, 1, 0};

    //render
    dopoo_render_cylinder(camera, h, r, &map, rgb, lineRgb);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/cylinder.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

static inline void 
dopoo_testRenderCone()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(HRESOLUTION, VRESOLUTION, q, t, ORTHOGRAPHICCAMERA);

    // create cone
    double h = 1;
    double r0 = 0.1;
    double r1 = 0.5;
    dopoo_mapD map;
    dopoo_mapD_init(&map);
    map.r = dopoo_quatD_create(1, 0, 1, 0.25);
    //map.t = (dopoo_vec3D){0, 0, 0};
    dopoo_vec3D rgb = {1, 0, 1};
    dopoo_vec3D lineRgb = {0, 1, 0};

    //render
    dopoo_render_cone(camera, h, r0, r1, &map, rgb, lineRgb);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/cone.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

#endif
