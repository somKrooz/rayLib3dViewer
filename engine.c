#define RAYGUI_IMPLEMENTATION
#include <engine.h>
#include <loader.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <raygui.h>
#include <raymath.h>

bool isRender = false;
bool HideGui = false;
int frameCount = 0;
int maxRender = 180;

void InitEngine(struct Renderer *renderer, struct Loader *loader) {
    
    InitWindow(WIDTH, HEIGHT, "Viewer");
    SetTargetFPS(60);
    if (renderer == NULL) {
        printf("Bad params Renderer");
        return;
    }
    if (loader == NULL) {
        printf("Bad params Loader");
        return;
    }

    renderer->camera = (Camera *)malloc(sizeof(Camera));
    if (renderer->camera == NULL) {
        printf("Bad params Camera");
        return;
    }
    renderer->camera->position = (Vector3){0.0f, 10.0f, 10.0f};
    renderer->camera->target = (Vector3){0.0f, 0.0f, 0.0f};
    renderer->camera->up = (Vector3){0.0f, 1.0f, 0.0f};
    renderer->camera->fovy = 60.0f;
    renderer->camera->projection = CAMERA_PERSPECTIVE;
    

    strcpy(loader->path, "./assets/Box.obj");
    sLoadModel(loader);

}

void GameLoop(struct Renderer *renderer, struct Loader *loader) {
    renderer->isActive = false;
    loader->scale = 1.0f;

    while (!WindowShouldClose()) 
    {
        // Key Bindings
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            UpdateCamera(renderer->camera, CAMERA_ORTHOGRAPHIC);
        }

        if (IsFileDropped())
        {
            FilePathList file = LoadDroppedFiles();
            if (file.count == 1)
            {
                if (IsFileExtension(file.paths[0], ".obj") || IsFileExtension(file.paths[0], ".gltf"))
                {   
                    strcpy(loader->path, file.paths[0]);
                    sLoadModel(loader);
                }
                else if (IsFileExtension(file.paths[0], ".png") || IsFileExtension(file.paths[0], ".jpg"))
                {
                    strcpy(loader->path, file.paths[0]);
                    sLoadTexture(loader);
                }
            }
            UnloadDroppedFiles(file);
        }

        BeginDrawing();
        ClearBackground((Color){20, 20, 20});

        BeginMode3D(*renderer->camera);
        DrawModel(loader->model, (Vector3){0.0f, 0.0f, 0.0f}, loader->scale, WHITE);

        if (!isRender)
        {
            DrawGrid(10, 1.0f);
        }
        EndMode3D();

        if (!isRender && !HideGui)
        {
            int Render = GuiButton((Rectangle){10.f, 10.0f, 100.f, 20.0f}, "Render");
            GuiToggle((Rectangle){10.f, 30.0f, 100.f, 20.0f}, "AutoRot", &renderer->isActive);
            GuiSlider((Rectangle){10.f, 60.0f, 120.f, 20.0f}, "", "scale", &loader->scale, 0.1, 10);

            // Handle Buttons
            if (Render == 1) 
            {   
                HideGui = true;
                sleep(0.5);
                isRender = true;
            }
            if (renderer->isActive)
            {
                sRotateModel(loader);
            }            
        }

        EndDrawing();

        if (isRender)
        {
            sRotateModel(loader);
            Image screenshot = LoadImageFromScreen(); 
            ExportImage(screenshot, TextFormat("./render/Frame_%d.png", frameCount));
            frameCount++; 
            UnloadImage(screenshot); 

            if (frameCount >= maxRender) 
            {
                system("python utils/convert.py");
                system("python utils/preview.py");
                system("python utils/remove.py");
                frameCount = 0;
                isRender = false;
                HideGui = false;
                loader->model.transform = MatrixRotateXYZ((Vector3){0.0f, 0.0f, 0.0f});
                loader->rotation = (Vector3){0.0f, 0.0f, 0.0f};
            }
        }
    }
    free(renderer->camera);
    UnloadModel(loader->model);
}