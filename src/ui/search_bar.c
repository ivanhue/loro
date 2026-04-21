#include "raylib.h"
#include "ui/theme.h"
#include "core/apps.h"
#include <string.h>

static void joinText(char s[127][4], int length, char *dest) {
    dest[0] = '\0';
    for (int i=0; i<length; i++) {
        strcat(dest, s[i]);
    }
}

void update_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, int* currentFrame, const App *totalApps, App *currentApps, int totalCount, int* currentCount, int max_out, int* cursor) {
    bool changed = false;
    int key = GetCharPressed();

    while (key > 0) {
        if (*letterCount < 126 && key >= 32 && key <= 255) {
            int byteCount = 0;
            const char *utf8 = CodepointToUTF8(key, &byteCount);
            strcpy(value[*letterCount], utf8);
            (*letterCount)++;
            changed = true;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (*letterCount > 0) {
            (*letterCount)--;
            strcpy(value[*letterCount], "\0");
            *currentFrame = *frames;
            changed = true;
        }
    }
    else if (IsKeyDown(KEY_BACKSPACE)) {
        if ((*frames - *currentFrame) >= 20 && *letterCount > 0) {
            (*letterCount)--;
            strcpy(value[*letterCount], "\0");
            changed = true;
        }
    }

    if (changed) {
        (*cursor) = 0;
        char fullString[127 * 4] = {0};
        joinText(value, *letterCount, fullString);
        update_apps_list(totalApps, currentApps, totalCount, currentCount, fullString, max_out);
    }
}

void draw_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, char utf8String[127*4]) {
    joinText(value, *letterCount, utf8String);
    Rectangle textBox = { (int)theme->padding/2, (int)theme->padding/2, theme->width-theme->padding, theme->fontSize+5 };
    DrawLine(10, theme->fontSize+12, 780, theme->fontSize+12, theme->fg);
    Vector2 tmp = {textBox.x, textBox.y};
    DrawTextEx(theme->font, utf8String, tmp, theme->fontSize, theme->horizontalSpacing, theme->fg);
    int key = GetKeyPressed();
    Vector2 textMeasures = MeasureTextEx(theme->font, utf8String, theme->fontSize, theme->horizontalSpacing);
    Vector2 position = {
        (int)textBox.x + 5 + (int)textMeasures.x,
        (int)textBox.y + 2
    };
    if ((*frames/20)%2 == 0) {
        DrawTextEx(
            theme->font,
            "_",
            position,
            theme->fontSize,
            theme->horizontalSpacing,
            theme->fg
        );
    }
}
