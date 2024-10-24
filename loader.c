#include "engine.h"
#include "string.h"
#include  "raylib.h"

void UpdateModels(struct Enginedata *engineData  , const char *path){
    UnloadModel(engineData->model);
    engineData->model = LoadModel(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex;
}

void LoadTerrain(struct Enginedata *engineData  , const char *path){
    UnloadModel(engineData->model);
    engineData->img = LoadImage(path);
    Mesh mesh = GenMeshHeightmap(engineData->img , (Vector3){5,1,5});
    engineData->model = LoadModelFromMesh(mesh);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex;
}

void UpdateTextures(struct Enginedata *engineData, const char *path){
    UnloadTexture(engineData->tex);
    engineData->tex  = LoadTexture(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex; 
}


