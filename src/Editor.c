#include "Editor.h"

void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, BLOCK block, vec2 position)
{
unsigned int sprite = 1;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = 2; // To-Do: write some function to find the number of sprites in the sheet

unsigned int rd = CreateSpriteRenderable(rds, "res/sprites/movable_spritesheet.png", nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);

unsigned int ent = AddEntity(ents, td, 1);
}

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, unsigned int eid)
{
int index = getEntitiesIDIndex(*ents, eid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, ents->trsid[index]); // remove the drawable
RemoveEntity(ents, eid);
}