#include "Input.h"

static int ckey = 0;    // current key
static int caction = 0; // current action
static int cmods = 0;   // current mod keys

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


ckey = key;
caction = action;
cmods = mods;
}

void InitialiseInput(GLFWwindow *window)
{
glfwSetKeyCallback(window, key_callback);   // setting up the callback
}

InputPacket getCurrentInputInformation()
{
return (InputPacket){ckey, caction, cmods};
}

void resetInputPacket()
{
ckey = -1;
caction = -1;
cmods = -1;
}

int isPressedSingle(int key)
{
static int pkey = 0;
InputPacket ip = getCurrentInputInformation();
if(ip.key == key && pkey != key)
    {
    if(ip.action == GLFW_PRESS)
        {
        pkey = key;
        return 1;
        }
    else if(ip.action == GLFW_RELEASE)
        {
        resetInputPacket();
        pkey = 0;
        return 0;
        }
    }
else if(ip.action == GLFW_RELEASE)
    pkey = 0;
return 0;
}

int isHeldDown(int key)
{
InputPacket ip = getCurrentInputInformation();
if(ip.key == key)
    if(ip.action == GLFW_REPEAT)
        return 1;
return 0;
}