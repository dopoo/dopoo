#include "../inc/Matrix.h"

void
dopoo_matrix3F_createRotateMatrix(float mat[][3], dopoo_axis axis, float radians)
{
    memset(mat, 0, sizeof(float) * 9);
    mat[0][0] = mat[1][1] = mat[2][2] = 1;
    float c = cos(radians);
    float s = sin(radians); 
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
dopoo_matrix3F_postMult(float this[][3], const float other[][3])
{
    float res[3][3];
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
dopoo_matrix3F_inverse(float invMat[][3], float mat[][3])
{
    float determinant = 0;
    float transposeMat[3][3];

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
