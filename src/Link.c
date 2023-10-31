#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include "../inc/Link.h"
#include "../inc/Node.h"
#include "../inc/Joint.h"

dopoo_link*
dopoo_link_create(int32_t nodeSize, int32_t jointSize, dopoo_vec3D lineRgb)
{
    dopoo_link* link = (dopoo_link*)malloc(sizeof(dopoo_link));
    link->nodes = dopoo_list_create(nodeSize);
    link->joints = dopoo_list_create(jointSize);
    link->links = dopoo_list_create(5);
    link->lineRgb = lineRgb;
    dopoo_mapD_init(&(link->map));
    return link; 
}

void
dopoo_link_clear(dopoo_link* link)
{
    dopoo_list_clear(link->nodes);
    dopoo_list_clear(link->joints);
    dopoo_list_clear(link->links);
    free(link);
}

void
dopoo_link_addNode(dopoo_link* link, dopoo_node2* node)
{
    dopoo_list_add(link->nodes, node);
}

void
dopoo_link_addJoint(dopoo_link* link, dopoo_joint2* joint)
{
    dopoo_list_add(link->joints, joint);
}

void
dopoo_link_addLink(dopoo_link* link, dopoo_link* branch)
{
    dopoo_list_add(link->links, branch);
}

dopoo_node2*
dopoo_link_getNode(const dopoo_link* link, int32_t i)
{
    return (dopoo_node2*)(dopoo_list_get(link->nodes, i));
}

dopoo_joint2*
dopoo_link_getJoint(const dopoo_link* link, int32_t i)
{
    return (dopoo_joint2*)(dopoo_list_get(link->joints, i));
}

dopoo_link*
dopoo_link_getLink(const dopoo_link* link, int32_t i)
{
    return (dopoo_link*)(dopoo_list_get(link->links, i));
}

int32_t
dopoo_link_nodeCount(const dopoo_link* link)
{
    int32_t nodeCount = link->nodes->size + link->joints->size;
    for(int32_t i = 0; i < link->links->size; i++)
    {
        dopoo_link* l = (dopoo_link*)(link->links->data[i]);
        nodeCount += dopoo_link_nodeCount(l);
    }
    return nodeCount;
}

bool
dopoo_link_intersect(const dopoo_link* link, dopoo_rayD* ray, int32_t* num, dopoo_vec3D* n, double* t)
{
    *t = DBL_MAX;
    double t0 = DBL_MAX;
    dopoo_vec3D n0 = {0, 0, 0};
    bool intersect = false;
    int32_t nodeCount = 0;
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
    nodeCount += link->nodes->size + link->joints->size;

    for(int32_t i = 0; i < link->links->size; i++)
    {
        dopoo_link* l = (dopoo_link*)(link->links->data[i]);
        if(dopoo_link_intersect(l, ray, num, &n0, &t0))
        {
            intersect = true;
            if(*t > t0)
            {
                *t = t0;
                *n = n0;
                *num += nodeCount;
            }
        }
        nodeCount += dopoo_link_nodeCount(l);
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
    {
        num -= link->nodes->size + link->joints->size;
        for(int32_t i = 0; i < link->links->size; i++)
        {
            dopoo_link* l = (dopoo_link*)(link->links->data[i]);
            if(num < l->nodes->size + l->joints->size)
                return dopoo_link_getRgb(l, num);
            else
                num -= dopoo_link_nodeCount(l);
        }
    }
    return (dopoo_vec3D){0, 0, 0};
}

dopoo_vec3D
dopoo_link_getLineRgb(const dopoo_link* link)
{
    return link->lineRgb;
}





