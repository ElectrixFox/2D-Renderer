#pragma once
#include "MathsOperations.h"
#include "Input.h"
#include "Shader.h"

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

/**
 * Moves the camera using the keys pressed
 * 
 * @param cam A pointer to the camera
 * 
 * @returns 1 if the camera has been moved otherwise 0
 */
int MoveCamera(Camera* cam);

/**
 * Applies the view matrix to the program
 * 
 * @param cam The camera in the scene
 * @param progs The shader programs
 * @param size The number of programs
 */
void _ApplyCamera(Camera cam, unsigned int* progs, unsigned int size);

/**
 * Applies a matrix to keep the given programs static on the screen with relation to the camera
 * 
 * @param cam The camera
 * @param progs The shader programs
 * @param size The number of programs
 */
void _ApplyStaticCamera(Camera cam, unsigned int* progs, unsigned int size);