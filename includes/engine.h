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
    Image img;
    Texture tex;
    float scale;
    float rotx;
    float roty;
    float rotz;
};

struct LoadedData{
    char ModelPath[1000];
    char TexturePath[1000];
};

void InitEngine(struct Enginedata *engineData);
void GameLoop(struct Enginedata *engineData , struct LoadedData *loadedData);
void UpdateModels(struct Enginedata *engineData, const char *path);
void UpdateTextures(struct Enginedata *engineData, const char *path);
void LoadTerrain(struct Enginedata *engineData, const char *path);


void AutoRotate(struct Enginedata *engineData ,  float angle);

#endif