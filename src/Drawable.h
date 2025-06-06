#pragma once
#include "Entity.h"
#include "Camera.h"

struct Drawables {
    unsigned int* trsids;
    unsigned int* rids;
    unsigned int size;
};
typedef struct Drawables Drawables;

Drawables InitialiseDrawables();

void AddDrawable(Drawables* drabs, unsigned int trid, unsigned int rid);

void RemoveDrawable(Drawables* drabs, RenderDetails* rds, TransformationDetails* tds, unsigned int trid);

void DrawDrawables(RenderDetails rds, TransformationDetails tds, Drawables drabs, Camera cam);