#include <raylib.h>
#include <string>
using namespace std;
using vec2 = Vector2;


const int GridX = 20;
const int GridY = 20;

float DelayPlus(float del){
    float delay = 1/del;
    if(delay == 500){return del;}
    return 1/(delay+1);
}

float DelayMinus(float del){
    float delay = 1/del;
    if(delay == 1){return del;}
    return 1/(delay-1);
}

int close(const bool arr[GridX][GridY], int cordX, int cordY){
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

void newGeneretion(const bool arr[GridX][GridY], bool newGen[GridX][GridY]){
    int h;
    for(int i(0); i < GridX; i++){
        for(int j(0); j < GridY; j++){
            h = close(arr, i, j);
            if(arr[i][j]){
                if(h < 2){
                    newGen[i][j] = false;
                }
                if(h == 2 || h == 3){
                    newGen[i][j] = true;
                }
                if(h > 3){
                    newGen[i][j] = false;
                }
            }else{
                newGen[i][j] = (h == 3);
            }
        }
    }
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;

    string temp;
    Color myColor = {0, 255, 255, 255};
    float timer = 0.0f;
    float GenDeley = 0.2f;
    bool sim = false;

    InitWindow(screenWidth, screenHeight, "Cellular Automata");
    SetTargetFPS(60);
    bool grid[GridX][GridY]{};
    bool nextGrid[GridX][GridY]{};
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
                DrawText(temp.c_str(), i*25+5, j*25+5, 15, {100, 100, 100, 255});
            }
        }
        if(IsKeyPressed(KEY_EQUAL)){
            GenDeley = DelayPlus(GenDeley);
        }
        if(IsKeyPressed(KEY_MINUS)){
            GenDeley = DelayMinus(GenDeley);
        }
        if(IsKeyPressed(KEY_N) && !sim){
            newGeneretion(grid, nextGrid);
            for (int i = 0; i < GridX; i++) {
                for (int j = 0; j < GridY; j++) {
                    grid[i][j] = nextGrid[i][j];
                }
            }
        }
        timer += GetFrameTime();
        if(IsKeyPressed(KEY_SPACE)){sim = !sim;}
        while(timer >= GenDeley){
            if(sim){
                newGeneretion(grid, nextGrid);
                for (int i = 0; i < GridX; i++) {
                    for (int j = 0; j < GridY; j++) {
                        grid[i][j] = nextGrid[i][j];
                    }
                }
            }
            timer -= GenDeley;
        }
        temp = to_string(1/GenDeley);
        DrawText(temp.c_str(), 10, 500, 40, WHITE);
        DrawFPS(510, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
