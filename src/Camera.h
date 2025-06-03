#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MathsOperations.h"

struct Camera
    {
    unsigned int camid; // i.e. entity ID
    vec2 zoomcomponent; // i.e. scale
    vec2 poscomponent;  // i.e. pos
    int* scrspx;    // screen dimension y
    int* scrspy;    // screen dimension x
    };
typedef struct Camera Camera;

Camera CreateCamera(vec2 pos, vec2 scale, int* scrwid, int* srchig);

m4 getCameraMatrix(Camera cam);
