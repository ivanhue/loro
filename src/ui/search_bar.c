#include "raylib.h"
#include "ui/theme.h"
#include <stdio.h>

void update_search_bar(Theme* theme, char* value, int* frames, int* letterCount, int* currentFrame) {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125)) {
            value[*letterCount] = (char)key;
            value[*letterCount+1]='\0';
            (*letterCount)++;
        }
        printf("key pressed: %c | value: %s\n", key, value);
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentFrame = *frames;
        (*letterCount)--;
        if ((*letterCount)<0) (*letterCount) = 0;
        value[*letterCount] = '\0';
    }
    if (IsKeyDown(KEY_BACKSPACE)) {
        if (*frames - *currentFrame >= 20) {
            (*letterCount)--;
            if ((*letterCount)<0) (*letterCount) = 0;
            value[*letterCount] = '\0';
        }
    }
}

void draw_search_bar(Theme* theme, char* value, int* frames, int* letterCount) {
    Rectangle textBox = { (int)theme->padding/2, (int)theme->padding/2, theme->width-theme->padding, theme->fontSize+5 };
    DrawLine(10, 36, 780, 36, theme->fg);
    DrawText(value, (int)textBox.x, (int)textBox.y, theme->fontSize, theme->fg);
    int key = GetKeyPressed();
    if ((*frames/20)%2 == 0 && !(key>=32 && key<=125)) {
        DrawText(
            "_",
            (int)textBox.x+5+MeasureText(value, theme->fontSize),
            (int)textBox.y+2,
            theme->fontSize,
            theme->fg
        );
    }
}
