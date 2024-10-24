#include "engine.h"
#include "string.h"
#include  "raylib.h"
#include "raymath.h"

void UpdateModels(struct Enginedata *engineData  , const char *path){
    UnloadModel(engineData->model);
    engineData->model = LoadModel(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex;
}

void AutoRotate(struct Enginedata *engineData , float Speed){
    engineData->roty += Speed;
    engineData->model.transform = MatrixRotateXYZ((Vector3){0,RAD2DEG*engineData->roty, 0});
}


void LoadTerrain(struct Enginedata *engineData  , const char *path){
    UnloadModel(engineData->model);
    engineData->img = LoadImage(path);
    Mesh mesh = GenMeshHeightmap(engineData->img , (Vector3){5,.5,5});
    engineData->model = LoadModelFromMesh(mesh);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex;
}

void UpdateTextures(struct Enginedata *engineData, const char *path){
    UnloadTexture(engineData->tex);
    engineData->tex  = LoadTexture(path);
    engineData->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = engineData->tex; 
}


