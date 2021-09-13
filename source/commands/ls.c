#include "ls.h"

String *lastModified(time_t time) {
	String *date = newString();

	struct tm t;
	t = *localtime(&time);
	strftime(date->str, date->maxSize, "%b %d %H:%M", &t);
	updateLength(date);
	return date;
}

String *filePermissions(String *filePath) {
	String *permissions = initString("----------");
	struct stat fileStat;
	if (stat(filePath->str, &fileStat) < 0) {
		printf("File: %s\n", filePath->str);
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

long countBlocks(String *path, int countHidden) {
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	long count = 0;
	while ((dir = readdir(directory)) != NULL) {
		if (dir->d_name[0] == '.' && !countHidden)
			continue;
		struct stat file;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));
		stat(temp->str, &file);
		count += file.st_blocks;
	}
	return count / 2;
}

void findMaxLengths(String *path, int showHidden, unsigned int *maxLinks,
					unsigned int *maxUserLength, unsigned int *maxGroupLength,
					unsigned int *maxByteSize) {
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	while ((dir = readdir(directory)) != NULL) {
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		struct stat file;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));
		stat(temp->str, &file);
		String *userOwner = getUser(file.st_uid);
		String *groupOwner = getGroup(file.st_gid);

		unsigned byteLength = 0;
		long x = file.st_size;
		while (x != 0) {
			byteLength++;
			x /= 10;
		}

		unsigned linkLength = 0;
		unsigned long y = file.st_nlink;
		while (y != 0) {
			linkLength++;
			y /= 10;
		}

		*maxUserLength = MAX(*maxUserLength, userOwner->length);
		*maxGroupLength = MAX(*maxGroupLength, groupOwner->length);
		*maxByteSize = MAX(*maxByteSize, byteLength);
		*maxLinks = MAX(*maxLinks, linkLength);
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
		default: printf("ls: Unknown error\n"); break;
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

void listDirectories(String *path, int showHidden, int displayName) {
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
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		printf("%s\n", dir->d_name);
	}
	closedir(directory);
}

void listDirectoriesVerbose(String *path, int showHidden, int displayName) {
	if (!folderExists(*path)) {
		printf("%s: No such directory exists\n", path->str);
		return;
	}
	if (displayName) {
		printf("%s:\n", path->str);
	}
	DIR *directory;
	long totalBlocks = countBlocks(path, showHidden);
	printf("total %ld\n", totalBlocks);
	unsigned int maxLinks = 0, maxUserLength = 0, maxGroupLength = 0,
				 maxByteSize = 0;
	findMaxLengths(path, showHidden, &maxLinks, &maxUserLength, &maxGroupLength,
				   &maxByteSize);
	char buf[80];
	sprintf(buf, "%%s %%%uld %%-%us %%-%us %%%uld %%s %%s\n", maxLinks,
			maxUserLength, maxGroupLength, maxByteSize);
	struct dirent *dir;
	directory = opendir(path->str);
	while ((dir = readdir(directory)) != NULL) {
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		struct stat file;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));
		stat(temp->str, &file);
		String *userOwner = getUser(file.st_uid);
		String *groupOwner = getGroup(file.st_gid);
		String *date = lastModified(file.st_mtim.tv_sec);
		printf(buf, filePermissions(temp)->str, file.st_nlink, userOwner->str,
			   groupOwner->str, file.st_size, date->str, dir->d_name);
	}
	closedir(directory);
}

void commandLS(TokenArray *tokens) {
	int flags = checkFlags(tokens);
	if (flags == -1)
		return;

	int pathCount = countPaths(tokens);

	if (pathCount == 0) {
		if (flags & 2)
			listDirectoriesVerbose(currentPath, flags & 1, 0);
		else
			listDirectories(currentPath, flags & 1, 0);
	} else {
		for (int i = 1; i < tokens->argCount; i++) {
			if (tokens->args[i]->str[0] == '-')
				continue;
			if (flags & 2)
				listDirectoriesVerbose(tokens->args[i], flags & 1,
									   (pathCount > 1));
			else
				listDirectories(tokens->args[i], flags & 1, (pathCount > 1));
			if (i != tokens->argCount - 1)
				printf("\n");
		}
	}
}
