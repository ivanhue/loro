#include <unistd.h>
#include "core/apps.h"
// #include "ui/theme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static int compare_apps(const void *a, const void *b) {
    const App *app_a = (const App *)a;
    const App *app_b = (const App *)b;
    return strcmp(app_a->name, app_b->name);
}

static void print_apps(const App *apps, int length) {
    printf("\n--- DEBUG APP LIST (Size: %d) ---\n", length);

    if (length <= 0) {
        printf("Empty list.\n");
        return;
    }

    for (int i = 0; i < length; i++) {
        printf("[%03d] Name: %-20s\n", i, apps[i].name[0] != '\0' ? apps[i].name : "(EMPTY)");
    }
    printf("-----------------------------------\n\n");
}

static void parse_desktop_files(const char *path, App *app) {
    FILE *f = fopen(path, "r");
    if (!f) return;
    char line[512];
    int in_desktop_entry = 0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '[') {
            in_desktop_entry = strncmp(line, "[Desktop Entry]", 15) == 0;
            continue;
        }

        if (!in_desktop_entry) continue;

        if (strncmp(line, "Name=", 5) == 0) {
            strncpy(app->name, line + 5, sizeof(app->name) - 1);
            app->name[sizeof(app->name) - 1] = '\0';
            app->name[strcspn(app->name, "\n")] = '\0';
        } else if (strncmp(line, "Exec=", 5) == 0) {
            strncpy(app->exec, line + 5, sizeof(app->exec) - 1);
            app->exec[sizeof(app->exec) - 1] = '\0';
            app->exec[strcspn(app->exec, "\n")] = '\0';
        } else if (strncmp(line, "Icon=", 5) == 0) {
            strncpy(app->icon, line + 5, sizeof(app->icon) - 1);
            app->icon[sizeof(app->icon) - 1] = '\0';
            app->icon[strcspn(app->icon, "\n")] = '\0';
        } else if (strncmp(line, "Type=", 5) == 0) {
            strncpy(app->type, line + 5, sizeof(app->type) - 1);
            app->type[sizeof(app->type) - 1] = '\0';
            app->type[strcspn(app->type, "\n")] = '\0';
        } else if (strncmp(line, "NoDisplay=", 10) == 0) {
            app->no_display = strncmp(line + 10, "true", 4) == 0;
        } else if (strncmp(line, "Hidden=", 7) == 0) {
            app->hidden = strncmp(line + 7, "true", 4) == 0;
        }
    }
    fclose(f);
}

int apps_load(App *out, int max, char **pathApps, int lenPaths) {
    struct dirent *entry;
    int count = 0;

    for (int i=0; i<lenPaths; i++) {
        DIR *dir = opendir(pathApps[i]);
        if (!dir) continue;
        while ((entry = readdir(dir)) != NULL && count < max) {
            const char *ext = strrchr(entry->d_name, '.');
            if (!ext || strcmp(ext, ".desktop") != 0) continue;

            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", pathApps[i], entry->d_name);
            App app = {0};
            parse_desktop_files(full_path, &app);

            if (app.name[0] != '\0'
                && strcmp(app.type, "Application") == 0
                && !app.no_display
                && !app.hidden
            ) {
                out[count++] = app;
                printf("app encontrada: %s\n", app.name);
            } else {
                printf("app descartada: %s\n", app.name);
            }
        }
        closedir(dir);
    }
    qsort(out, count, sizeof(App), compare_apps);
    return count;
}

void launch(App *app) {
    if (!app || app->exec[0] == '\0') return;
    execlp("sh", "sh", "-c", app->exec, NULL);
}

void init_current_apps(const App *totalApps, App *currentApps, int countTotal, int* countCurrent, int max_out) {
    int to_copy = (countTotal > max_out) ? max_out : countTotal;
    *countCurrent = to_copy;
    memcpy(currentApps, totalApps, sizeof(App) * to_copy);
    print_apps(totalApps, countTotal);
}

void update_apps_list(const App *totalApps, App *currentApps, int countTotal, int* countCurrent, char *search, int max_out) {
    if (search == NULL || search[0] == '\0') {
        init_current_apps(totalApps, currentApps, countTotal, countCurrent, max_out);
        // print_apps(currentApps, *countCurrent);
        return;
    }
    *countCurrent = 0;
    for (int i=0; i<countTotal; i++) {
        if (*countCurrent < max_out) {
            if (strcasestr(totalApps[i].name, search) != NULL) {
                currentApps[*countCurrent] = totalApps[i];
                (*countCurrent)++;
            }
        } else {
            break;
        }
    }
}
