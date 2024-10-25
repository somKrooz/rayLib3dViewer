#include "loader.h"
#include "raymath.h"
#include "raylib.h"
#include "string.h"

void sLoadModel(struct Loader *loader)
{
    if(loader->model.meshCount == 0) UnloadModel(loader->model);
    loader->model = LoadModel(loader->path);
    if(loader->tex.id >=0)
    {
        strcpy(loader->path , "./assets/uv_shader.png");
        loader->tex = LoadTexture(loader->path);
    }
    loader->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = loader->tex;
}

void sRotateModel(struct Loader *loader)
{
    loader->rotation.y += 2.0f;
    loader->model.transform = MatrixScale(10.0f,0.0f,0.0f); 
    loader->model.transform = MatrixRotateXYZ((Vector3){0.0f ,DEG2RAD*loader->rotation.y,0.0f});
}

void sLoadTexture(struct Loader *loader)
{
    if(loader->tex.id <0) UnloadTexture(loader->tex);
    loader->tex = LoadTexture(loader->path);
    loader->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = loader->tex; 
}
