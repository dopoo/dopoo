#include "math.h"
#include "../inc/Quaternion.h"
#include "../inc/Math.h"
#include "../inc/Common.h"

double
dopoo_quaternionF_length(dopoo_quaternionF quat)
{
    return sqrt(quat.x * quat.x + quat.y * quat.y +
                quat.z * quat.z + quat.w * quat.w);
}

dopoo_quaternionF
dopoo_quaternionF_norm(dopoo_quaternionF quat)
{
    dopoo_quaternionF nq;
    double length = dopoo_quaternionF_length(quat);
    if(length < toleranceF)
    {
        dopoo_printf(true, "the length of quaternion is too small to normalize!\n");   
        nq = (dopoo_quaternionF){0, 0, 0, 1};
        return nq;
    }
    nq.x = quat.x / length;
    nq.y = quat.y / length;
    nq.z = quat.z / length;
    nq.w = quat.w / length;
    return nq;
}