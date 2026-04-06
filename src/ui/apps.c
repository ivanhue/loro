#include "raylib.h"
#include "ui/theme.h"
#include "core/apps.h"
#include <string.h>
#include <stdio.h>

static int calculateSpace(Theme theme, char* type) {
    if (strcmp(type, "header")) {
        return theme.fontSize+theme.verticalSpacing;
    } else if (strcmp(type, "app")) {
        return theme.fontSize-2+theme.verticalSpacing;
    }

    return -1;
}

static Vector2 get_app_position(Theme* theme, int index) {
    return (Vector2){
        theme->padding,
        theme->padding+(calculateSpace(*theme, "header"))+index*(calculateSpace(*theme, "app"))
    };
}

void draw_apps_list(Theme* theme, App *apps, int count, int max) {
    for (int i=0; i<count && i<max; i++) {
        DrawTextEx(
            theme->font,
            apps[i].name,
            get_app_position(theme, i),
            theme->fontSize-2,
            // Spacing within words
            theme->horizontalSpacing,
            theme->fg
        );
    }
}

void draw_hover(Theme* theme, int index) {
    Vector2 appCoordinates = get_app_position(theme, index);
    Rectangle app = {appCoordinates.x-4, appCoordinates.y-4, theme->width-2*theme->padding, theme->fontSize+4};
    DrawRectangleLinesEx(app, 2.0, theme->fg);
}

void draw_navigation(Theme* theme, App *currentApps, int* cursor) {
    if (IsKeyPressed(KEY_UP)) {
        *cursor= *cursor - 1;
        if (*cursor<0) {
            *cursor = 0;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        *cursor = *cursor + 1;
        if (*cursor>9) {
            *cursor = 9;
        }
    }
    draw_hover(theme, *cursor);
}

void open_selected_app(App *currentApps, int* cursor) {
    if (IsKeyPressed(KEY_ENTER)) {
        int index = *cursor;
        launch(&currentApps[index]);
    }
}
