#include "Input.h"

static int ckey = 0;    // current key
static int caction = 0; // current action
static int paction = GLFW_RELEASE;  // previous action
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
return (InputPacket){ckey, paction, caction, cmods};
}

int isPressedSingle(int key)
{
}