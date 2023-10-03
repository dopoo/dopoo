#include "math.h"
#include "../inc/Quaternion.h"
#include "../inc/Math.h"
#include "../inc/Common.h"
#include "../inc/Vec.h"

double
dopoo_quatD_length(dopoo_quatD q)
{
    return sqrt(q.x * q.x + q.y * q.y +
                q.z * q.z + q.w * q.w);
}

dopoo_quatD
dopoo_quatD_norm(dopoo_quatD q)
{
    dopoo_quatD nq;
    double length = dopoo_quatD_length(q);
    if(length < toleranceF)
    {
        dopoo_print(true, "the length of quaternion is too small to normalize!\n");   
        nq = (dopoo_quatD){0, 0, 0, 1};
        return nq;
    }
    nq.x = q.x / length;
    nq.y = q.y / length;
    nq.z = q.z / length;
    nq.w = q.w / length;
    return nq;
}

dopoo_quatD
dopoo_quatD_negative(dopoo_quatD q)
{
    return (dopoo_quatD){-q.x, -q.y, -q.z, q.w};
}

dopoo_vec3D
dopoo_quatD_getVec(dopoo_quatD q)
{
    return (dopoo_vec3D){q.x, q.y, q.z};
}

dopoo_vec3D
dopoo_quatD_rotate(dopoo_quatD q, dopoo_vec3D v)
{
    q = dopoo_quatD_norm(q);
    dopoo_vec3D qv = dopoo_quatD_getVec(q);
    double x = q.w * q.w - dopoo_vec3D_lengthSqr(qv);
    double y = dopoo_vec3D_dot(qv, v);
    dopoo_vec3D cqvv = dopoo_vec3D_cross(qv, v);
    return dopoo_vec3D_add(dopoo_vec3D_scale(v, x), 
                           dopoo_vec3D_add(dopoo_vec3D_scale(qv, 2*y), dopoo_vec3D_scale(cqvv, 2 * q.w)));
}

void
dopoo_quatD_q2m(double m[][3], dopoo_quatD q)
{
    q = dopoo_quatD_norm(q);
    m[0][0] = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
    m[1][1] = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
    m[2][2] = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
    m[0][1] = 2 * q.x * q.y + 2 * q.z * q.w;
    m[1][0] = 2 * q.x * q.y - 2 * q.z * q.w;
    m[0][2] = 2 * q.x * q.z - 2 * q.y * q.w;
    m[2][0] = 2 * q.x * q.z + 2 * q.y * q.w;
    m[1][2] = 2 * q.y * q.z + 2 * q.x * q.w;
    m[2][1] = 2 * q.y * q.z - 2 * q.x * q.w;
}

dopoo_quatD
dopoo_quatD_m2q(double m[][3])
{
    double trace = m[0][0] + m[1][1] + m[2][2];
    if (trace > 0.0f)
    {
        double k = 0.5f / sqrt(1.0f + trace);
        return (dopoo_quatD){ k * (m[1][2] - m[2][1]), k * (m[2][0] - m[0][2]), k * (m[0][1] - m[1][0]), 0.25f / k };
    }
    else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2]))
    {
        double k = 0.5f / sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]);
        return (dopoo_quatD){ 0.25f / k, k * (m[1][0] + m[0][1]), k * (m[2][0] + m[0][2]), k * (m[1][2] - m[2][1]) };
    }
    else if (m[1][1] > m[2][2])
    {
        double k = 0.5f / sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]);
        return (dopoo_quatD){  k * (m[1][0] + m[0][1]), 0.25f / k, k * (m[2][1] + m[1][2]), k * (m[2][0] - m[0][2]) };
    }
    else {
        double k = 0.5f / sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]);
        return (dopoo_quatD){  k * (m[2][0] + m[0][2]), k * (m[2][1] + m[1][2]), 0.25f / k, k * (m[0][1] - m[1][0]) };
    }
}

void
dopoo_quatD_print(dopoo_quatD q, const char* label)
{
    q = dopoo_quatD_norm(q);
    dopoo_print(true, "%s: %f %f %f %f\n", label, q.x, q.y, q.z, q.w);
}



