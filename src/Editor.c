#include "Editor.h"

void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, BLOCK block, vec2 position)
{
unsigned int sprite = 1;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = 2; // To-Do: write some function to find the number of sprites in the sheet

unsigned int rd = CreateSpriteRenderable(rds, "res/sprites/movable_spritesheet.png", nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

AddDrawable(drabs, td, rd);
AddEntity(ents, td, 1);
}

void RemoveBlock(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents, unsigned int eid)
{
int index = getEntitiesIDIndex(*ents, eid); // finding the ID
if(index == -1)
    return; // if the index isn't found just quit

RemoveDrawable(drabs, rds, tds, ents->trsid[index]); // remove the drawable
RemoveEntity(ents, eid);
}

void BuildSelectBar(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs, Entities* ents)
{
vec2 topright = {1255.0f, 695.0f};
const unsigned int nsheets = 2;
const float padding = 10.0f;
const unsigned int nsprites[] = {2, 1};
const char* spritesheets[] = {
    "res/sprites/movable_spritesheet.png",
    "res/sprites/movable_barrier_tilesheet.png"
};

int spacer = 0;
for (int i = 0; i < nsheets; i++)
    {
    for (int sprite = 1; sprite < nsprites[i] + 1; sprite++)
        {
        vec2 position = {topright.x, topright.y - (spacer * 50.0f + padding)}; // placing the items in a vertical line on the right side of the screen
        
        unsigned int rd = CreateSpriteRenderable(rds, spritesheets[i], nsprites[i], sprite);
        unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

        AddDrawable(drabs, td, rd);

        AddEntity(ents, td, 0);
        spacer++; // increase the spacer for the next item
        }
    }
}