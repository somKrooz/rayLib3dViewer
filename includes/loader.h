#ifndef LOADER_H
#define LOADER_H
#include <raylib.h>

struct Loader
{   
    char path[300];
    Model model;
    Texture tex;
    float scale;
    Vector3 rotation;
};

void sLoadModel(struct Loader *loader);
void sRotateModel(struct Loader *loader);
void sLoadTexture(struct Loader *loader);

#endif