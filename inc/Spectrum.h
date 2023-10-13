#ifndef __DOPOOSPECTRUM__
#define __DOPOOSPECTRUM__

#include <stdint.h>

#ifdef XCODE_PROGRAM

typedef union{
    struct{
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    } sColor;

    int32_t iColor;
} dopoo_rgbI;

#else

typedef union{
    struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    } sColor;

    int32_t iColor;
} dopoo_rgbI;

#endif

typedef struct{
    double r;
    double g;
    double b;
} dopoo_rgbD;

dopoo_rgbI
dopoo_rgb_DtoI(dopoo_rgbD d);


#endif