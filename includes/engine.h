#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"  

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define min_scale 1
#define max_scale 10


struct Enginedata
{
    Camera3D *camera;
    Model model;
    Texture tex;
    float scale;
    float rotx;
    float roty;
    float rotz;
};

void InitEngine(struct Enginedata *engineData);
void GameLoop(struct Enginedata *engineData);
void UpdateModels(struct Enginedata *engineData, const char *path);
void UpdateTextures(struct Enginedata *engineData, const char *path);

#endif