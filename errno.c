#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "db.inc"

#define desc strerror
static const char * name(int e)
{
	int i;
	for (i = 0; ECODES[i].name; i++) {
		if (ECODES[i].code == e) {
			return ECODES[i].name;
		}
	}
	return "(unknown)";
}

static int exists(int e)
{
	int i;
	for (i = 0; ECODES[i].name; i++) {
		if (ECODES[i].code == e) {
			return 1;
		}
	}
	return 0;
}

static int parse(const char *s)
{
	char *end;
	unsigned long x;
	int i;

	x = strtol(s, &end, 10);
	if (end && !*end) return x;

	for (i = 0; ECODES[i].name; i++) {
		if (strcasecmp(ECODES[i].name, s) == 0) {
			return ECODES[i].code;
		}
	}

	fprintf(stderr, "unrecognized error '%s'\n", s);
	return -1;
}

int main (int argc, char **argv)
{
	int i, e;

	if (argc >= 2 && strcmp(argv[1], "-v") == 0) {
#ifdef VERSION
		printf("errno v" VERSION "\n");
#else
		printf("errno (development version)\n");
#endif
		printf("Copyright (c) 2017 James Hunt\n");
		printf("https://jameshunt.us/code/errno\n");
		return 0;
	}

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			printf("USAGE: errno [arguments]\n\n");
			printf("i.e. errno 1 2 3\n");
			printf("     errno ENOENT EPERM\n");
			printf("     errno\n");
			return 1;
		}
		e = parse(argv[i]);
		if (e < 0) continue;
		printf("%-16s %d %s\n", name(e), e, desc(e));
	}
	if (argc == 1) {
		for (e = 1; e < 255; e++) {
			if (!exists(e)) continue;
			printf("%-16s %d %s\n", name(e), e, desc(e));
		}
	}
	return 0;
}
