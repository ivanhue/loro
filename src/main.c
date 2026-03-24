#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Loro Launcher");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
