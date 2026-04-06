#include <unistd.h>
#include "core/apps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static int compare_apps(const void *a, const void *b) {
    const App *app_a = (const App *)a;
    const App *app_b = (const App *)b;
    return strcmp(app_a->name, app_b->name);
}

static void parse_desktop_files(const char *path, App *app) {
    FILE *f = fopen(path, "r");
    if (!f) return;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Name=", 5) == 0) {
            strncpy(app->name, line + 5, sizeof(app->name)-1);
            app->name[strcspn(app->name, "\n")] = '\0';
        } else if (strncmp(line, "Exec=", 5) == 0) {
            strncpy(app->exec, line + 5, sizeof(app->exec)-1);
            app->exec[strcspn(app->exec, "\n")] = '\0';
        } else if (strncmp(line, "Icon=", 5) == 0) {
            strncpy(app->icon, line + 5, sizeof(app->icon)-1);
            app->icon[strcspn(app->icon, "\n")] = '\0';
        } else if (strncmp(line, "Type=", 5) == 0) {
            strncpy(app->type, line + 5, sizeof(app->type)-1);
            app->type[strcspn(app->type, "\n")] = '\0';
        } else if (strncmp(line, "NoDisplay=", 10) == 0) {
            app->no_display = strncmp(line+10, "true", 4) == 0;
        } else if (strncmp(line, "Hidden=", 7) == 0) {
            app->hidden = strncmp(line+7, "true", 4) == 0;
        }
    }
    fclose(f);
}

int apps_load(App *out, int max) {
    const char *dir_path = "/usr/share/applications";
    DIR *dir = opendir(dir_path);
    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < max) {
        const char *ext = strrchr(entry->d_name, '.');
        if (!ext || strcmp(ext, ".desktop") != 0) continue;

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        App app = {0};
        parse_desktop_files(full_path, &app);

        if (app.name[0] != '\0'
            && strcmp(app.type, "Application") == 0
            && !app.no_display
            && !app.hidden
        ) {
            out[count++] = app;
        }
    }

    closedir(dir);
    qsort(out, count, sizeof(App), compare_apps);
    return count;
}

void launch(App *app) {
    if (!app || app->exec[0] == '\0') return;
    execlp("sh", "sh", "-c", app->exec, NULL);
}
