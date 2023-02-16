#include "raylib.h"
#include "rlgl.h"
#include <emscripten/emscripten.h>


void UpdateDrawFrame();

Camera camera = { 0 };
const int screenWidth = 800;
const int screenHeight = 450;
Model model = {0}; 
Vector3 position = { 0.0f, 0.0f, 0.0f };    

int main(void)
{


    InitWindow(screenWidth, screenHeight, "Maria");

      
    camera.position = (Vector3){ 0.0f, 0.0f, -17.0 }; 
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };     
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 60.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;                   

    //Model model = LoadModel("resources/models/castle.obj");                 // Load model
    //Texture2D texture = LoadTexture("resources/models/castle.png"); // Load model texture
                   // Load model
    model = LoadModel("resources/models/body_empty.iqm");  
    Texture2D texture = LoadTexture("resources/models/Base_texture.png");    
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture

                    

    SetTargetFPS(60);


    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);




    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateDrawFrame()
{
        //UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        //UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        //UpdateCamera(&camera, CAMERA_ORBITAL);
        UpdateCamera(&camera, CAMERA_FREE);
        camera.position = (Vector3){ 0.0f, 0.0f, -17.0f}; 
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };  
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                rlPushMatrix();
                rlRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.75f, 1.75f, 1.75f }, WHITE);
                rlPopMatrix();                
                DrawGrid(20, 10.0f);
            EndMode3D();
            
            DrawText(TextFormat("Camera x:%f y:%f z: %f", camera.position.x, camera.position.y, camera.position.z), 10, GetScreenHeight() - 20, 10, DARKGRAY);
            DrawText(TextFormat("Target x:%f y:%f z:%f", camera.target.x, camera.target.y, camera.target.z), screenWidth - 200, screenHeight - 20, 10, GRAY);
            //DrawFPS(10, 10);

        EndDrawing();
}