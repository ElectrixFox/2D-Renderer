#pragma once
#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>

unsigned int CreateTexture(const char* path);

void BindTexture(unsigned int texture);