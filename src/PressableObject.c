#include "PressableObject.h"

PressableArray InitPressableArray(unsigned int size)
{

}

void AddPressable(unsigned int* presids, unsigned int eid, unsigned int* n)
{
(*n)++;
presids[*n] = eid;
}

void RemovePressable(unsigned int* presids, unsigned int eid, unsigned int* n)
{
for (int i = 0; i < (*n); i++)
    {
    if(presids[i] == eid)
        presids[i] = (NULL);
    }
(*n)--;
}

int CheckPressed(unsigned int* presids, unsigned int n, vec2* poses, unsigned int eid)
{
unsigned int index = 0; // some hash function to get where the eid is in the big...
}

void PressedUpdate(PressableArray pa, EntityQueue eq, GLFWwindow* window)
{
double x, y;
int wid, hig;
glfwGetCursorPos(window, &x, &y);
glfwGetWindowSize(window, &wid, &hig);
vec2 point = GetMousePositionRelative((vec2){x, y}, wid, hig);

for (int i = 0; i < eq.tail; i++)
    {
    for (int j = 0; j < pa.size; j++)
        {
        if(eq.data[i].id == pa.eids[j])
            if(PointInSquare(point, eq.data[i].pos, eq.data[i].scale))
                printf("\nPressed!");
        }
    }


}

