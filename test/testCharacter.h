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

    dopoo_vec3D rgb0 = {1, 0, 0};
    dopoo_vec3D rgb1 = {0, 1, 0};
    dopoo_vec3D rgb2 = {0, 0, 1};
    dopoo_vec3D rgb3 = {1, 1, 0};
    dopoo_vec3D rgb4 = {1, 0, 1};
    dopoo_vec3D rgb5 = {0, 1, 1};
    dopoo_vec3D rgb6 = {0.5, 0, 0};
    dopoo_vec3D rgb7 = {0, 0.5, 0};
    dopoo_vec3D rgb8 = {0, 0, 0.5};
    dopoo_vec3D rgb9 = {0.5, 0, 0.5};
    dopoo_vec3D rgb10 = {0.5, 0.5, 0};
    dopoo_vec3D rgb11 = {0, 0.5, 0.5};

    double waistSize = 0.1;
    int32_t nodeCount = 10;
    int32_t jointCount = 10;

    // torso
    double h = 0.4;
    double w0 = waistSize * 2;
    double w1 = 0.5;
    double d0 = 0.15;
    double d1 = 0.15;
    dopoo_pyra* torso = dopoo_pyra_create(h, w0, w1, d0, d1, rgb0);

    h = 0.4;
    double r0 = waistSize;
    double r1 = 0.2;
    //dopoo_cone* torso = dopoo_cone_create(h, r0, r1, rgb0);

    double r = 0.2;
    //dopoo_sphere* torso = dopoo_sphere_create(r, rgb0);



    //waist
    double w = waistSize * 2;
    h = 0.2;
    double d = 0.15;
    //dopoo_cuboid* waist = dopoo_cuboid_create(w, h, d, rgb2);

    h = 0.2;
    r0 = waistSize;
    r1 = 0.3;
    //dopoo_cone* waist = dopoo_cone_create(h, r0, r1, rgb2);

    h = 0.2;
    w0 = waistSize * 2;
    w1 = 0.3;
    d0 = 0.15;
    d1 = 0.15;
    dopoo_pyra* waist = dopoo_pyra_create(h, w0, w1, d0, d1, rgb2);

    //left shoulder
    h = 0.35;
    r = 0.05;
    dopoo_cylinder* lshoulder = dopoo_cylinder_create(h, r, rgb3);

    //right shoulder
    h = 0.35;
    r = 0.05;
    dopoo_cylinder* rshoulder = dopoo_cylinder_create(h, r, rgb3);

    //left upper arm
    h = 0.3;
    r0 = 0.05;
    r1 = 0.07;
    //dopoo_cone* lupperarm = dopoo_cone_create(h, r0, r1, rgb4);

    h = 0.3;
    r = 0.05;
    dopoo_cylinder* lupperarm = dopoo_cylinder_create(h, r, rgb4);

    //right upper arm
    h = 0.3;
    r0 = 0.05;
    r1 = 0.07;
    //dopoo_cone* rupperarm = dopoo_cone_create(h, r0, r1, rgb4);

    h = 0.3;
    r = 0.05;
    dopoo_cylinder* rupperarm = dopoo_cylinder_create(h, r, rgb4);

    //left lower arm
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* llowerarm = dopoo_cone_create(h, r0, r1, rgb6);

    //right lower arm
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* rlowerarm = dopoo_cone_create(h, r0, r1, rgb6);

    //lShoulderJoint
    r = 0.00;
    dopoo_sphere* lshoulderjoint = dopoo_sphere_create(r, rgb5);

    //rShoulderJoint
    r = 0.0;
    dopoo_sphere* rshoulderjoint = dopoo_sphere_create(r, rgb5);

    //lupperarmjoint
    r = 0.05;
    dopoo_sphere* lupperarmjoint = dopoo_sphere_create(r, rgb5);

    //rupperarmjoint
    r = 0.05;
    dopoo_sphere* rupperarmjoint = dopoo_sphere_create(r, rgb5);

    // create nodes
    dopoo_node2* node0 = dopoo_node2_create(torso, NULL, NULL);
    dopoo_node2* node1 = dopoo_node2_create(waist, NULL, NULL);
    dopoo_node2* node2 = dopoo_node2_create(lshoulder, NULL, NULL);
    dopoo_node2* node3 = dopoo_node2_create(rshoulder, NULL, NULL);
    dopoo_node2* node4 = dopoo_node2_create(lupperarm, NULL, NULL);
    dopoo_node2* node5 = dopoo_node2_create(rupperarm, NULL, NULL);
    dopoo_node2* node6 = dopoo_node2_create(llowerarm, NULL, NULL);
    dopoo_node2* node7 = dopoo_node2_create(rlowerarm, NULL, NULL);

    // create joints
    dopoo_joint2* joint0 = dopoo_joint2_create(lshoulderjoint, lshoulder, NULL);
    dopoo_joint2* joint1 = dopoo_joint2_create(rshoulderjoint, rshoulder, NULL);
    dopoo_joint2* joint2 = dopoo_joint2_create(lupperarmjoint, lupperarm, NULL);
    dopoo_joint2* joint3 = dopoo_joint2_create(rupperarmjoint, rupperarm, NULL);
    

    // create link
    dopoo_link* link = dopoo_link_create(nodeCount, jointCount, rgb1);

    //add node
    dopoo_link_addNode(link, node0);
    dopoo_link_addNode(link, node1);
    dopoo_link_addNode(link, node2);
    dopoo_link_addNode(link, node3);
    dopoo_link_addNode(link, node4);
    dopoo_link_addNode(link, node5);
    dopoo_link_addNode(link, node6);
    dopoo_link_addNode(link, node7);


    //add joint
    dopoo_link_addJoint(link, joint0);
    dopoo_link_addJoint(link, joint1);
    dopoo_link_addJoint(link, joint2);
    dopoo_link_addJoint(link, joint3);




    //create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);

    // transform
    link->map.r = dopoo_quatD_create(0, 0, 0, 0.15);
    torso->map.t = (dopoo_vec3D){0, 0.3, 0};
    waist->map.r = dopoo_quatD_create(1, 0, 0, 0);

    lshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    lshoulder->map.t = (dopoo_vec3D){0.23, 0.55, 0};

    rshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    rshoulder->map.t = (dopoo_vec3D){-0.23, 0.55, 0};

    lupperarm->map.t = (dopoo_vec3D){ 0.35, 0.4, 0};
    rupperarm->map.t = (dopoo_vec3D){-0.35, 0.4, 0};

    llowerarm->map.t = (dopoo_vec3D){ 0.35, 0.1, 0};
    rlowerarm->map.t = (dopoo_vec3D){-0.35, 0.1, 0};

    lshoulderjoint->map.t = (dopoo_vec3D){ 0.35, 0.55, 0};
    rshoulderjoint->map.t = (dopoo_vec3D){-0.35, 0.55, 0};
    lupperarmjoint->map.t = (dopoo_vec3D){ 0.35, 0.25, 0};
    rupperarmjoint->map.t = (dopoo_vec3D){-0.35, 0.25, 0};

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