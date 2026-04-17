#pragma once
#include "raylib.h"

typedef struct {
    Color bg;
    Color fg;
    Color accent;
    Color border;
    Color hover;

    int fontSize;
    int borderRadius;

    int iconSize;

    int horizontalSpacing;
    int verticalSpacing;

    int width;
    int padding;

    Font font;
} Theme;

int theme_load(Theme* theme, char* pathTheme, char **pathApps, int *lenPaths);
