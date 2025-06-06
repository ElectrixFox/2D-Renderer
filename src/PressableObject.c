#include "PressableObject.h"

int _CheckPressed(vec2* poses, vec2* scales, vec2 cursorpos, unsigned int eid)
{
unsigned int index = eid; // some hash function to get where the eid is in the big array

if(PointInSquare(cursorpos, poses[index], scales[index]))
    return 1;
return 0;
}