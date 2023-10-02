#include "math.h"
#include "../inc/Quaternion.h"
#include "../inc/Math.h"
#include "../inc/Common.h"

double
dopoo_quaternionD_length(dopoo_quaternionD quat)
{
    return sqrt(quat.x * quat.x + quat.y * quat.y +
                quat.z * quat.z + quat.w * quat.w);
}

dopoo_quaternionD
dopoo_quaternionD_norm(dopoo_quaternionD quat)
{
    dopoo_quaternionD nq;
    double length = dopoo_quaternionD_length(quat);
    if(length < toleranceF)
    {
        dopoo_printf(true, "the length of quaternion is too small to normalize!\n");   
        nq = (dopoo_quaternionD){0, 0, 0, 1};
        return nq;
    }
    nq.x = quat.x / length;
    nq.y = quat.y / length;
    nq.z = quat.z / length;
    nq.w = quat.w / length;
    return nq;
}