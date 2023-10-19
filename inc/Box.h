#ifndef __DOPOOBOX__
#define __DOPOOBOX__

#include <stdbool.h>
#include "Vec.h"

typedef struct{
    dopoo_vec3D min;
    dopoo_vec3D max;
} dopoo_boxD;

bool
dopoo_boxD_isZero(const dopoo_boxD* box);

#endif