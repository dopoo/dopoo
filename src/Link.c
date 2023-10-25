#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include "../inc/Link.h"
#include "../inc/Node.h"
#include "../inc/Joint.h"

dopoo_link*
dopoo_link_create(int32_t nodeSize, int32_t jointSize)
{
    dopoo_link* link = (dopoo_link*)malloc(sizeof(dopoo_link));
    link->nodes = dopoo_list_create(nodeSize);
    link->joints = dopoo_list_create(jointSize);
    return link; 
}

void
dopoo_link_clear(dopoo_link* link)
{
    dopoo_list_clear(link->nodes);
    dopoo_list_clear(link->joints);
    free(link);
}

void
dopoo_link_addNode(dopoo_link* link, void* node)
{
    dopoo_list_add(link->nodes, node);
}

void
dopoo_link_addJoint(dopoo_link* link, void* joint)
{
    dopoo_list_add(link->joints, joint);
}

void*
dopoo_link_getNode(const dopoo_link* link, int32_t i)
{
    return dopoo_list_get(link->nodes, i);
}

void*
dopoo_link_getJoint(const dopoo_link* link, int32_t i)
{
    return dopoo_list_get(link->joints, i);
}

bool
dopoo_link_intersect(const dopoo_link* link, dopoo_rayD* ray, int32_t* num, dopoo_vec3D* n, double* t)
{
    *t = DBL_MAX;
    double t0 = DBL_MAX;
    dopoo_vec3D n0 = {0, 0, 0};
    bool intersect = false;
    for(int32_t i = 0; i < link->nodes->size; i++)
    {
        void* prim = ((dopoo_node2*)(link->nodes->data[i]))->prim;
        if(dopoo_prim_intersect(prim, ray, &n0, &t0))
        {
            intersect = true;
            if(*t > t0)
            {
                *t = t0;
                *n = n0;
                *num = i;
            }
        }
    }

    for(int32_t i = 0; i < link->joints->size; i++)
    {
        dopoo_sphere s = ((dopoo_joint2*)(link->joints->data[i]))->s;
        if(dopoo_prim_intersect((void*)(&s), ray, &n0, &t0))
        {
            intersect = true;
            if(*t > t0)
            {
                *t = t0;
                *n = n0;
                *num = link->nodes->size + i;
            }
        }
    }
    
    return intersect;
}

dopoo_vec3D
dopoo_link_getRgb(const dopoo_link* link, int32_t num)
{
    if(num < link->nodes->size)
        return dopoo_prim_getRgb(((dopoo_node2*)(link->nodes->data[num]))->prim);
    else if(num < link->nodes->size + link->joints->size)
        return dopoo_prim_getRgb((void*)(&(((dopoo_joint2*)(link->joints->data[num]))->s)));
    else
        return (dopoo_vec3D){0, 0, 0};
}





