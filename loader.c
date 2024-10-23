#include "engine.h"
#include  "raylib.h"

void UpdateModels(struct Enginedata *engineData  , const char *path){
    UnloadModel(engineData->model);
    engineData->model = LoadModel(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex;
}

void UpdateTextures(struct Enginedata *engineData, const char *path){
    UnloadTexture(engineData->tex);
    engineData->tex  = LoadTexture(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex; 
}


