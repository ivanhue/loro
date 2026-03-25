#include "raylib.h"
#include "core/apps.h"
#include "ui/theme.h"
#include "ui/window.h"
#include <stdio.h>

int main(void) {
    Theme theme;

    int err = theme_load(&theme, "../themes/base.ini");
    if (err) {
        printf("Failed theme loading!\n");
        return 1;
    }

    App apps[MAX_APPS];
    int count = apps_load(apps, MAX_APPS);

    InitWindow(800, 450, "Loro Launcher");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;

        BeginDrawing();
            draw_window(&theme, apps, count);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
