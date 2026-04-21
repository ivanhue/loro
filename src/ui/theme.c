#include "ui/theme.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int theme_load(Theme* theme, char* pathTheme, char **pathApps, int *lenPaths) {
    FILE *f = fopen(pathTheme, "r");
    if (!f) return 1;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        // TODO: edge cases: empty string, invalid string, etc.
        line[strcspn(line, "\n")] = '\0';
        if (strncmp(line, "bg=", 3) == 0) {
            if (strcmp(line+3, "") == 0) continue;
            unsigned int hexBg = strtoul(line+4, NULL, 16);
            hexBg = (hexBg << 8) | 0xFF;
            Color bgColor = GetColor(hexBg);
            theme->bg=bgColor;
        } else if (strncmp(line, "fg=", 3) == 0) {
            if (strcmp(line+3, "") == 0) continue;
            unsigned int hexFg = strtoul(line+4, NULL, 16);
            hexFg = (hexFg << 8) | 0xFF;
            Color fgColor = GetColor(hexFg);
            theme->fg=fgColor;
        } else if (strncmp(line, "accent=", 7) == 0) {
            if (strcmp(line+7, "") == 0) continue;
            unsigned int hexAccent = strtoul(line+8, NULL, 16);
            Color accentColor = GetColor(hexAccent);
            theme->accent=accentColor;
        } else if (strncmp(line, "border=", 7) == 0) {
            if (strcmp(line+7, "") == 0) continue;
            unsigned int hexBorder = strtoul(line+8, NULL, 16);
            Color borderColor = GetColor(hexBorder);
            theme->border=borderColor;
        } else if (strncmp(line, "hover=", 6) == 0) {
            if (strcmp(line+6, "") == 0) continue;
            unsigned int hexHover = strtoul(line+7, NULL, 16);
            Color hoverColor = GetColor(hexHover);
            theme->hover=hoverColor;
        } else if (strncmp(line, "fontSize=", 9) == 0) {
            if (strcmp(line+9, "") == 0) continue;
            theme->fontSize = strtol(line+9, NULL, 10);
        } else if (strncmp(line, "borderRadius=", 13) == 0) {
            theme->borderRadius = strtol(line+13, NULL, 10);
        } else if (strncmp(line, "iconSize=", 9) == 0) {
            theme->iconSize = strtol(line+9, NULL, 10);
        } else if (strncmp(line, "horizontalSpacing=", 18) == 0) {
            theme->horizontalSpacing = strtol(line+18, NULL, 10);
        } else if (strncmp(line, "verticalSpacing=", 16) == 0) {
            theme->verticalSpacing = strtol(line+16, NULL, 10);
        } else if (strncmp(line, "font=", 5) == 0) {
            char pathFont[512];
            strncpy(pathFont, line + 5, sizeof(pathFont) - 1);
            pathFont[sizeof(pathFont) - 1] = '\0';
            theme->fontPath = strdup(pathFont);
        } else if (strncmp(line, "width=", 6) == 0) {
            theme->width = strtol(line+6, NULL, 10);
        } else if (strncmp(line, "padding=", 8) == 0) {
            theme->padding = strtol(line+8, NULL, 10);
        } else if (strncmp(line, "apps=", 5) == 0) {
            int count = 0;
            char *token = strtok(line+5, ";");
            while (token != NULL) {
                pathApps[count++] = strdup(token);
                token = strtok(NULL, ";");
                (*lenPaths)++;
            }
        }
    }

    fclose(f);
    return 0;
}

void theme_load_assets(Theme *theme) {
    theme->font = LoadFontEx(theme->fontPath, 32, NULL, 255);
    if (theme->font.texture.id <= 0) {
        theme->font = GetFontDefault();
    }
}
