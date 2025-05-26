#include "PressableObject.h"

PressableArray InitPressableArray(unsigned int size)
{

}

void AddPressable(PressableArray* pa, unsigned int eid)
{

}

void RemovePressable(PressableArray* pa, unsigned int eid)
{

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

