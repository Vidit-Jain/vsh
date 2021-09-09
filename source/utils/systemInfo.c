#include "systemInfo.h"
String *getUsername() {
	struct passwd *pass = getpwuid(getuid());
	String *username = initString(pass->pw_name);
	return username;
}

String *getSystemName() {
	String *hostName = newString();
	gethostname(hostName->str, hostName->maxSize);
	updateLength(hostName);

	return hostName;
}