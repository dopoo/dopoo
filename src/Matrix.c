#include "assert.h"
#include "math.h"
#include "string.h"
#include "../inc/Matrix.h"

void
dopoo_mat3D_createRotateMatrix(double mat[][3], dopoo_axis axis, double radians)
{
    memset(mat, 0, sizeof(double) * 9);
    mat[0][0] = mat[1][1] = mat[2][2] = 1;
    double c = cos(radians);
    double s = sin(radians); 
    switch (axis) {
    case X_AXIS:
        {
            mat[1][1] = c;
            mat[1][2] = -s;
            mat[2][1] = s;
            mat[2][2] = c;
        }
        break;

    case Y_AXIS:
        {
            mat[0][0] = c;
            mat[0][2] = -s;
            mat[2][0] = s;
            mat[2][2] = c;
        }
        break;

    case Z_AXIS:
        {
            mat[0][0] = c;
            mat[0][1] = -s;
            mat[1][0] = s;
            mat[1][1] = c;
        }
        break;
        
    default:
        assert(axis==X_AXIS || axis==Y_AXIS || axis==Z_AXIS);
    }   
}

/*this = this * other*/
void
dopoo_mat3D_postMult(double this[][3], const double other[][3])
{
    double res[3][3];
    for (int32_t rowIdx = 0; rowIdx < 3; rowIdx++)
    {
        for (int32_t colIdx = 0; colIdx < 3; colIdx++)
        {

                    res[rowIdx][colIdx] = (this[rowIdx][0] * other[0][colIdx] + this[rowIdx][1] * other[1][colIdx]
                                                + this[rowIdx][2] * other[2][colIdx] );
        }
    }

    for (int32_t rowIdx = 0; rowIdx < 3; rowIdx++)
    {
        for (int32_t colIdx = 0; colIdx < 3; colIdx++)
        {
            this[rowIdx][colIdx] = res[rowIdx][colIdx];
        }
    }
}

/*https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix*/
void
dopoo_mat3D_inverse(double invMat[][3], double mat[][3])
{
    double determinant = 0;
    double transposeMat[3][3];

    //transpose
    for(int32_t row = 0; row < 3; row++)
        for(int32_t col = 0; col < 3; col++)
            transposeMat[row][col] = mat[col][row];

    //finding determinant
    for(int32_t col = 0; col < 3; col++)
        determinant = determinant + (transposeMat[0][col] * (transposeMat[1][(col+1)%3] * transposeMat[2][(col+2)%3] 
                                                           - transposeMat[1][(col+2)%3] * transposeMat[2][(col+1)%3]));

    for(int32_t row = 0; row < 3; row++)
        for(int32_t col = 0; col < 3; col++)
            invMat[row][col] = ((transposeMat[(row+1)%3][(col+1)%3] * transposeMat[(row+2)%3][(col+2)%3]) 
                              - (transposeMat[(row+1)%3][(col+2)%3] * transposeMat[(row+2)%3][(col+1)%3]))/ determinant;
    
}

dopoo_vec3D
dopoo_mat3D_postRotate(double m[][3], dopoo_vec3D v)
{
    dopoo_vec3D dst;

    dst.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
    dst.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
    dst.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];

    return dst;
}
