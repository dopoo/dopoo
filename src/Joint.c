#include <stdlib.h>
#include "../inc/Joint.h"



dopoo_joint2*
dopoo_joint2_create(dopoo_vec3D c, double r, dopoo_rgbI rgb, void* prev, void* next)
{
    dopoo_joint2* joint = (dopoo_joint2*)malloc(sizeof(dopoo_joint2));
    joint->c = c;
    joint->r = r;
    joint->rgb = rgb;
    joint->prev = prev;
    joint->next = next;
    return joint;
}

void
dopoo_joint2_clear(dopoo_joint2* joint)
{
    free(joint);
}