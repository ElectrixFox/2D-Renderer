#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

unsigned int CreateTexture(const char* path)
{
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

int width, height, nrChannels;
stbi_set_flip_vertically_on_load(1);
unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
if(!data)
    {
    printf("ERROR: Failed to load texture\n");
    stbi_image_free(data);
    return -1;
    }

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);

stbi_image_free(data);

return texture;
}