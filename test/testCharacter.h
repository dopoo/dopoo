#ifndef __DOPOOTESTCHARACTER__
#define __DOPOOTESTCHARACTER__

#include "../inc/Render.h"
#include "../inc/Primitive.h"
#include "../inc/Node.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdPartyLibrary/stb_image_write.h"

#define HRESOLUTION 1920
#define VRESOLUTION 1080


static inline void 
dopoo_testCreateCharacter()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(HRESOLUTION, VRESOLUTION, q, t, PERSPECTIVECAMERA);

    // torso
    h = 1;
    double w0 = 0.318;
    double w1 = 0.4;
    double d0 = 0.1;
    double d1 = 0.5;
    rgb = (dopoo_vec3D){0, 0, 1};
    dopoo_pyra* torso = dopoo_pyra_create(h, w0, w1, d0, d1, rgb);




    // create nodes
    dopoo_node2* node0 = dopoo_node2_create(torso, NULL, NULL);

    // create link
    dopoo_vec3D lineRgb = {0, 1, 0};
    dopoo_link* link = dopoo_link_create(1, 0, lineRgb);
    dopoo_link_addNode(link, node0);

    //create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);

    // transform
    //pyra->map.r = dopoo_quatD_create(1, 0, 1, 0.25);
    //cone->map.r = dopoo_quatD_create(-1, 0, -1, 0.25);
    //pyra->map.t = (dopoo_vec3D){-0.3, 0, 0};

    //render
    dopoo_render_scene(camera, scene);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/scene.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

#endif