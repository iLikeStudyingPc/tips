#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

int is_directory(const char *path);
void print_files(const char *directory);
char **get_files(const char *directory);

int is_directory(const char *path) {
#ifdef _WIN32
    DWORD attributes = GetFileAttributesA(path);
    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat file_stat;
    if (stat(path, &file_stat) == 0) {
        return S_ISDIR(file_stat.st_mode);
    }
    return 0;
#endif
}

void print_files(const char *directory) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        if (!is_directory(file_path)) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

char **get_files(const char *directory) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        return NULL;
    }

    char **files = malloc(100 * sizeof(char *));
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        if (!is_directory(file_path)) {
            files[count] = malloc(strlen(entry->d_name) + 1);
            strcpy(files[count], entry->d_name);
            count++;
        }
    }

    closedir(dir);

    files[count] = NULL;
    return files;
}

int main() {
    const char *directory = "/"; // 示例文件夹路径

    printf("打印文件夹中的文件:\n");
    print_files(directory);

    printf("\n返回文件夹中的文件:\n");
    char **files = get_files(directory);
    if (files == NULL) {
        printf("无法返回文件。\n");
        return 1;
    }

    for (int i = 0; files[i] != NULL; i++) {
        printf("%s\n", files[i]);
        free(files[i]);
    }
    free(files);

    return 0;
}