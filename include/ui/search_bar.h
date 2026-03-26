#include "ui/theme.h"

void update_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, int* currentFrame);
void draw_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, char utf8String[127*4]);
