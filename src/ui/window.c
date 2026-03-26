#include "ui/theme.h"
#include "raylib.h"
// #include "core/apps.h"
#include "ui/window.h"
#include <string.h>

int calculateSpace(Theme theme, char* type) {
    if (strcmp(type, "header")) {
        return theme.fontSize+theme.verticalSpacing;
    } else if (strcmp(type, "app")) {
        return theme.fontSize-2+theme.verticalSpacing;
    }

    return -1;
}

void draw_window(Theme* theme, App *apps, int count, int max) {
    ClearBackground(theme->bg);

    for (int i=0; i<count && i<max; i++) {
        DrawTextEx(
            theme->font,
            apps[i].name,
            // x = offset, y = spacing within rows
            (Vector2){theme->padding, theme->padding+(calculateSpace(*theme, "header"))+i*(calculateSpace(*theme, "app"))},
            theme->fontSize-2,
            // Spacing within words
            theme->horizontalSpacing,
            theme->fg
        );
    }
}
