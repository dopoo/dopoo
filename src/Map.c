#include <assert.h>
#include "../inc/Map.h"
#include "../inc/Math.h"

dopoo_vec3D
dopoo_mapD_applyR(dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_quatD_rotate(map->r, v);
}

dopoo_vec3D
dopoo_mapD_applyRS(dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_vec3D_scale(dopoo_quatD_rotate(map->r, v), map->s);
}

dopoo_vec3D
dopoo_mapD_applyRST(dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_vec3D_add(dopoo_vec3D_scale(
           dopoo_quatD_rotate(map->r, v), map->s),
           dopoo_vec3D_scale(map->t, map->s));
}

dopoo_vec3D
dopoo_mapD_applyInvR(dopoo_mapD* map, dopoo_vec3D v)
{
    return dopoo_quatD_rotate(dopoo_quatD_inverse(map->r), v);
}

dopoo_vec3D
dopoo_mapD_applyInvRS(dopoo_mapD* map, dopoo_vec3D v)
{
    assert(map->s > deltaD);
    return dopoo_vec3D_scale(dopoo_mapD_applyInvR(map, v), 1 / map->s);
}

dopoo_vec3D
dopoo_mapD_applyInvRST(dopoo_mapD* map, dopoo_vec3D v)
{
    assert(map->s > deltaD);
    return dopoo_vec3D_scale(dopoo_mapD_applyInvR(map, dopoo_vec3D_minus(v, 
                             dopoo_vec3D_scale(map->t, map->s))), 1 / map->s);
}