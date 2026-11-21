#include <cstdio>
#include <raylib.h>
using vec2 = Vector2;
template <size_t W, size_t H>

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;

    Color myColor = {0, 255, 255, 255};

    InitWindow(screenWidth, screenHeight, "Cellular Automata");
    SetTargetFPS(60);
    bool grid[20][20]{};
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        vec2 mouse = GetMousePosition();
        for(int i(0); i < 20; i++){
            for(int j(0); j < 20; j++){
                if((i+j)%2==0){
                    myColor = {0, 0, 0, 255};
                } else {myColor = {255, 255, 255, 255};}
                if(mouse.x > i*25 && mouse.y > j*25 && mouse.x < (i+1)*25 && mouse.y < (j+1)*25){
                    myColor = {0, 255, 0, 255};
                }
                if(mouse.x > i*25 && mouse.y > j*25 && mouse.x < (i+1)*25 && mouse.y < (j+1)*25 && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    grid[i][j] = true;
                }
                if(mouse.x > i*25 && mouse.y > j*25 && mouse.x < (i+1)*25 && mouse.y < (j+1)*25 && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                    grid[i][j] = false;
                }
                if(grid[i][j]) {
                    myColor = {255, 0, 0, 255};
                }
                DrawRectangle(i*25, j*25, 25, 25, myColor);
                DrawRectangleLines(i*25, j*25, 25, 25, BLACK);
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
