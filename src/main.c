#include "raylib.h"
#include "core/apps.h"
#include "ui/theme.h"
#include "ui/window.h"
#include "ui/search_bar.h"
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
    // (search bar + apps count total) + (each app)
    int height = 40 + ((2*(theme.fontSize+theme.verticalSpacing))-2 + (MAX_SHOW_APPS*(theme.fontSize-2+theme.verticalSpacing)));

    char value[255];
    int letterCount = 0;
    int framesCounter = 0;
    int currentFrame = 0;

    InitWindow(theme.width, height, "Loro Launcher");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;
        framesCounter++;
        update_search_bar(&theme, value, &framesCounter, &letterCount, &currentFrame);

        BeginDrawing();
            draw_window(&theme, apps, count, MAX_SHOW_APPS);
            draw_search_bar(&theme, value, &framesCounter, &letterCount);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
