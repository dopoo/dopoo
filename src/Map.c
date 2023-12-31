#include <assert.h>
#include "../inc/Map.h"
#include "../inc/Math.h"


dopoo_vec3D
dopoo_mapD_applyR(const dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_quatD_rotate(map->r, v);
}

dopoo_vec3D
dopoo_mapD_applyRS(const dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_vec3D_scale(dopoo_mapD_applyR(map, v), map->s);
}

dopoo_vec3D
dopoo_mapD_applyRST(const dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_vec3D_add(dopoo_mapD_applyRS(map, v), map->t);
}

dopoo_vec3D
dopoo_mapD_applyInvR(const dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_quatD_rotate(dopoo_quatD_inverse(map->r), v);
}

dopoo_vec3D
dopoo_mapD_applyInvRS(const dopoo_mapD* map, dopoo_vec3D v)
{
    assert(map->s > deltaD);
    return dopoo_vec3D_scale(dopoo_mapD_applyInvR(map, v), 1 / map->s);
}

dopoo_vec3D
dopoo_mapD_applyInvRST(const dopoo_mapD* map, dopoo_vec3D v)
{
    assert(map->s > deltaD);
    return dopoo_vec3D_scale(dopoo_mapD_applyInvR(map, 
                             dopoo_vec3D_minus(v, map->t)), 1 / map->s);
}

void
dopoo_mapD_addTransit(dopoo_mapD* map, dopoo_vec3D v)
{
    map->t = dopoo_vec3D_add(map->t, v);
}

void
dopoo_mapD_addRotate(dopoo_mapD* map, dopoo_quatD q)
{
    map->r = dopoo_quatD_mult(q, map->r);
}

void
dopoo_mapD_init(dopoo_mapD* map)
{
    map->r = dopoo_quatD_create(0, 0, 0, 1);
    map->t = (dopoo_vec3D){0, 0, 0};
    map->s = 1;
}
