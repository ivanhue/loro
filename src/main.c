#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
// CORE
#include "core/apps.h"
// UI
#include "ui/theme.h"
#include "ui/window.h"
#include "ui/search_bar.h"
#include "ui/apps.h"

int calculate_window_height(Theme* theme, int currentCount) {
    // padding + search bar + app list + vertical spacing
    return 2*(theme->padding) + (theme->fontSize) +
           (currentCount * theme->fontSize) +
           ((currentCount - 1) * theme->verticalSpacing);
}

int main(void) {
    Theme theme;
    char *pathApps[32];
    int lenPaths = 0;

    char *home = getenv("HOME");
    char configPath[512];
    snprintf(configPath, sizeof(configPath), "%s/.config/loro/config.ini", home);
    int err = theme_load(&theme, configPath, pathApps, &lenPaths);
    if (err) {
        printf("Failed theme loading!\n");
        return 1;
    }
    App _internalApps[MAX_APPS];
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

    theme_load_assets(&theme);

    init_current_apps(totalApps, currentApps, totalCount, &currentCount, MAX_SHOW_APPS);

    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) break;
        framesCounter++;
        int lastCount = currentCount;
        update_search_bar(&theme, value, &framesCounter, &letterCount, &currentFrame, totalApps, currentApps, totalCount, &currentCount, MAX_SHOW_APPS, &cursor);

        if (currentCount != lastCount) {
            int newHeight = calculate_window_height(&theme, currentCount);

            if (newHeight < 80) newHeight = 80;

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

    UnloadFont(theme.font);
    CloseWindow();

    return 0;
}
