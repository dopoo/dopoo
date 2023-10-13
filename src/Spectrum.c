#include "../inc/Spectrum.h"
#include "../inc/Math.h"

dopoo_rgbI
dopoo_rgbI_fromVec(dopoo_vec3D v)
{
    dopoo_rgbI rgb;
    v = dopoo_vec3D_clamp(v);

    rgb.sColor.r = ((uint8_t)(v.x * 255));
    rgb.sColor.g = ((uint8_t)(v.y * 255));
    rgb.sColor.b = ((uint8_t)(v.z * 255));
    rgb.sColor.a = 255;

    return rgb;
}