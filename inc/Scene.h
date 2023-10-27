#ifndef __DOPOOSCENE__
#define __DOPOOSCENE__

#include <stdlib.h>
#include <stdint.h>
#include "List.h"
#include "Link.h"
#include "Camera.h"


typedef struct
{
    dopoo_list*  links;
}dopoo_scene;

dopoo_scene*
dopoo_scene_create(int32_t linkSize);

void
dopoo_scene_clear(dopoo_scene* scene);

void
dopoo_scene_addLink(dopoo_scene* scene, dopoo_link* link);

dopoo_link*
dopoo_scene_getLink(const dopoo_scene* scene, int32_t i);

bool
dopoo_scene_intersect(const dopoo_scene* scene, dopoo_rayD* ray, int32_t* linkIndex, int32_t* nodeIndex, dopoo_vec3D* n, double* t);

#endif