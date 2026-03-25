#include "raylib.h"
#include "core/apps.h"
#include "ui/theme.h"
#include <stdio.h>

int main(void) {
    App apps[MAX_APPS];
    int count = apps_load(apps, MAX_APPS);
    Theme theme;

    int err = theme_load(&theme, "../themes/base.ini");
    if (err) {
        printf("Failed theme loading!\n");
        return 1;
    }


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
