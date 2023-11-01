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

    dopoo_vec3D rgb0  = {0.867, 0.565, 0.455};
    dopoo_vec3D rgb1  = {0.682, 0.494, 0.306};
    dopoo_vec3D rgb2  = {0.651, 0.090, 0.106};
    dopoo_vec3D rgb3  = {0.906, 0.780, 0.012};
    dopoo_vec3D rgb4  = {0.039, 0.337, 0.529};
    dopoo_vec3D rgb5  = {0.102, 0.427, 0.639};
    dopoo_vec3D rgb6  = {0.843, 0.839, 0.769};
    dopoo_vec3D rgb7  = {0.584, 0.302, 0.247};
    dopoo_vec3D rgb8  = {1.000, 0.824, 0.05};
    dopoo_vec3D rgb9  = {0.886, 0.812, 0.682};
    dopoo_vec3D rgb10 = {0.784, 0.612, 0.310};
    dopoo_vec3D rgb11 = {0.502, 0.569, 0.290};
    dopoo_vec3D rgb12 = {0.970, 0.970, 0.839};
    dopoo_vec3D rgb13 = {0.298, 0.263, 0.518};
    dopoo_vec3D rgb14 = {0.871, 0.694, 0.235};
    dopoo_vec3D rgb15 = {0.682, 0.682, 0.690};
    dopoo_vec3D rgb16 = {0.647, 0.478, 0.106};
    dopoo_vec3D rgb17 = {0.996, 0.970, 0.847};
    dopoo_vec3D rgb18 = {1.000, 0.584, 0.251};
    dopoo_vec3D rgb19 = {0.584, 0.510, 0.243};
    dopoo_vec3D rgb20 = {0.910, 0.698, 0.322};
    dopoo_vec3D rgb21 = {0.922, 0.545, 0.012};
    dopoo_vec3D rgb22 = {0.000, 1.000, 0.000};
    dopoo_vec3D rgb23 = {1.000, 1.000, 0.000};


    double waistSize = 0.1;
    int32_t nodeCount = 10;
    int32_t jointCount = 10;

    // torso
    double h = 0.4;
    double w0 = waistSize * 2;
    double w1 = 0.5;
    double d0 = 0.15;
    double d1 = 0.15;
    dopoo_pyra* torso = dopoo_pyra_create(h, w0, w1, d0, d1, rgb1);

    h = 0.4;
    double r0 = waistSize;
    double r1 = 0.2;
    //dopoo_cone* torso = dopoo_cone_create(h, r0, r1, rgb0);

    double r = 0.2;
    //dopoo_sphere* torso = dopoo_sphere_create(r, rgb0);

    //abdomen
    r = 0.2;
    dopoo_sphere* abdomen = dopoo_sphere_create(r, rgb2);

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
    dopoo_pyra* waist = dopoo_pyra_create(h, w0, w1, d0, d1, rgb20);

    //left shoulder
    h = 0.35;
    r = 0.05;
    dopoo_cylinder* lshoulder = dopoo_cylinder_create(h, r, rgb4);

    //right shoulder
    h = 0.35;
    r = 0.05;
    dopoo_cylinder* rshoulder = dopoo_cylinder_create(h, r, rgb4);

    //left upper arm
    h = 0.3;
    r0 = 0.05;
    r1 = 0.07;
    //dopoo_cone* lupperarm = dopoo_cone_create(h, r0, r1, rgb4);

    h = 0.3;
    r = 0.03;
    dopoo_cylinder* lupperarm = dopoo_cylinder_create(h, r, rgb5);

    //right upper arm
    h = 0.3;
    r0 = 0.05;
    r1 = 0.07;
    //dopoo_cone* rupperarm = dopoo_cone_create(h, r0, r1, rgb4);

    h = 0.3;
    r = 0.03;
    dopoo_cylinder* rupperarm = dopoo_cylinder_create(h, r, rgb5);

    //left upper arm1
    h = 0.2;
    r = 0.08;
    dopoo_cylinder* lupperarm1 = dopoo_cylinder_create(h, r, rgb6);

    //right upper arm1
    h = 0.2;
    r = 0.08;
    dopoo_cylinder* rupperarm1 = dopoo_cylinder_create(h, r, rgb6);

    //left lower arm
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* llowerarm = dopoo_cone_create(h, r0, r1, rgb7);

    //right lower arm
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* rlowerarm = dopoo_cone_create(h, r0, r1, rgb7);

    //left upper leg
    h = 0.4;
    r0 = 0.05;
    r1 = 0.08;
    dopoo_cone* lupperleg = dopoo_cone_create(h, r0, r1, rgb8);

    //right upper leg
    h = 0.4;
    r0 = 0.05;
    r1 = 0.08;
    dopoo_cone* rupperleg = dopoo_cone_create(h, r0, r1, rgb8);

    //left lower leg
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* llowerleg = dopoo_cone_create(h, r0, r1, rgb9);

    //right lower leg
    h = 0.3;
    r0 = 0.03;
    r1 = 0.05;
    dopoo_cone* rlowerleg = dopoo_cone_create(h, r0, r1, rgb9);

    // left foot
    h = 0.1;
    w0 = 0.1;
    w1 = 0.1;
    d0 = 0.3;
    d1 = 0.1;
    dopoo_pyra* lfoot = dopoo_pyra_create(h, w0, w1, d0, d1, rgb10);

    // right foot
    h = 0.1;
    w0 = 0.1;
    w1 = 0.1;
    d0 = 0.3;
    d1 = 0.1;
    dopoo_pyra* rfoot = dopoo_pyra_create(h, w0, w1, d0, d1, rgb10);


    //neck
    h = 0.15;
    r = 0.05;
    dopoo_cylinder* neck = dopoo_cylinder_create(h, r, rgb11);

    //lower head
    h = 0.1;
    r0 = 0.05;
    r1 = 0.1;
    dopoo_cone* lhead = dopoo_cone_create(h, r0, r1, rgb12);

    //middle head
    h = 0.15;
    r = 0.1;
    dopoo_cylinder* mhead = dopoo_cylinder_create(h, r, rgb13);

    //left eye
    h = 0.05;
    r = 0.03;
    dopoo_cylinder* leye = dopoo_cylinder_create(h, r, rgb15);

    //left eye
    h = 0.05;
    r = 0.03;
    dopoo_cylinder* reye = dopoo_cylinder_create(h, r, rgb15);

    //left eye ball
    r = 0.02;
    dopoo_sphere* leyeball = dopoo_sphere_create(r, rgb22);

    //right eye ball
    r = 0.02;
    dopoo_sphere* reyeball = dopoo_sphere_create(r, rgb23);

    //left wrist
    h = 0.03;
    r = 0.1;
    dopoo_cylinder* lwrist = dopoo_cylinder_create(h, r, rgb15);

    //right wrist
    h = 0.03;
    r = 0.1;
    dopoo_cylinder* rwrist = dopoo_cylinder_create(h, r, rgb15);

    //left finger 00
    h = 0.05;
    r = 0.015;
    dopoo_cylinder* lfinger00 = dopoo_cylinder_create(h, r, rgb15);

    //right finger 00
    h = 0.05;
    r = 0.015;
    dopoo_cylinder* rfinger00 = dopoo_cylinder_create(h, r, rgb15);

    //left finger 01
    h = 0.05;
    r0 = 0.01;
    r1 = 0.015;
    dopoo_cone* lfinger01 = dopoo_cone_create(h, r0, r1, rgb15);

    //right finger 01
    h = 0.05;
    r0 = 0.01;
    r1 = 0.015;
    dopoo_cone* rfinger01 = dopoo_cone_create(h, r0, r1, rgb15);

    //left finger 00
    h = 0.05;
    r = 0.015;
    dopoo_cylinder* lfinger10 = dopoo_cylinder_create(h, r, rgb15);

    //right finger 00
    h = 0.05;
    r = 0.015;
    dopoo_cylinder* rfinger10 = dopoo_cylinder_create(h, r, rgb15);

    //left finger 01
    h = 0.05;
    r0 = 0.01;
    r1 = 0.015;
    dopoo_cone* lfinger11 = dopoo_cone_create(h, r0, r1, rgb15);

    //right finger 01
    h = 0.05;
    r0 = 0.01;
    r1 = 0.015;
    dopoo_cone* rfinger11 = dopoo_cone_create(h, r0, r1, rgb15);


    
    //joints
    //lShoulderJoint
    r = 0.00;
    dopoo_sphere* lshoulderjoint = dopoo_sphere_create(r, rgb5);

    //rShoulderJoint
    r = 0.0;
    dopoo_sphere* rshoulderjoint = dopoo_sphere_create(r, rgb5);

    //lupperarmjoint
    r = 0.00;
    dopoo_sphere* lupperarmjoint = dopoo_sphere_create(r, rgb5);

    //rupperarmjoint
    r = 0.00;
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
    dopoo_node2* node8 = dopoo_node2_create(lupperleg, NULL, NULL);
    dopoo_node2* node9 = dopoo_node2_create(rupperleg, NULL, NULL);
    dopoo_node2* node10 = dopoo_node2_create(llowerleg, NULL, NULL);
    dopoo_node2* node11 = dopoo_node2_create(rlowerleg, NULL, NULL);
    dopoo_node2* node12 = dopoo_node2_create(lupperarm1, NULL, NULL);
    dopoo_node2* node13 = dopoo_node2_create(rupperarm1, NULL, NULL);
    dopoo_node2* node14 = dopoo_node2_create(neck, NULL, NULL);
    dopoo_node2* node15 = dopoo_node2_create(lhead, NULL, NULL);
    dopoo_node2* node16 = dopoo_node2_create(mhead, NULL, NULL);
    dopoo_node2* node17 = dopoo_node2_create(lfoot, NULL, NULL);
    dopoo_node2* node18 = dopoo_node2_create(rfoot, NULL, NULL);
    dopoo_node2* node19 = dopoo_node2_create(leye, NULL, NULL);
    dopoo_node2* node20 = dopoo_node2_create(reye, NULL, NULL);
    dopoo_node2* node21 = dopoo_node2_create(leyeball, NULL, NULL);
    dopoo_node2* node22 = dopoo_node2_create(reyeball, NULL, NULL);
    dopoo_node2* node23 = dopoo_node2_create(abdomen, NULL, NULL);
    dopoo_node2* node24 = dopoo_node2_create(lwrist, NULL, NULL);
    dopoo_node2* node25 = dopoo_node2_create(rwrist, NULL, NULL);
    dopoo_node2* node26 = dopoo_node2_create(lfinger00, NULL, NULL);
    dopoo_node2* node27 = dopoo_node2_create(rfinger00, NULL, NULL);
    dopoo_node2* node28 = dopoo_node2_create(lfinger01, NULL, NULL);
    dopoo_node2* node29 = dopoo_node2_create(rfinger01, NULL, NULL);
    dopoo_node2* node30 = dopoo_node2_create(lfinger10, NULL, NULL);
    dopoo_node2* node31 = dopoo_node2_create(rfinger10, NULL, NULL);
    dopoo_node2* node32 = dopoo_node2_create(lfinger11, NULL, NULL);
    dopoo_node2* node33 = dopoo_node2_create(rfinger11, NULL, NULL);
    

    // create joints
    dopoo_joint2* joint0 = dopoo_joint2_create(lshoulderjoint, lshoulder, NULL);
    dopoo_joint2* joint1 = dopoo_joint2_create(rshoulderjoint, rshoulder, NULL);
    dopoo_joint2* joint2 = dopoo_joint2_create(lupperarmjoint, lupperarm, NULL);
    dopoo_joint2* joint3 = dopoo_joint2_create(rupperarmjoint, rupperarm, NULL);
    

    // create link
    dopoo_link* link = dopoo_link_create(nodeCount, jointCount, rgb16);

    //add node
    dopoo_link_addNode(link, node0);
    dopoo_link_addNode(link, node1);
    dopoo_link_addNode(link, node2);
    dopoo_link_addNode(link, node3);
    dopoo_link_addNode(link, node4);
    dopoo_link_addNode(link, node5);
    dopoo_link_addNode(link, node6);
    dopoo_link_addNode(link, node7);
    dopoo_link_addNode(link, node8);
    dopoo_link_addNode(link, node9);
    dopoo_link_addNode(link, node10);
    dopoo_link_addNode(link, node11);
    dopoo_link_addNode(link, node12);
    dopoo_link_addNode(link, node13);
    dopoo_link_addNode(link, node14);
    dopoo_link_addNode(link, node15);
    dopoo_link_addNode(link, node16);
    dopoo_link_addNode(link, node17);
    dopoo_link_addNode(link, node18);
    dopoo_link_addNode(link, node19);
    dopoo_link_addNode(link, node20);
    dopoo_link_addNode(link, node21);
    dopoo_link_addNode(link, node22);
    dopoo_link_addNode(link, node23);
    dopoo_link_addNode(link, node24);
    dopoo_link_addNode(link, node25);
    dopoo_link_addNode(link, node26);
    dopoo_link_addNode(link, node27);
    dopoo_link_addNode(link, node28);
    dopoo_link_addNode(link, node29);
    dopoo_link_addNode(link, node30);
    dopoo_link_addNode(link, node31);
    dopoo_link_addNode(link, node32);
    dopoo_link_addNode(link, node33);

    //add joint
    dopoo_link_addJoint(link, joint0);
    dopoo_link_addJoint(link, joint1);
    dopoo_link_addJoint(link, joint2);
    dopoo_link_addJoint(link, joint3);




    //create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);

    // transform
    link->map.r = dopoo_quatD_create(0, 1, 0, 4.5);
    torso->map.t = (dopoo_vec3D){0, 0.3, 0};
    abdomen->map.t = (dopoo_vec3D){0, 0.3, 0};
    waist->map.r = dopoo_quatD_create(1, 0, 0, 0);
    neck->map.t = (dopoo_vec3D){0, 0.575, 0};
    lhead->map.t = (dopoo_vec3D){0, 0.70, 0};
    mhead->map.t = (dopoo_vec3D){0, 0.825, 0};

    leye->map.r = dopoo_quatD_create(1, 0, 0, 1);
    leye->map.t = (dopoo_vec3D){ 0.04, 0.85, 0.08};

    reye->map.r = dopoo_quatD_create(1, 0, 0, 1);
    reye->map.t = (dopoo_vec3D){-0.04, 0.85, 0.08};

    leyeball->map.t = (dopoo_vec3D){ 0.04, 0.85, 0.095};
    reyeball->map.t = (dopoo_vec3D){ -0.04, 0.85, 0.095};

    lshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    lshoulder->map.t = (dopoo_vec3D){0.23, 0.55, 0};

    rshoulder->map.r = dopoo_quatD_create(0, 0, 1, 1);
    rshoulder->map.t = (dopoo_vec3D){-0.23, 0.55, 0};

    lupperarm->map.t = (dopoo_vec3D){ 0.35, 0.4, 0};
    rupperarm->map.t = (dopoo_vec3D){-0.35, 0.4, 0};

    lupperarm1->map.t = (dopoo_vec3D){ 0.35, 0.38, 0};
    rupperarm1->map.t = (dopoo_vec3D){-0.35, 0.38, 0};

    llowerarm->map.t = (dopoo_vec3D){ 0.35, 0.1, 0};
    rlowerarm->map.t = (dopoo_vec3D){-0.35, 0.1, 0};
    
    lwrist->map.t = (dopoo_vec3D){ 0.35, -0.05, 0};
    rwrist->map.t = (dopoo_vec3D){-0.35, -0.05, 0};

    lfinger00->map.t = (dopoo_vec3D){ 0.42, -0.09, 0};
    rfinger00->map.t = (dopoo_vec3D){-0.42, -0.09, 0};

    lfinger01->map.r = dopoo_quatD_create(0, 0, -1, 4);
    rfinger01->map.r = dopoo_quatD_create(0, 0, 1, 4);

    lfinger01->map.t = (dopoo_vec3D){ 0.41, -0.13, 0};
    rfinger01->map.t = (dopoo_vec3D){-0.41, -0.13, 0};

    lfinger10->map.t = (dopoo_vec3D){ 0.28, -0.09, 0};
    rfinger10->map.t = (dopoo_vec3D){-0.28, -0.09, 0};

    lfinger11->map.r = dopoo_quatD_create(0, 0, 1, 4);
    rfinger11->map.r = dopoo_quatD_create(0, 0, -1, 4);

    lfinger11->map.t = (dopoo_vec3D){ 0.29, -0.13, 0};
    rfinger11->map.t = (dopoo_vec3D){-0.29, -0.13, 0};

    lupperleg->map.t = (dopoo_vec3D){ 0.15, -0.3, 0};
    rupperleg->map.t = (dopoo_vec3D){-0.15, -0.3, 0};
    
    llowerleg->map.t = (dopoo_vec3D){ 0.15, -0.65, 0};
    rlowerleg->map.t = (dopoo_vec3D){-0.15, -0.65, 0};
    lfoot->map.t = (dopoo_vec3D){ 0.15, -0.85, 0};
    rfoot->map.t = (dopoo_vec3D){-0.15, -0.85, 0};

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