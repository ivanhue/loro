#include "ui/theme.h"
#include "core/apps.h"

#define MAX_SHOW_APPS 10

void draw_apps_list(Theme* theme, App *apps, int count, int max);
void draw_hover(Theme* theme, int index);
void draw_navigation(Theme* theme, App *currentApps, int* cursor);
void open_selected_app(App *currentApps, int* cursor);
