#include "Shader.h"

/*
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"*/

unsigned int createShader(const char* vertsrc, const char* fragsrc)
{
char errmsg[512];
int success;

unsigned int vertshad;
vertshad = glCreateShader(GL_VERTEX_SHADER);    // creating the shader
glShaderSource(vertshad, 1, &vertsrc, NULL);    // sets the source of the shader
glCompileShader(vertshad);  // compiles the shader

glGetShaderiv(vertshad, GL_COMPILE_STATUS, &success);
if (!success)
    {
    glGetShaderInfoLog(vertshad, 512, NULL, errmsg);
    printf("ERROR: Vertex Shader %s", errmsg);
    }

/*
do error management here
*/

unsigned int fragshad;
fragshad = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragshad, 1, &fragsrc, NULL);
glCompileShader(fragshad);

/*
do error management here
*/
glGetShaderiv(fragshad, GL_COMPILE_STATUS, &success);
if (!success)
    {
    glGetShaderInfoLog(fragshad, 512, NULL, errmsg);
    printf("ERROR: Fragment Shader %s", errmsg);
    }

unsigned int program;   // the program linking both shaders
program = glCreateProgram();
glAttachShader(program, vertshad);
glAttachShader(program, fragshad);
glLinkProgram(program);

glGetProgramiv(program, GL_LINK_STATUS, &success);
if (!success)
    {
    glGetProgramInfoLog(program, 512, NULL, errmsg);
    printf("ERROR: %s", errmsg);
    }
/*
do error checking here
*/

glUseProgram(program);  // actually using the shaders for all future objects

glDeleteShader(vertshad);   // delete the unnecessary shaders
glDeleteShader(fragshad);

return program;
}

void BindShader(unsigned int program)
{
glUseProgram(program);  // binds the shader program
}

unsigned int createTexture(const char* path)
{
unsigned int texture;
glGenTextures(1, &texture);   // generates a texture
glBindTexture(GL_TEXTURE_2D, texture);   // binds the texture

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // sets the texture wrapping
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);   // sets the texture filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

int width, height, nrChannels;
/*
unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);   // loads the texture
if (!data)  // if the texture is not loaded
    {
    printf("ERROR: Failed to load texture\n");
    stbi_image_free(data);
    return -1;
    }
    
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   // generates the texture
glGenerateMipmap(GL_TEXTURE_2D);   // generates the mipmap
stbi_image_free(data);   // frees the data
*/

return texture;
}

void BindTexture(unsigned int texture)
{
glBindTexture(GL_TEXTURE_2D, texture);   // binds the texture
}

void SetUniform1f(unsigned int program, const char* varname, float value)
{
int uniloc = glGetUniformLocation(program, varname);
BindShader(program);
glUniform1f(uniloc, value);
}

void SetUniformM4(unsigned int program, const char* varname, m4 matr)
{
int uniloc = glGetUniformLocation(program, varname);
BindShader(program);
glUniformMatrix4fv(uniloc, 1, GL_FALSE, &matr.mat[0][0]);
}

void SetUniform1i(unsigned int program, const char* varname, unsigned int value)
{
int uniloc = glGetUniformLocation(program, varname);
BindShader(program);
glUniform1i(uniloc, value);
}