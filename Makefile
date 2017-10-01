INSTALLDIR=/usr/local/bin
all: errno
static: errno-static
clean:
	rm -fr errno errno-static *.o

errno: errno.o

errno-static: errno.o
	$(CC) $(CFLAGS) -static $< -o $@

VERSION := 1.0
release:
	CFLAGS=-D'VERSION=\"$(VERSION)\"' make clean errno

errno.o: errno.c db.inc
	$(CC) $(CFLAGS) -c -o $@ $<

db.inc: gendb known.errno
	./gendb $< > $@

install: errno
	install errno $(DESTDIR)$(INSTALLDIR)/errno


.PHONY: all static clean release
