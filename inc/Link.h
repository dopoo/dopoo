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



#endif