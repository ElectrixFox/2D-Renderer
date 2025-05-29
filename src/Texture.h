#pragma once
#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>

unsigned int getActiveTexture(unsigned int texture);
unsigned int getTexture(unsigned int texture);

unsigned int CreateTexture(const char* path);

void BindTexture(unsigned int texture);