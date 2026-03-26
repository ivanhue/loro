#include "raylib.h"
#include "ui/theme.h"
#include <stdio.h>
#include <string.h>

static void joinText(char s[127][4], int length, char *dest) {
    dest[0] = '\0';
    for (int i=0; i<length; i++) {
        strcat(dest, s[i]);
    }
}

void update_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, int* currentFrame) {
    int key = GetCharPressed();
    while (key > 0) {
        int byteCount = 2;
        const char *utf8 = CodepointToUTF8(key, &byteCount);
        if ((key >= 32) && (key <= 255)) {
            strcpy(value[*letterCount], utf8);
            (*letterCount)++;
        }
        printf("key pressed: %c | utf8: %s | value: %s\n", key, utf8, value[*letterCount]);
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentFrame = *frames;
        (*letterCount)--;
        if ((*letterCount)<0) (*letterCount) = 0;
        strcpy(value[*letterCount], "\0");
    }
    if (IsKeyDown(KEY_BACKSPACE)) {
        if (*frames - *currentFrame >= 20) {
            (*letterCount)--;
            if ((*letterCount)<0) (*letterCount) = 0;
            strcpy(value[*letterCount], "\0");
        }
    }
}

void draw_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, char utf8String[127*4]) {
    joinText(value, *letterCount, utf8String);
    Rectangle textBox = { (int)theme->padding/2, (int)theme->padding/2, theme->width-theme->padding, theme->fontSize+5 };
    DrawLine(10, 36, 780, 36, theme->fg);
    Vector2 tmp = {textBox.x, textBox.y};
    DrawTextEx(theme->font, utf8String, tmp, theme->fontSize, theme->horizontalSpacing, theme->fg);
    int key = GetKeyPressed();
    if ((*frames/20)%2 == 0 && !(key>=32 && key<=125)) {
        DrawText(
            "_",
            (int)textBox.x+5+MeasureText(utf8String, theme->fontSize),
            (int)textBox.y+2,
            theme->fontSize,
            theme->fg
        );
    }
}
