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

int apps_load(App *out, int max, char **pathApps, int lenPaths);
void launch(App *app);
void init_current_apps(const App *totalApps, App *currentApps, int countTotal, int* countCurrent, int max_out);
void update_apps_list(const App *totalApps, App *currentApps, int countTotal, int* countCurrent, char *search, int max_out);
