#include <stdlib.h>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <emscripten/emscripten.h>
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define GLSL_VERSION            100

RenderTexture2D convertRGBATexture2Map(Image encodedMap, bool flipTexture, RenderTexture2D decodedMapResult);
void UpdateDrawFrame();

Camera camera = { 0 };
const int screenWidth = 800;
const int screenHeight = 450;
Model model = {0}; 
Vector3 position = { 0.0f, 0.0f, 0.0f };    
Shader lightingShader;
Shader warpShader;
Texture2D map;

int main(void)
{
    //InitWindow(screenWidth, screenHeight, "Maria");     
    TraceLog(LOG_INFO, "Maria screen size:%d x %d", screenWidth, screenHeight);
    //emscripten_run_script("alert('hi')");
    int x = EM_ASM_INT({
     return window.screen.width;
     });
    int y = EM_ASM_INT({
     return window.screen.height;
     });     
    TraceLog(LOG_INFO, "x screen width from emscriptem: %d", x);
    TraceLog(LOG_INFO, "y screen width from emscriptem: %d", y);
    InitWindow(x, y, "Maria");
    ToggleFullscreen();

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

    Shader lightingShader = LoadShader(TextFormat("resources/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));                   

    // Get some required shader locations
    lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightingShader, "viewPos");
    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(lightingShader, "ambient");
    SetShaderValue(lightingShader, ambientLoc, (float[4]){ 2.5f, 2.5f, 2.5f, 1.0f }, SHADER_UNIFORM_VEC4);
    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };

    if (GLSL_VERSION == 330) {
        lights[0] = CreateLight(LIGHT_POINT, (Vector3){ 0, 0, -50 }, Vector3Zero(), WHITE, lightingShader);
    }
    else {
        lights[0] = CreateLight(LIGHT_POINT, (Vector3){ 0, 0, 50 }, Vector3Zero(), WHITE, lightingShader);
    }

    model.materials[0].shader = lightingShader;
    

    Image mapTex = LoadImage("resources/maps/IpadProDistortionCalibrationMap.png");   // Load model texture (diffuse map)
    RenderTexture2D decodedTex = LoadRenderTexture(mapTex.width, mapTex.height);
    decodedTex = convertRGBATexture2Map(mapTex, true, decodedTex);
    map = decodedTex.texture;

    // Load postprocessing shader    
    warpShader = LoadShader(TextFormat("resources/shaders/glsl%i/warp.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl%i/warp.fs", GLSL_VERSION));    

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
            //ClearBackground(RAYWHITE);
            ClearBackground(BLACK);
            BeginMode3D(camera);
                rlPushMatrix();
                rlRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                //DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.75f, 1.75f, 1.75f }, WHITE);
                DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.75f, 1.75f, 1.75f }, WHITE);
                rlPopMatrix();                
                //DrawGrid(20, 10.0f);
            EndMode3D();
            
            //DrawText(TextFormat("Camera x:%f y:%f z: %f", camera.position.x, camera.position.y, camera.position.z), 10, GetScreenHeight() - 20, 10, DARKGRAY);
            //DrawText(TextFormat("Target x:%f y:%f z:%f", camera.target.x, camera.target.y, camera.target.z), screenWidth - 200, screenHeight - 20, 10, GRAY);
            //DrawFPS(10, 10);

        EndDrawing();
}

RenderTexture2D convertRGBATexture2Map(Image encodedMap, bool flipTexture, RenderTexture2D decodedMapResult){

        float mapDiv = 4095;
        Color *encodedColor32 = LoadImageColors(encodedMap);
        int arraySize = encodedMap.width * encodedMap.height;
        static Color* mapColor;
        mapColor = malloc(arraySize * sizeof(Color));
        Color ec;
        Vector4 tempColor;

        int LOAD_TEX_COLOR_BIT_DEPTH = 8;
        for (int pixel = 0; pixel < (encodedMap.width * encodedMap.height); ++pixel) {
            ec = encodedColor32[pixel];

            tempColor.x = ((ec.r << LOAD_TEX_COLOR_BIT_DEPTH) + ec.g) / mapDiv;
            tempColor.y = ((ec.b << LOAD_TEX_COLOR_BIT_DEPTH) + ec.a) / mapDiv;
         
            if (flipTexture) {
                tempColor.y = 1.0 - tempColor.y;
            }

            tempColor.w = 0.0;
            tempColor.z = 0.0;
            //takes format x y z w
            mapColor[pixel] = ColorFromNormalized(tempColor);
        }
        

        UpdateTexture(decodedMapResult.texture, mapColor);
        UnloadImageColors(encodedColor32);
        return decodedMapResult;
}