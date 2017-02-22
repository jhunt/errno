all: errno
static: errno-static
clean:
	rm -fr errno errno-static *.o

errno: errno.o

errno-static: errno.o
	$(CC) -static $< -o $@

.PHONY: all static clean
