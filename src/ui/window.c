#include "ui/theme.h"
#include "raylib.h"
// #include "core/apps.h"
#include "ui/window.h"

void draw_window(Theme* theme, App *apps, int count) {
    ClearBackground(theme->bg);
    DrawTextEx(
        theme->font,
        TextFormat("Apps found: %d", count),
        (Vector2){theme->horizontalSpacing, 10},
        theme->fontSize,
        2,
        theme->fg
    );
    for (int i=0; i<count && i<20; i++) {
        DrawTextEx(
            theme->font,
            apps[i].name,
            (Vector2){theme->horizontalSpacing, 40+i*theme->verticalSpacing},
            theme->fontSize-2,
            2,
            theme->fg
        );
    }
}
