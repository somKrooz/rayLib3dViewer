#ifndef RENDERER_H
#define RENDERER_H
#include <raylib.h>
#include <loader.h>

#define WIDTH 900
#define HEIGHT 600

struct Renderer
{
    Camera *camera;
    Model model;
    Texture tex;  
    bool isActive; 
};

void InitEngine(struct Renderer *renderer,struct Loader *loader);
void GameLoop(struct Renderer *renderer , struct Loader *loader);


#endif