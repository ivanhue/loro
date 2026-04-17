#include <stdio.h>
#include "raylib.h"
// CORE
#include "core/apps.h"
// UI
#include "ui/theme.h"
#include "ui/window.h"
#include "ui/search_bar.h"
#include "ui/apps.h"

int calculate_window_height(Theme* theme, int currentCount) {
    return 10 + (theme->padding * 2) + (currentCount * (theme->fontSize + theme->verticalSpacing));
}

int main(void) {
    Theme theme;
    char *pathApps[32];
    int lenPaths = 0;

    int err = theme_load(&theme, "../themes/base.ini", pathApps, &lenPaths);
    if (err) {
        printf("Failed theme loading!\n");
        return 1;
    }
    App _internalApps[MAX_APPS];
    // printf("lenPaths: %d\n", lenPaths);
    // for (int i = 0; i < lenPaths; i++) {
    //     printf("path[%d]: '%s'\n", i, pathApps[i]);
    // }
    int totalCount = apps_load(_internalApps, MAX_APPS, pathApps, lenPaths);
    const App *totalApps = _internalApps;
    App currentApps[MAX_SHOW_APPS];
    int currentCount = (totalCount > MAX_SHOW_APPS) ? MAX_SHOW_APPS : totalCount;
    // (search bar + apps count total) + (each app)
    int height = calculate_window_height(&theme, currentCount);

    char value[127][4];
    char utf8String[127*4];
    int letterCount = 0;
    int framesCounter = 0;
    int currentFrame = 0;
    int cursor = 0;

    InitWindow(theme.width, height, "Loro Launcher");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    init_current_apps(totalApps, currentApps, totalCount, &currentCount, MAX_SHOW_APPS);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;
        framesCounter++;
        int lastCount = currentCount;
        update_search_bar(&theme, value, &framesCounter, &letterCount, &currentFrame, totalApps, currentApps, totalCount, &currentCount, MAX_SHOW_APPS, &cursor);

        if (currentCount != lastCount) {
            int newHeight = calculate_window_height(&theme, currentCount);

            if (newHeight < 100) newHeight = 100;

            SetWindowSize(theme.width, newHeight);
        }
        open_selected_app(currentApps, &cursor);

        BeginDrawing();
            draw_window(&theme);
            draw_search_bar(&theme, value, &framesCounter, &letterCount, utf8String);
            draw_apps_list(&theme, currentApps, currentCount, MAX_SHOW_APPS);
            draw_navigation(&theme, currentApps, &cursor, &currentCount);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
