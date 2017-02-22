#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define E(s) {"E" #s, E ## s}
struct ecode {
	const char *name;
	int         code;
};
static struct ecode ECODES[] = {
	/* from /usr/include/asm-generic/errno-base.h */
	E(PERM),  E(NOENT),  E(SRCH),  E(INTR),   E(IO),    E(NXIO),  E(2BIG),   E(NOEXEC),
	E(BADF),  E(CHILD),  E(AGAIN), E(NOMEM),  E(ACCES), E(FAULT), E(NOTBLK), E(BUSY),
	E(EXIST), E(XDEV),   E(NODEV), E(NOTDIR), E(ISDIR), E(INVAL), E(NFILE),  E(MFILE),
	E(NOTTY), E(TXTBSY), E(FBIG),  E(NOSPC),  E(SPIPE), E(ROFS),  E(MLINK),  E(PIPE),
	E(DOM),   E(RANGE),

	/* from /usr/include/asm-generic/errno.h */
	E(DEADLK),         E(NAMETOOLONG), E(NOLCK),          E(NOSYS),
	E(NOTEMPTY),       E(LOOP),        E(WOULDBLOCK),     E(NOMSG),
	E(IDRM),           E(CHRNG),       E(L2NSYNC),        E(L3HLT),
	E(L3RST),          E(LNRNG),       E(UNATCH),         E(NOCSI),
	E(L2HLT),          E(BADE),        E(BADR),           E(XFULL),
	E(NOANO),          E(BADRQC),      E(BADSLT),         E(DEADLOCK),
	E(BFONT),          E(NOSTR),       E(NODATA),         E(TIME),
	E(NOSR),           E(NONET),       E(NOPKG),          E(REMOTE),
	E(NOLINK),         E(ADV),         E(SRMNT),          E(COMM),
	E(PROTO),          E(MULTIHOP),    E(DOTDOT),         E(BADMSG),
	E(OVERFLOW),       E(NOTUNIQ),     E(BADFD),          E(REMCHG),
	E(LIBACC),         E(LIBBAD),      E(LIBSCN),         E(LIBEXEC),
	E(LIBMAX),         E(ILSEQ),       E(RESTART),        E(STRPIPE),
	E(USERS),          E(NOTSOCK),     E(DESTADDRREQ),    E(MSGSIZE),
	E(PROTOTYPE),      E(NOPROTOOPT),  E(PROTONOSUPPORT), E(SOCKTNOSUPPORT),
	E(OPNOTSUPP),      E(PFNOSUPPORT), E(AFNOSUPPORT),    E(ADDRINUSE),
	E(ADDRNOTAVAIL),   E(NETDOWN),     E(NETUNREACH),     E(NETRESET),
	E(CONNABORTED),    E(CONNRESET),   E(NOBUFS),         E(ISCONN),
	E(NOTCONN),        E(SHUTDOWN),    E(TOOMANYREFS),    E(TIMEDOUT),
	E(CONNREFUSED),    E(HOSTDOWN),    E(HOSTUNREACH),    E(ALREADY),
	E(INPROGRESS),     E(STALE),       E(UCLEAN),         E(NOTNAM),
	E(NAVAIL),         E(ISNAM),       E(REMOTEIO),       E(DQUOT),
	E(NOMEDIUM),       E(MEDIUMTYPE),  E(CANCELED),       E(NOKEY),
	E(KEYEXPIRED),     E(KEYREVOKED),  E(KEYREJECTED),    E(OWNERDEAD),
	E(NOTRECOVERABLE), E(RFKILL),      E(HWPOISON),
	{.name = NULL, .code = 0},
};
#undef E

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
