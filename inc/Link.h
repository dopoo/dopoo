#ifndef __DOPOOLINK__
#define __DOPOOLINK__

#include <stdbool.h>
#include "Ray.h"
#include "List.h"
#include "Joint.h"
#include "Node.h"

typedef struct
{
    dopoo_vec3D lineRgb;
    dopoo_mapD map;
    dopoo_list*  nodes;
    dopoo_list* joints;
    dopoo_list* links;
    bool drawBorderLine;
}dopoo_link;

bool
dopoo_link_intersect(const dopoo_link* link, dopoo_rayD* ray, int32_t* num, dopoo_vec3D* p, dopoo_vec3D* n, double* t);

dopoo_vec3D
dopoo_link_getRgb(const dopoo_link* link, int32_t num);

dopoo_link*
dopoo_link_create(int32_t nodeSize, int32_t jointSize, dopoo_vec3D lineRgb);

void
dopoo_link_clear(dopoo_link* link);

void
dopoo_link_addNode(dopoo_link* link, dopoo_node2* node);

void
dopoo_link_addJoint(dopoo_link* link, dopoo_joint2* joint);

dopoo_node2*
dopoo_link_getNode(const dopoo_link* link, int32_t i);

dopoo_joint2*
dopoo_link_getJoint(const dopoo_link* link, int32_t i);

dopoo_vec3D
dopoo_link_getLineRgb(const dopoo_link* link);

#endif