#include "ui/theme.h"
#include "core/apps.h"

void update_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, int* currentFrame, const App *totalApps, App *currentApps, int totalCount, int* currentCount, int max_out, int* cursor);
void draw_search_bar(Theme* theme, char value[127][4], int* frames, int* letterCount, char utf8String[127*4]);
