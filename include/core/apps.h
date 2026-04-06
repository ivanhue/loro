#pragma once

#define MAX_APPS 512

typedef struct {
    char name[128];
    char exec[256];
    char icon[256];
    char type[32];
    int no_display;
    int hidden;
} App;

int apps_load(App *out, int max);
void launch(App *app);
