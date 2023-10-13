#include "../inc/Spectrum.h"
#include "../inc/Math.h"

dopoo_rgbD
dopoo_RGB_clamp(dopoo_rgbD d)
{
	d.r = dopoo_double_clamp(d.r, 0, 1.0);
	d.g = dopoo_double_clamp(d.g, 0, 1.0);
	d.b = dopoo_double_clamp(d.b, 0, 1.0);
	return d;
}

dopoo_rgbI
dopoo_rgb_DtoI(dopoo_rgbD d)
{
    dopoo_rgbI i;
    d = dopoo_RGB_clamp(d);

    i.sColor.r = ((uint8_t)(d.r * 255));
    i.sColor.g = ((uint8_t)(d.g * 255));
    i.sColor.b = ((uint8_t)(d.b * 255));
    i.sColor.a = 255;

    return i;
}