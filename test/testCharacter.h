#ifndef __DOPOOTESTCHARACTER__
#define __DOPOOTESTCHARACTER__

#include "../inc/Render.h"
#include "../inc/Primitive.h"
#include "../inc/Node.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdPartyLibrary/stb_image_write.h"

#define CHRESOLUTION 1080
#define CVRESOLUTION 720


static inline void 
dopoo_testCreateCharacter()
{
    // create camera
    dopoo_quatD q = dopoo_quatD_create(0, 0, 0, 1);
    dopoo_vec3D t = {0, 0, 2};
    dopoo_camera* camera = dopoo_camera_create(CHRESOLUTION, CVRESOLUTION, q, t, ORTHOGRAPHICCAMERA);

    // torso
    double h = 0.4;
    double w0 = 0.3;
    double w1 = 0.4;
    double d0 = 0.15;
    double d1 = 0.15;
    dopoo_vec3D rgb = {0, 0, 1};
    dopoo_pyra* torso = dopoo_pyra_create(h, w0, w1, d0, d1, rgb);

    //waist
    double w = 0.3;
    h = 0.2;
    double d = 0.15;
    rgb = (dopoo_vec3D){1, 0, 1};
    dopoo_cuboid* waist = dopoo_cuboid_create(w, h, d, rgb);

    //left shoulder
    h = 0.15;
    double r = 0.05;
    rgb = (dopoo_vec3D){1, 0, 0};
    dopoo_cylinder* lshoulder = dopoo_cylinder_create(h, r, rgb);

    //right shoulder
    h = 0.15;
    r = 0.05;
    rgb = (dopoo_vec3D){1, 0, 0};
    dopoo_cylinder* rshoulder = dopoo_cylinder_create(h, r, rgb);

    //lShoulderJoint
    r = 0.05;
    rgb = (dopoo_vec3D){1, 0, 0};
    dopoo_sphere* lShoulderJoint = dopoo_sphere_create(r, rgb);

    // create nodes
    dopoo_node2* node0 = dopoo_node2_create(torso, NULL, NULL);
    dopoo_node2* node1 = dopoo_node2_create(waist, NULL, NULL);
    dopoo_node2* node2 = dopoo_node2_create(lshoulder, NULL, NULL);
    dopoo_node2* node3 = dopoo_node2_create(rshoulder, NULL, NULL);

    // create joints
    dopoo_joint2* joint0 = dopoo_joint2_create(lShoulderJoint, lshoulder, NULL);
    

    // create link
    dopoo_vec3D lineRgb = {0, 1, 0};
    dopoo_link* link = dopoo_link_create(10, 0, lineRgb);

    //add node
    dopoo_link_addNode(link, node0);
    dopoo_link_addNode(link, node1);
    dopoo_link_addNode(link, node2);
    dopoo_link_addNode(link, node3);


    //add joint
    dopoo_link_addJoint(link, joint0);




    //create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);

    // transform
    link->map.r = dopoo_quatD_create(0, 0, 0, 0.15);
    torso->map.t = (dopoo_vec3D){0, 0.3, 0};
    lshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    lshoulder->map.t = (dopoo_vec3D){-0.13, 0.55, 0};
    rshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    rshoulder->map.t = (dopoo_vec3D){0.13, 0.55, 0};
    lShoulderJoint->map.t = (dopoo_vec3D){0.25, 0.55, 0};

    //render
    dopoo_render_scene(camera, scene);

    //save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/character.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

#endif