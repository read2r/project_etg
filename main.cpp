#include "raylib.h"

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;
    const char* windowTitle = "Project_ETG";
    InitWindow(windowWidth, windowHeight, windowTitle);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}