#include "math.h"
#include "assert.h"
#include "../inc/Quaternion.h"
#include "../inc/Math.h"
#include "../inc/Common.h"
#include "../inc/Vec.h"

dopoo_quatD
dopoo_quatD_create(double x, double y, double z, double w)
{
    return dopoo_quatD_norm((dopoo_quatD){x, y, z, w});
}

double
dopoo_quatD_length(dopoo_quatD q)
{
    return sqrt(q.x * q.x + q.y * q.y +
                q.z * q.z + q.w * q.w);
}

double
dopoo_quatD_lengthSqr(dopoo_quatD q)
{
    return  q.x * q.x + q.y * q.y +
            q.z * q.z + q.w * q.w;
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
dopoo_quatD_inverse(dopoo_quatD q)
{
    return (dopoo_quatD){-q.x, -q.y, -q.z, q.w};
}

dopoo_vec3D
dopoo_quatD_getVec(dopoo_quatD q)
{
    return (dopoo_vec3D){q.x, q.y, q.z};
}

//(w^2 -||vq||^2)v+2(vq dot v)vq+2w(vq cross v)
dopoo_vec3D
dopoo_quatD_rotate(dopoo_quatD q, dopoo_vec3D v)
{
    assert(fabs(dopoo_quatD_lengthSqr(q) - 1) < deltaD);
    dopoo_vec3D vq = dopoo_quatD_getVec(q);
    double x = q.w * q.w - dopoo_vec3D_lengthSqr(vq);
    double y = dopoo_vec3D_dot(vq, v);
    dopoo_vec3D cvqv = dopoo_vec3D_cross(vq, v);
    return dopoo_vec3D_add(dopoo_vec3D_scale(v, x), 
                           dopoo_vec3D_add(dopoo_vec3D_scale(vq, 2*y), dopoo_vec3D_scale(cvqv, 2 * q.w)));
}

// q0q1 = w0w1 - vq0 dot vq1 + w0vq1 + w1vq0 + vq0 cross vq1.
dopoo_quatD
dopoo_quatD_mult(dopoo_quatD q0, dopoo_quatD q1)
{
    dopoo_vec3D vq0 = dopoo_quatD_getVec(q0);
    dopoo_vec3D vq1 = dopoo_quatD_getVec(q1);
    double w = q0.w * q1.w - dopoo_vec3D_dot(vq0, vq1);
    dopoo_vec3D v = dopoo_vec3D_add(
                    dopoo_vec3D_cross(vq0, vq1), dopoo_vec3D_add(
                    dopoo_vec3D_scale(vq1, q0.w), dopoo_vec3D_scale(vq0, q1.w)));
    return (dopoo_quatD){v.x, v.y, v.z, w};
}

void
dopoo_quatD_q2m(double m[][3], dopoo_quatD q)
{
    assert(fabs(dopoo_quatD_lengthSqr(q) - 1) < deltaD);
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

double 
dopoo_quatD_rad(dopoo_quatD q)
{
    assert(fabs(dopoo_quatD_lengthSqr(q) - 1) < deltaD);
    return 2*acos(q.w);
}

void
dopoo_quatD_print(dopoo_quatD q, const char* label)
{
    dopoo_print(true, "%s: %f %f %f %f\n", label, q.x, q.y, q.z, q.w);
}



