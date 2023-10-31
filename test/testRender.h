#ifndef __DOPOOTESTRENDER__
#define __DOPOOTESTRENDER__

#include "../inc/Render.h"
#include "../inc/Primitive.h"
#include "../inc/Node.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdPartyLibrary/stb_image_write.h"

#define HRESOLUTION 960
#define VRESOLUTION 720


static inline void 
dopoo_testRenderLink()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(HRESOLUTION, VRESOLUTION, q, t, ORTHOGRAPHICCAMERA);

    // create sphere
    double r = 0.3;
    dopoo_vec3D rgb = {1, 0, 1};
    dopoo_sphere* sphere = dopoo_sphere_create(r, rgb);

    //cuboid
    double w = 0.3;
    double h = 0.3;
    double d = 0.15;
    rgb = (dopoo_vec3D){0, 0, 1};
    dopoo_cuboid* cuboid = dopoo_cuboid_create(w, h, d, rgb);
    
    // create cylinder
    h = 1;
    r = 0.5;
    rgb = (dopoo_vec3D){1, 0, 1};
    dopoo_cylinder* cylinder = dopoo_cylinder_create(h, r, rgb);

    // create pyra
    h = 1;
    double w0 = 0.1;
    double w1 = 0.5;
    double d0 = 0.1;
    double d1 = 0.5;
    rgb = (dopoo_vec3D){0, 0, 1};
    dopoo_pyra* pyra = dopoo_pyra_create(h, w0, w1, d0, d1, rgb);

    // create cone
    h = 1;
    double r0 = 0.1;
    double r1 = 0.5;
    rgb = (dopoo_vec3D){1, 0, 1};
    dopoo_cone* cone = dopoo_cone_create(h, r0, r1, rgb);

    // create nodes
    dopoo_node2* node0 = dopoo_node2_create(pyra, NULL, NULL);
    dopoo_node2* node1 = dopoo_node2_create(cone, NULL, NULL);
    dopoo_node2* node2 = dopoo_node2_create(sphere, NULL, NULL);
    dopoo_node2* node3 = dopoo_node2_create(cylinder, NULL, NULL);
    dopoo_node2* node4 = dopoo_node2_create(cuboid, NULL, NULL);

    // create link
    dopoo_vec3D lineRgb = {0, 1, 0};
    dopoo_link* link = dopoo_link_create(1, 0, lineRgb);
    //dopoo_link_addNode(link, node0);
    //dopoo_link_addNode(link, node1);
    dopoo_link_addNode(link, node2);
    //dopoo_link_addNode(link, node3);
    //dopoo_link_addNode(link, node4);

    //create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);

    // transform
    pyra->map.r = dopoo_quatD_create(1, 0, 1, 0.25);
    pyra->map.t = (dopoo_vec3D){-0.3, 0, 0};
    cone->map.r = dopoo_quatD_create(-1, 0, 0, 0.3);
    cone->map.t = (dopoo_vec3D){-0.3, 0, 3};
    cylinder->map.t = (dopoo_vec3D){-0.3, 0, 1};

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
