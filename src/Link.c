#include <stdlib.h>
#include <stdint.h>
#include "../inc/Link.h"

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




