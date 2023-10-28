#include <string.h>
#include <stdlib.h>
#include <float.h>
#include "../inc/Camera.h"

void
dopoo_film_init(dopoo_film* film, int32_t width, int32_t height)
{
    film->width = width;
    film->height = height;
    film->pixel = (dopoo_rgbI*)malloc(sizeof(dopoo_rgbI) * width * height);
    memset(film->pixel, 0, sizeof(dopoo_rgbI) * width * height);
    for(int32_t i = 0; i < width; i++)
        for(int32_t j = 0; j < height; j++)
        {
            dopoo_rgbI* c = film->pixel+ j * width + i;
            c->sColor.a = 0xff;
        }
}

void 
dopoo_film_clear(dopoo_film film)
{
    free(film.pixel);
}

void 
dopoo_camera_initRay(dopoo_camera* camera)
{
    dopoo_rayD_setT0(&(camera->ray), 1e-3);
    dopoo_rayD_setT1(&(camera->ray), DBL_MAX);
    dopoo_vec3D p = {0, 0, 0};
    p = dopoo_mapD_applyRST(&(camera->map), p);
    dopoo_rayD_setP(&(camera->ray), p);

    dopoo_vec3D d = {0, 0, -1};
    d = dopoo_mapD_applyRS(&(camera->map), d);
    d = dopoo_vec3D_norm(d);
    dopoo_rayD_setD(&(camera->ray), d);
}

void
dopoo_camera_init(dopoo_camera* camera, double width, double height, 
                  dopoo_quatD rotate, dopoo_vec3D transit, double screenWidth, dopoo_cameraType type)
{
    dopoo_film_init(&(camera->film), width, height);
    camera->screenWidth = screenWidth;
    camera->screenHeight = screenWidth * height / width;

    dopoo_mapD_init(&(camera->map));
    dopoo_mapD_addRotate(&(camera->map), rotate);
    dopoo_mapD_addTransit(&(camera->map), transit);

    dopoo_camera_initRay(camera);
    camera->type = type;
}

dopoo_camera*
dopoo_camera_create(double width, double height, 
                  dopoo_quatD rotate, dopoo_vec3D transit, dopoo_cameraType type)
{
    dopoo_camera* camera = (dopoo_camera*)malloc(sizeof(dopoo_camera));
    dopoo_camera_init(camera, width, height, rotate, transit, 1.5, type);
    return camera;
}

void
dopoo_camera_clear(dopoo_camera* camera)
{
    if(!camera) return;
    dopoo_film_clear(camera->film);
    free(camera);
}

dopoo_vec3D
dopoo_camera_rasterToScreen(const dopoo_camera* camera, double i, double j, double z)
{
    return (dopoo_vec3D) {(2 * i / (double)(camera->film.width) - 1) * camera->screenWidth,
                          (1 - 2 * j / (double)(camera->film.height)) * camera->screenHeight,
                           z};
}

void
dopoo_orthographicCamera_getRay(const dopoo_camera* camera, dopoo_rayD* ray, int32_t i, int32_t j, double iOffset, double jOffset) 
{
    *ray = camera->ray;
    ray->p = dopoo_camera_rasterToScreen(camera, (double)(i) + iOffset, (double)(j) + jOffset, 0.0);
    ray->p = dopoo_mapD_applyRST(&(camera->map), ray->p);
}

void
dopoo_perspectiveCamera_getRay(const dopoo_camera* camera, dopoo_rayD* ray, int32_t i, int32_t j, double iOffset, double jOffset) 
{
    *ray = camera->ray;
    ray->d = dopoo_camera_rasterToScreen(camera, (double)(i) + iOffset, (double)(j) + jOffset, -1.0);
    ray->d = dopoo_vec3D_norm(dopoo_mapD_applyRS(&(camera->map), ray->d));
}

void
dopoo_camera_getRay(const dopoo_camera* camera, dopoo_rayD* ray, int32_t i, int32_t j, double iOffset, double jOffset)
{
    dopoo_cameraType type = camera->type;
    switch (type)
    {
        case PERSPECTIVECAMERA:
            return dopoo_perspectiveCamera_getRay(camera, ray, i, j, iOffset, jOffset);
            break;
        case ORTHOGRAPHICCAMERA:
            return dopoo_orthographicCamera_getRay(camera, ray, i, j, iOffset, jOffset);
            break;
        default:
            break;
    }
}

int32_t
dopoo_camera_getWidth(const dopoo_camera* camera)
{
    return camera->film.width;
}

int32_t
dopoo_camera_getHeight(const dopoo_camera* camera)
{
    return camera->film.height;
}

dopoo_rgbI*
dopoo_camera_getPixel(const dopoo_camera* camera)
{
    return camera->film.pixel;
}

