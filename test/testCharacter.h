#ifndef __DOPOOTESTCHARACTER__
#define __DOPOOTESTCHARACTER__

#include "../inc/Render.h"
#include "../inc/Primitive.h"
#include "../inc/Node.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdPartyLibrary/stb_image_write.h"

#define CHRESOLUTION 1080
#define CVRESOLUTION 720

#define PARTCOUNT 34

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
    dopoo_vec3D rgb24 = {0.152, 0.156, 0.133};


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

    //abdomen
    double r = 0.2;
    dopoo_sphere* abdomen = dopoo_sphere_create(r, rgb2);

    //waist
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
    r = 0.03;
    dopoo_cylinder* lupperarm = dopoo_cylinder_create(h, r, rgb5);

    //right upper arm
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
    double r0 = 0.03;
    double r1 = 0.05;
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

    // transform
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

    void* parts[PARTCOUNT] = {torso, waist, lupperleg, rupperleg, llowerleg, rlowerleg,
                              lfoot, rfoot, lshoulder, rshoulder, lupperarm, rupperarm, 
                              lupperarm1, rupperarm1, llowerarm, rlowerarm, lwrist, rwrist,
                              lfinger00, rfinger00, lfinger01, rfinger01, lfinger10, rfinger10,
                              lfinger11, rfinger11, abdomen, neck, lhead, mhead,  
                              leye, reye, leyeball, reyeball};

    // create nodes
    dopoo_node2* nodes[PARTCOUNT];
    for(int32_t i = 0; i < PARTCOUNT; i++)
    {
        nodes[i] = dopoo_node2_create(parts[i], NULL, NULL);
    }

    // create link
    dopoo_link* link = dopoo_link_create(nodeCount, jointCount, rgb16);
    link->map.r = dopoo_quatD_create(0, 1, 0, 4.5);

    // add node
    for(int32_t i = 0; i < PARTCOUNT; i++)
    {
        dopoo_link_addNode(link, nodes[i]);
    }
    
    // create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);
    dopoo_scene_setBg(scene, rgb24);

    // render
    dopoo_render_scene(camera, scene);

    // save render result to image
    dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
    int32_t width = dopoo_camera_getWidth(camera);
    int32_t height = dopoo_camera_getHeight(camera);
    const char* path = "data/renderResult/character.jpg";
    stbi_write_jpg(path, width, height, 4, pixel, 90);
}

static inline void 
dopoo_testCreateCharacter1()
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
    dopoo_vec3D rgb24 = {0.152, 0.156, 0.133};


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

    //abdomen
    double r = 0.2;
    dopoo_sphere* abdomen = dopoo_sphere_create(r, rgb2);

    //waist
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
    r = 0.03;
    dopoo_cylinder* lupperarm = dopoo_cylinder_create(h, r, rgb5);

    //right upper arm
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
    double r0 = 0.03;
    double r1 = 0.05;
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

    // transform
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

    void* parts[PARTCOUNT] = {torso, waist, lupperleg, rupperleg, llowerleg, rlowerleg,
                              lfoot, rfoot, lshoulder, rshoulder, lupperarm, rupperarm, 
                              lupperarm1, rupperarm1, llowerarm, rlowerarm, lwrist, rwrist,
                              lfinger00, lfinger01, lfinger10, lfinger11, rfinger00,  rfinger01, 
                               rfinger10, rfinger11, abdomen, neck, lhead, mhead,  
                              leye, reye, leyeball, reyeball};

    // create nodes
    dopoo_node2* nodes[PARTCOUNT];
    for(int32_t i = 0; i < PARTCOUNT; i++)
    {
        nodes[i] = dopoo_node2_create(parts[i], NULL, NULL);
    }

    // create link
    dopoo_link* link = dopoo_link_create(nodeCount, jointCount, rgb16);
    link->map.r = dopoo_quatD_create(0, 1, 0, 4.5);
    
    // create scene
    dopoo_scene* scene = dopoo_scene_create(1);
    dopoo_scene_addLink(scene, link);
    dopoo_scene_setBg(scene, rgb24);

    // add node
    char path[100];
    for(int32_t i = 0; i < PARTCOUNT; i++)
    {
        dopoo_link_addNode(link, nodes[i]);
        sprintf(path, "data/renderResult/character%d.jpg", i);
    
        // render
        dopoo_render_scene(camera, scene);
    
        // save render result to image
        dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
        int32_t width = dopoo_camera_getWidth(camera);
        int32_t height = dopoo_camera_getHeight(camera);
        stbi_write_jpg(path, width, height, 4, pixel, 90);
    }

    int32_t imageCount = 34;

    for(int32_t i = 0; i <= 360; i += 10)
    {
        double rad = (double)(-i) * M_PI / 180.f;
        link->map.r = dopoo_quatD_create(0, sin(rad / 2), 0, cos(rad / 2));
        sprintf(path, "data/renderResult/character%d.jpg", imageCount + i / 10);
    
        // render
        dopoo_render_scene(camera, scene);
    
        // save render result to image
        dopoo_rgbI* pixel = dopoo_camera_getPixel(camera);
        int32_t width = dopoo_camera_getWidth(camera);
        int32_t height = dopoo_camera_getHeight(camera);
        stbi_write_jpg(path, width, height, 4, pixel, 90);

    }
}

#endif
