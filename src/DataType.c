#include "../inc/DataType.h"
#include "../inc/Joint.h"
#include "../inc/Node.h"
#include "../inc/Link.h"

void
dopoo_dataType_clear(void* d)
{
    dopoo_dataType type = *((dopoo_dataType*)d);
    switch(type)
    {
        case JOINT2:
            dopoo_joint2_clear((dopoo_joint2*)(d));
        case NODE2:
            dopoo_node2_clear((dopoo_node2*)(d));
        case LINK:
            dopoo_link_clear((dopoo_link*)(d));
        default:
            break;
    }
}