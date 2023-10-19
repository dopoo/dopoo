#include "../inc/Link.h"

#include "stdlib.h"

dopoo_joint*
dopoo_joint_create(dopoo_vec3D c, double r, dopoo_rgbI rgb, void* prev, void* next)
{
    dopoo_joint* joint = (dopoo_joint*)malloc(sizeof(dopoo_joint));
    joint->c = c;
    joint->r = r;
    joint->rgb = rgb;
    joint->prev = prev;
    joint->next = next;
    return joint;
}

void
dopoo_joint_clear(dopoo_joint* joint)
{
    free(joint);
}


