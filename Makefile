all: errno
static: errno-static
clean:
	rm -fr errno errno-static *.o

errno: errno.o

errno-static: errno.o
	$(CC) -static $< -o $@

errno.o: errno.c db.inc
	$(CC) -c -o $@ $<

db.inc: gendb known.errno
	./gendb $< > $@

.PHONY: all static clean
