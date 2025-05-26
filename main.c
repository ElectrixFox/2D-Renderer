#include <stdio.h>
#include <stdlib.h>

#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/Entity.h"

void SetPressable(Entity* pressables, Entity nent, unsigned int* n)
{
pressables[*n] = nent;
(*n)++;
}

void processInput(GLFWwindow* window, Entity e)
{
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    glfwSetWindowShouldClose(window, 1);
    }
if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)  // if the escape key is pressed close the window
    {
    /*double x, y;
    vec2 posy = GetMousePositionRelative(window);
    glfwGetCursorPos(window, &x, &y);
    */
    }
}

void PlaceEntity(EntityQueue* entities, vec2 at)
{
Entity nent = CreateEntity(0, at, "res/vertex.shader", "res/fragment.shader", NULL);
nent.scale = (vec2){10.0f, 10.0f};

EnqueueEntityQueue(entities, nent);
}


int main()
{
unsigned int width = 1020;
unsigned int height = 960;
glfwInit();
// (0, 0) is the top left
GLFWwindow* window = glfwCreateWindow(width, height, "Title", 0, 0); // creates the window of size width x height

glfwMakeContextCurrent(window); // sets the context of the window
glViewport(0, 0, width, height);

glewInit();

Entity ent1 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/texvert.shader", "res/texfrag.shader", "res/wood.png");
ent1.scale = (vec2){100.0f, 100.0f};
ent1.pos = (vec2){1020.0f, 960.0f};
SetUniform4f(ent1.rdets.shader, "colour", (vec4){0.75f, 0.0f, 0.0f, 1.0f});


Entity ent2 = CreateEntity(0, (vec2){0.0f, 0.0f}, "res/vertex.shader", "res/fragment.shader", NULL);
ent2.scale = (vec2){10.0f, 10.0f};
ent2.pos = (vec2){0.0f, 0.0f};
SetUniform4f(ent2.rdets.shader, "colour", (vec4){0.0f, 0.75f, 0.0f, 1.0f});

EntityQueue eq;
eq = InitQueueEntityQueue(10);
EnqueueEntityQueue(&eq, ent1);
EnqueueEntityQueue(&eq, ent2);

while(!glfwWindowShouldClose(window))
    {
    // loop
    processInput(window, eq.data[1]);   // do all the input processing here
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // setting the background colour
    glClear(GL_COLOR_BUFFER_BIT);   // clears colour buffer

    for (int i = 0; i < eq.size; i++)
        {
        DrawEntity(eq.data[i]);
        }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

glfwTerminate();    // cleans up all the glfw objects

return 0;
}
