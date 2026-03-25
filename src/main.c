#include "raylib.h"
#include "core/apps.h"
#include "ui/theme.h"

int main(void) {
    App apps[MAX_APPS];
    int count = apps_load(apps, MAX_APPS);
    Theme theme;

    theme_load(&theme, "themes/base.ini");


    InitWindow(800, 450, "Loro Launcher");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Apps found: %d", count), 10, 10, 20, DARKGRAY);
            for (int i=0; i<count && i<20; i++) {
                DrawText(apps[i].name, 10,40+i*20, 16, DARKGRAY);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
