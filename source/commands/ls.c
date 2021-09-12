#include <stdio.h>
#include "ls.h"
#include <sys/stat.h>
#include <dirent.h>
#include "../../globals.h"
String *filePermissions(String* filePath) {
    String *permissions = initString("----------");
    struct stat fileStat;
    if (stat(filePath->str, &fileStat) < 0) {
        printf("Error: File not found\n");
        return NULL;
    }
    if (S_ISDIR(fileStat.st_mode)) permissions->str[0] = 'd';
    int bits[3][3] = {{S_IRUSR, S_IWUSR, S_IXUSR}, {S_IRGRP, S_IWGRP, S_IXGRP}, {S_IROTH, S_IWOTH, S_IXOTH}};
    char *rwx = "rwx";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (fileStat.st_mode & bits[i][j]) permissions->str[1 + i * 3 + j] = rwx[j];
        }
    }
    return permissions;
}
void listDirectories(String* path, int showHidden) {
    DIR *directory;
    struct dirent *dir;
    directory = opendir(path->str);
    while ((dir = readdir(directory)) != NULL) {
        if (!strcmp("..", dir->d_name) || !strcmp(".", dir->d_name)) continue;
        if (!showHidden && dir->d_name[0] == '.') continue;
        printf("%s\n", dir->d_name);
    }
    closedir(directory);
}
void commandLS(TokenArray *tokens) {
    if (tokens->argCount > 4) {
        printf("ls: Too many arguments\n");
        return;
    }
    if (tokens->argCount == 1) {
        listDirectories(currentPath, 0);
    }
}