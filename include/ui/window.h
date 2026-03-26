#pragma once
#include "ui/theme.h"
#include "core/apps.h"

#define MAX_SHOW_APPS 10

void draw_window(Theme* theme, App *apps, int count, int max);
