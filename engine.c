#include <engine.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include  "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "raymath.h"

float TextToFloat(const char *text){
    return (float)atof(text);
}

void InitEngine(struct Enginedata *engineData) {

    if (engineData == NULL) {
        printf("engineData is NULL!\n");
        return; 
    }

    engineData->camera = (Camera3D*)malloc(sizeof(Camera3D)); 
    if (engineData->camera == NULL) {
        printf("Failed to allocate memory for camera!\n");
        return;
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Model Viewer");
    SetTargetFPS(120);

    engineData->camera->position = (Vector3){ 0.0f, 10.0f, 10.0f };
    engineData->camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    engineData->camera->fovy = 80.0f;
    engineData->camera->projection = CAMERA_PERSPECTIVE;
    engineData->model = LoadModel("assets/Monkey.obj");


}

void GameLoop(struct Enginedata *engineData , struct LoadedData *loadedData) {
    strcpy(loadedData->ModelPath , "default");    
    strcpy(loadedData->TexturePath , "default");    
    while (!WindowShouldClose()) {

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            UpdateCamera(engineData->camera, CAMERA_PERSPECTIVE);
        }
        if (IsFileDropped()){
            FilePathList files = LoadDroppedFiles();
            for(int i=0 ; i<files.count; i++ ){
                if(IsFileExtension(files.paths[i], ".obj")){
                    printf("We Got Obj File");
                    UpdateModels(engineData , files.paths[i]);
                    strcpy(loadedData->ModelPath , files.paths[i]); 
                }
                if(IsFileExtension(files.paths[i], ".png")){
                    printf("We Got Png File");
                    UpdateTextures(engineData , files.paths[i]);
                    strcpy(loadedData->TexturePath , files.paths[i]); 
                }

            }
            UnloadDroppedFiles(files);
        }

        //Rotation
        engineData->model.transform = MatrixRotateXYZ((Vector3){  DEG2RAD*engineData->rotx ,  DEG2RAD*engineData->roty ,  DEG2RAD*engineData->rotz }); 

        BeginDrawing();
        ClearBackground(DARKGRAY);
        //3d Stuff
        BeginMode3D(*engineData->camera);
        DrawModel(engineData->model, (Vector3){ 0.0f, 0.0f, 0.0f },engineData->scale, WHITE);
        EndMode3D();

        //GUI
        GuiSlider((Rectangle){ SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-30, 200, 20 }, "minScale", "maxScale", &engineData->scale, min_scale, max_scale);
        GuiSlider((Rectangle){ SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-60, 200, 20 }, "xMin", "xMax", &engineData->rotx, 0, 360);
        GuiSlider((Rectangle){ SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-80, 200, 20 }, "yMin", "yMax", &engineData->roty, 0, 360);
        GuiSlider((Rectangle){ SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-100, 200, 20 }, "zMin", "zMax", &engineData->rotz, 0, 360);
        GuiStatusBar((Rectangle){SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-300, 300, 30},loadedData->ModelPath);
        GuiStatusBar((Rectangle){SCREEN_WIDTH/2-500, SCREEN_HEIGHT/2-280, 300, 30},loadedData->TexturePath);

        EndDrawing();
    }

    UnloadModel(engineData->model);
    UnloadTexture(engineData->tex);
    free(engineData->camera);

}
