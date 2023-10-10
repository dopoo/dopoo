#ifndef __DOPOOTESTMAP__
#define __DOPOOTESTMAP__

#include "../inc/Map.h"

static inline void 
dopoo_testMap()
{
    dopoo_mapD map = {dopoo_quatD_create(1, 0, 0, 1), {1, 1, 0}, 10};
    dopoo_vec3D v = {0, 1, 0};
    dopoo_vec3D rv = dopoo_mapD_applyR(&map, v);
    dopoo_vec3D rsv = dopoo_mapD_applyRS(&map, v);
    dopoo_vec3D rstv = dopoo_mapD_applyRST(&map, v);
    dopoo_vec3D invrv = dopoo_mapD_applyInvR(&map, rv);
    dopoo_vec3D invrsv = dopoo_mapD_applyInvRS(&map, rsv);
    dopoo_vec3D invrstv = dopoo_mapD_applyInvRST(&map, rstv);

    dopoo_vec3D_print(v, "v");
    dopoo_vec3D_print(rv, "rv");
    dopoo_vec3D_print(rsv, "rsv");
    dopoo_vec3D_print(rstv, "rstv");
    dopoo_vec3D_print(invrv, "invrv");
    dopoo_vec3D_print(invrsv, "invrsv");
    dopoo_vec3D_print(invrstv, "invrstv");

}


#endif