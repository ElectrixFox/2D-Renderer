#include <include/GL/glew.h>
#include <include/GLFW/glfw3.h>
#include "src/FileHandling.h"

unsigned int createShader(const char* vertsrc, const char* fragsrc);

void BindShader(unsigned int program);

void SetUniform1f(unsigned int program, const char* varname, float value);