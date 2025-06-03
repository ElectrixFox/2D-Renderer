#include "Camera.h"

Camera CreateCamera(vec2 pos, vec2 scale, int* scrwid, int* srchig)
{
return (Camera){0, pos, scale, scrwid, srchig};
}

m4 getCameraMatrix(Camera cam)
{
//  the camera matrix is effectively a projection matrix with a position component
return 
    (m4){
         2 / (float)cam.zoomcomponent.x, 0.0f, 0.0f, 0.0f, // (float)(cam.poscomponent.x),
         0.0f, 2 / (float)cam.zoomcomponent.y, 0.0f, 0.0f, // (float)(cam.poscomponent.y),
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    };
}
