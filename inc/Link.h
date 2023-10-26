#ifndef __DOPOOLINK__
#define __DOPOOLINK__

#include <stdbool.h>
#include "Ray.h"
#include "List.h"

typedef struct
{
    dopoo_list*  nodes;
    dopoo_list* joints;
}dopoo_link;

bool
dopoo_link_intersect(const dopoo_link* link, dopoo_rayD* ray, int32_t* num, dopoo_vec3D* n, double* t);

dopoo_vec3D
dopoo_link_getRgb(const dopoo_link* link, int32_t num);

dopoo_link*
dopoo_link_create(int32_t nodeSize, int32_t jointSize);

void
dopoo_link_clear(dopoo_link* link);

void
dopoo_link_addNode(dopoo_link* link, void* node);

void
dopoo_link_addJoint(dopoo_link* link, void* joint);

void*
dopoo_link_getNode(const dopoo_link* link, int32_t i);

void*
dopoo_link_getJoint(const dopoo_link* link, int32_t i);


#endif