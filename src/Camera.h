#pragma once
#include "MathsOperations.h"
#include "Input.h"

struct Camera
    {
    unsigned int camid; // i.e. entity ID
    vec2 poscomponent;  // i.e. pos
    vec2 zoomcomponent; // i.e. scale
    int* scrspx;    // screen dimension y
    int* scrspy;    // screen dimension x
    };
typedef struct Camera Camera;

Camera CreateCamera(vec2 pos, vec2 scale, int* scrwid, int* srchig);

m4 getCameraMatrix(Camera cam);

void MoveCamera(Camera* cam);

/**
 * Applies the view matrix to the program
 * 
 * @param cam The camera in the scene
 * @param progs The shader programs
 * @param size The number of programs
 */
void _ApplyCamera(Camera cam, unsigned int* progs, unsigned int size);

