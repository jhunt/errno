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

int parse(const char *s)
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

	for (i = 1; i < argc; i++) {
		e = parse(argv[i]);
		if (e < 0) continue;
		printf("%-16s %d %s\n", name(e), e, desc(e));
	}
	return 0;
}
