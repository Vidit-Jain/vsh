#include "ls.h"

/* Returns a string for the last modified time
 * Gives the year instead of 24hr time if it's
 * been more than 6 months
 */
String *lastModified(time_t modifiedTime) {
	String *date = newString();

	struct tm *modifiedTimeStruct;
	modifiedTimeStruct = localtime(&modifiedTime);
	if (modifiedTimeStruct == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return NULL;
	}
	time_t now = time(NULL);
	time_t diff = now - modifiedTime;
	if (now < diff || diff >= SIX_MONTHS) {
		strftime(date->str, date->maxSize, "%b %d  %Y", modifiedTimeStruct);
	} else {
		strftime(date->str, date->maxSize, "%b %d %H:%M", modifiedTimeStruct);
	}
	updateLength(date);
	return date;
}
/* Returns us a 10 character string
 * to display the file permissions
 * of the form "drwx--xrw-"
 */
String *filePermissions(String *filePath) {
	String *permissions = initString("----------");
	struct stat fileStat;
	if (lstat(filePath->str, &fileStat) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return NULL;
	}
	if (S_ISDIR(fileStat.st_mode))
		permissions->str[0] = 'd';
	else if (S_ISBLK(fileStat.st_mode))
		permissions->str[0] = 'b';
	else if (S_ISFIFO(fileStat.st_mode))
		permissions->str[0] = 'p';
	else if (S_ISLNK(fileStat.st_mode))
		permissions->str[0] = 'l';
	else if (S_ISCHR(fileStat.st_mode))
		permissions->str[0] = 'c';
	else if (S_ISSOCK(fileStat.st_mode))
		permissions->str[0] = 's';

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
// Count the number of blocks occupied by files in directory
long countBlocks(String *path, int countHidden) {
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	if (directory == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	long count = 0;
	errno = 0;
	while ((dir = readdir(directory)) != NULL) {
		if (dir->d_name[0] == '.' && !countHidden)
			continue;
		struct stat file;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));
		if (lstat(temp->str, &file) < 0) {
			errorHandler(GENERAL_NONFATAL);
			return -1;
		}
		count += file.st_blocks;
	}
	if (errno) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	return count / 2;
}
/* Find max number of characters taken by:
 * 1. links
 * 2. username length
 * 3. groupname length
 * 4. bytes occupied
 * To be able to print the ls -l output in aligned manner
 */
int findMaxLengths(String *path, int showHidden, unsigned int *maxLinks,
				   unsigned int *maxUserLength, unsigned int *maxGroupLength,
				   unsigned int *maxByteSize) {
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	if (directory == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	errno = 0;
	while ((dir = readdir(directory)) != NULL) {
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		struct stat file;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));
		if (stat(temp->str, &file) < 0) {
			errorHandler(GENERAL_NONFATAL);
			return -1;
		}
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

	if (closedir(directory) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	return 0;
}
/* Check the flags passed by the user
 * -l - Verbose ls
 * -a - Show hidden files
 */
int checkFlagsLs(TokenArray *tokens) {
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
			errorHandler(INVALID_ARGS);
			flags = -1;
			break;
		default: errorHandler(INVALID_ARGS);
		}
		if (flags == -1)
			break;
	}
	optind = 0;
	return flags;
}
/* Count number of paths to figure out if we need to display
 * name before printing contents of directories
 */
int countPaths(TokenArray *tokens) {
	int pathCount = 0;
	for (int i = 1; i < tokens->argCount; i++) {
		pathCount += (tokens->args[i]->str[0] != '-');
	}
	return pathCount;
}
// Prints a file name
void listFile(char *fileName) { printf("%s\n", fileName); }
// Prints a file's details
void listFileVerbose(String *path, char *fileName, char *buf) {
	struct stat file;
	if (stat(path->str, &file) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (buf == NULL) {
		buf = "%s %ld %s %s %ld %s %s\n";
	}
	String *userOwner = getUser(file.st_uid);
	String *groupOwner = getGroup(file.st_gid);
	String *date = lastModified(file.st_mtim.tv_sec);
	String *permissions = filePermissions(path);
	if (permissions == NULL) {
		return;
	}
	printf(buf, permissions->str, file.st_nlink, userOwner->str,
		   groupOwner->str, file.st_size, date->str, fileName);
}

/* List all the directories. If -a is passed, showHidden = 1,
 * which means to check hidden files as well
 */
void listDirectories(String *path, int showHidden, int displayName) {
	if (!folderExists(*path)) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (displayName) {
		printf("%s:\n", path->str);
	}
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	if (directory == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	errno = 0;
	while ((dir = readdir(directory)) != NULL) {
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		listFile(dir->d_name);
	}
	if (errno) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (closedir(directory) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
/* List all directory contents verbosely
 * If -a passed, showHidden = 1, which means
 * to check hidden files as well
 */
void listDirectoriesVerbose(String *path, int showHidden, int displayName) {
	if (!folderExists(*path)) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (displayName) {
		printf("%s:\n", path->str);
	}
	long totalBlocks = countBlocks(path, showHidden);
	if (totalBlocks == -1) {
		return;
	}
	printf("total %ld\n", totalBlocks);
	unsigned int maxLinks = 0, maxUserLength = 0, maxGroupLength = 0,
				 maxByteSize = 0;
	int err = findMaxLengths(path, showHidden, &maxLinks, &maxUserLength,
							 &maxGroupLength, &maxByteSize);
	if (err < 0) {
		return;
	}
	char buf[80];
	sprintf(buf, "%%s %%%uld %%-%us %%-%us %%%uld %%s %%s\n", maxLinks,
			maxUserLength, maxGroupLength, maxByteSize);
	DIR *directory;
	struct dirent *dir;
	directory = opendir(path->str);
	if (directory == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	errno = 0;
	while ((dir = readdir(directory)) != NULL) {
		if (!showHidden && dir->d_name[0] == '.')
			continue;
		String *temp = newString();
		stringCopy(temp, *path);
		concatenate(temp, initString("/"));
		concatenate(temp, initString(dir->d_name));

		listFileVerbose(temp, dir->d_name, buf);
	}
	if (errno) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (closedir(directory) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}

void commandLS(TokenArray *tokens) {
	int flags = checkFlagsLs(tokens);
	if (flags == -1) // Some error occurred
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

			if (flags & 2) {
				if (fileExists(*tokens->args[i])) {
					listFileVerbose(tokens->args[i], tokens->args[i]->str,
									NULL);
				} else {
					listDirectoriesVerbose(tokens->args[i], flags & 1,
										   (pathCount > 1));
				}
			} else {
				if (fileExists(*tokens->args[i])) {
					listFile(tokens->args[i]->str);
				} else {
					listDirectories(tokens->args[i], flags & 1,
									(pathCount > 1));
				}
			}
			if (i != tokens->argCount - 1)
				printf("\n");
		}
	}
}
