#include "ls.h"
#include "../../globals.h"
#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/stat.h>
int folderExists(String path) {
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISDIR(sb.st_mode);
}
String *filePermissions(String *filePath) {
	String *permissions = initString("----------");
	struct stat fileStat;
	if (stat(filePath->str, &fileStat) < 0) {
		printf("Error: File not found\n");
		return NULL;
	}
	if (S_ISDIR(fileStat.st_mode))
		permissions->str[0] = 'd';
	int bits[3][3] = {{S_IRUSR, S_IWUSR, S_IXUSR},
					  {S_IRGRP, S_IWGRP, S_IXGRP},
					  {S_IROTH, S_IWOTH, S_IXOTH}};
	char *rwx = "rwx";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (fileStat.st_mode & bits[i][j])
				permissions->str[1 + i * 3 + j] = rwx[j];
		}
	}
	return permissions;
}
void listDirectories(String *path, int flags, int displayName) {
	if (!folderExists(*path)) {
		printf("%s: No such directory exists\n", path->str);
		return;
	}
	if (displayName) {
		printf("%s:\n", path->str);
	}
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	while ((dir = readdir(directory)) != NULL) {
		if (!strcmp("..", dir->d_name) || !strcmp(".", dir->d_name))
			continue;
		if (!(flags & 1) && dir->d_name[0] == '.')
			continue;
		printf("%s\n", dir->d_name);
	}
	closedir(directory);
}
int checkFlags(TokenArray *tokens) {
	char *args[tokens->argCount];
	for (int i = 0; i < tokens->argCount; i++) {
		args[i] = tokens->args[i]->str;
	}
	int flags = 0;
	int opt;
	while ((opt = getopt((int)tokens->argCount, args, ":al")) != -1) {
		switch (opt) {
		case 'l': flags |= 2; break;
		case 'a': flags |= 1; break;
		case '?':
			printf("ls: invalid option -- '%c'\n", optopt);
			flags = -1;
			break;
		}
		if (flags == -1)
			break;
	}
	optind = 1;
	return flags;
}
int countPaths(TokenArray *tokens) {
	int pathCount = 0;
	for (int i = 1; i < tokens->argCount; i++) {
		pathCount += (tokens->args[i]->str[0] != '-');
	}
	return pathCount;
}
void commandLS(TokenArray *tokens) {
	int flags = checkFlags(tokens);
	if (flags == -1)
		return;

	int pathCount = countPaths(tokens);

	if (pathCount == 0) {
		listDirectories(currentPath, flags, 0);
	} else {
		for (int i = 1; i < tokens->argCount; i++) {
			if (tokens->args[i]->str[0] == '-')
				continue;
			listDirectories(tokens->args[i], flags, (pathCount > 1));
		}
	}
}