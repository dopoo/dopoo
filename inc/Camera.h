#ifndef __DOPOOCAMERA__
#define __DOPOOCAMERA__

#include <stdint.h>
#include "Spectrum.h"
#include "Ray.h"
#include "Map.h"

typedef enum {
	PERSPECTIVECAMERA = 0,
	ORTHOGRAPHICCAMERA = 1
} dopoo_cameraType;

typedef struct{
	int32_t width, height;
    dopoo_color* pixels;
} dopoo_film;

typedef struct{
    dopoo_cameraType type;
    dopoo_film film;
    double screenWidth, screenHeight;
    dopoo_rayD ray;
    dopoo_mapD map;
} dopoo_camera;

#endif