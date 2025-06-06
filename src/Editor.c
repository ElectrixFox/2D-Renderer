#include "Editor.h"

void PlaceBlock(RenderDetails* rds, TransformationDetails* tds, Entities* ents, BLOCK block, vec2 position)
{
unsigned int sprite = 1;    // To-Do: write some function to find the sprite from the enum
unsigned int nosprites = 2; // To-Do: write some function to find the number of sprites in the sheet

unsigned int rd = CreateSpriteRenderable(rds, "res/sprites/movable_spritesheet.png", nosprites, sprite);
unsigned int td = AddTransformation(tds, position, (vec2){25.0f, 25.0f});

unsigned int ent = CreateEntity(ents, rd, td);
}