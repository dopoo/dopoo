#include <float.h>
#include "../inc/Scene.h"

dopoo_scene*
dopoo_scene_create(int32_t linkSize)
{
    dopoo_scene* scene = (dopoo_scene*)malloc(sizeof(dopoo_scene));
    scene->links = dopoo_list_create(linkSize);
    return scene; 
}

void
dopoo_scene_clear(dopoo_scene* scene)
{
    dopoo_list_clear(scene->links);
    free(scene);
}

void
dopoo_scene_addLink(dopoo_scene* scene, dopoo_link* link)
{
    dopoo_list_add(scene->links, link);
}

dopoo_link*
dopoo_scene_getLink(const dopoo_scene* scene, int32_t i)
{
    return (dopoo_link*)(dopoo_list_get(scene->links, i));
}

bool
dopoo_scene_intersect(const dopoo_scene* scene, dopoo_rayD* ray, int32_t* linkIndex, int32_t* nodeIndex, dopoo_vec3D* n, double* t)
{
    *t = DBL_MAX;
    double t0 = DBL_MAX;
    dopoo_vec3D n0 = {0, 0, 0};
    bool intersect = false;
    for(int32_t i = 0; i < scene->links->size; i++)
    {
        dopoo_link* link = (dopoo_link*)(scene->links->data[i]);
        if(dopoo_link_intersect(link, ray, nodeIndex, &n0, &t0))
        {
            intersect = true;
            if(*t > t0)
            {
                *t = t0;
                *n = n0;
                *linkIndex = i;
            }
        }
    }
    return intersect;
}