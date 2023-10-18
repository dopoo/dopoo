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
    dopoo_rgbI* pixel;
} dopoo_film;

typedef struct{
    dopoo_cameraType type;
    dopoo_film film;
    double screenWidth, screenHeight;
    dopoo_rayD ray;
    dopoo_mapD map;
} dopoo_camera;

void
dopoo_camera_getRay(const dopoo_camera* camera, dopoo_rayD* ray, int32_t i, int32_t j, double iOffset, double jOffset);

int32_t
dopoo_camera_getWidth(const dopoo_camera* camera);

int32_t
dopoo_camera_getHeight(const dopoo_camera* camera);

dopoo_rgbI*
dopoo_camera_getPixel(const dopoo_camera* camera);

dopoo_camera*
dopoo_camera_create(double width, double height, 
                  dopoo_quatD rotate, dopoo_vec3D transit, dopoo_cameraType type);

#endif