#include "raylib.h"
#include "rlgl.h"
#include <emscripten/emscripten.h>

#define STRIPES_COUNT 10

void UpdateDrawFrame();


RenderTexture2D target;
Color colors[2] = { (Color) {255,0,0,255},  (Color) {0,255,0,255}};

int width;
int height;

int main(void)
{
    width = EM_ASM_INT({
     return window.screen.width;
     });
    height = EM_ASM_INT({
     return window.screen.height;
     });     
    TraceLog(LOG_INFO, "x screen width from emscriptem: %d", width);
    TraceLog(LOG_INFO, "y screen width from emscriptem: %d", height);
    InitWindow(width, height, "Stripes");
    ToggleFullscreen();
            
    SetTargetFPS(60);
    
    target = LoadRenderTexture(width, height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);




    // De-Initialization
    //--------------------------------------------------------------------------------------
       // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateDrawFrame()
{ 
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);  // Clear render texture background color
            for (int i = 0; i < STRIPES_COUNT; i++) {
                //Horizonatal Stripes
                //DrawRectangle(0, (height/STRIPES_COUNT)*i, width, height/STRIPES_COUNT, colors[i%2]);
                
                //Vertical stripes
                DrawRectangle((width/STRIPES_COUNT)*i,0, width/STRIPES_COUNT, height, colors[i%2]);
            }
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);     // Clear screen background

            // Draw render texture to screen, properly scaled
            DrawTexture(target.texture, 0, 0, WHITE);        
        EndDrawing();
}