#include <raylib.h>
#include <string>
using namespace std;
using vec2 = Vector2;


const int GridX = 20;
const int GridY = 20;

int close(bool arr[GridX][GridY], int cordX, int cordY){
    int c = 0;
    for(int i(-1); i < 2; i++){
        for(int j(-1); j < 2; j++){
            if(j == 0 && i == 0){
                continue;
            }
            if(cordX+i >=0 && cordY + j>=0 &&
                cordX+i < GridX && cordY+j < GridY){
                if(arr[cordX+i][cordY+j]){c++;}
            }
        }
    }
    return c;
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;

    string temp;
    Color myColor = {0, 255, 255, 255};

    InitWindow(screenWidth, screenHeight, "Cellular Automata");
    SetTargetFPS(60);
    bool grid[GridX][GridY]{};
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
                temp = to_string(close(grid, i, j));
                DrawRectangle(i*25, j*25, 25, 25, myColor);
                DrawRectangleLines(i*25, j*25, 25, 25, BLACK);
                DrawText(temp.c_str(), i*25, j*25, 15, WHITE);
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
