/*******************************************************************************************
*
*   raylib [models] example - Models loading
*
*   NOTE: raylib supports multiple models file formats:
*
*     - OBJ  > Text file format. Must include vertex position-texcoords-normals information,
*              if files references some .mtl materials file, it will be loaded (or try to).
*     - GLTF > Text/binary file format. Includes lot of information and it could
*              also reference external files, raylib will try loading mesh and materials data.
*     - IQM  > Binary file format. Includes mesh vertex data but also animation data,
*              raylib can load .iqm animations.
*     - VOX  > Binary file format. MagikaVoxel mesh format:
*              https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
*     - M3D  > Binary file format. Model 3D format:
*              https://bztsrc.gitlab.io/model3d
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Maria");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };    
    camera.position = (Vector3){ 36.334663, 56.054199, -2.222321}; 
    camera.target = (Vector3){ 4.325600, -14.786743, 32.85185 }; 
    //camera.position = (Vector3){ 0.0f, 10.0f, 17.0f }; 
    //camera.target = (Vector3){ -10.0f, 20.0f, 0.0f };    
    //camera.position = (Vector3){ 20.0f, 30.0f, -60.0f }; // Camera position
    //camera.target = (Vector3){ 0.0f, 0.0f, 60.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 v0 = {0.0f, 0.0f, 0.0f};
    Vector3 v1 = {0.0f, 30.0f, 0.0f};
    Vector3 v2 = {0.0f, 0.0f, 30.0f};
    Vector3 v3 = {30.0f, 0.0f, 0.0f};

    //Model model = LoadModel("resources/models/castle.obj");                 // Load model
    //Texture2D texture = LoadTexture("resources/models/castle.png"); // Load model texture
    //Model model = LoadModel("resources/models/body_empty.iqm");                 // Load model
    //Texture2D texture = LoadTexture("resources/models/Base_texture.png");    
    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture

    //Vector3 position = { 0.0f, 0.0f, 0.0f };                    // Set model position

  
    //BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    //bool selected = false;          // Selected object flag

    DisableCursor();                // Limit cursor to relative movement inside the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        

        // Update
        //----------------------------------------------------------------------------------
        //Mohan: Uncomment this when you need to know camera position and target
        //UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        //UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        // Load new models/textures on drag&drop
        /*
        if (IsFileDropped())
        {
            FilePathList droppedFiles = LoadDroppedFiles();

            if (droppedFiles.count == 1) // Only support one file dropped
            {
                if (IsFileExtension(droppedFiles.paths[0], ".obj") ||
                    IsFileExtension(droppedFiles.paths[0], ".gltf") ||
                    IsFileExtension(droppedFiles.paths[0], ".glb") ||
                    IsFileExtension(droppedFiles.paths[0], ".vox") ||
                    IsFileExtension(droppedFiles.paths[0], ".iqm") ||
                    IsFileExtension(droppedFiles.paths[0], ".m3d"))       // Model file formats supported
                {
                    UnloadModel(model);                         // Unload previous model
                    model = LoadModel(droppedFiles.paths[0]);   // Load new model
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                    bounds = GetMeshBoundingBox(model.meshes[0]);

                    // TODO: Move camera position from target enough distance to visualize model properly
                }
                else if (IsFileExtension(droppedFiles.paths[0], ".png"))  // Texture file formats supported
                {
                    // Unload current model texture and load new one
                    UnloadTexture(texture);
                    texture = LoadTexture(droppedFiles.paths[0]);
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
                }
            }

            UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }
        */

        /*
        // Select model on mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Check collision between ray and box
            if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), bounds).hit) selected = !selected;
            else selected = false;
        }
        //----------------------------------------------------------------------------------
        */


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawLine3D(v0, v1, RED);
                DrawLine3D(v0, v2, BLUE);
                DrawLine3D(v0, v3, GREEN);
                //DrawModel(model, position, 1.0f, WHITE);        // Draw 3d model with texture
                
                DrawGrid(20, 10.0f);         // Draw a grid

                //if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

            EndMode3D();
            
            DrawText(TextFormat("Camera x:%f y:%f z: %f", camera.position.x, camera.position.y, camera.position.z), 10, GetScreenHeight() - 20, 10, DARKGRAY);
            //if (selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

            DrawText(TextFormat("Target x:%f y:%f z:%f", camera.target.x, camera.target.y, camera.target.z), screenWidth - 240, screenHeight - 20, 10, GRAY);

            //DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadTexture(texture);     // Unload texture
    //UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}