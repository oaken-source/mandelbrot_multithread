
# this is picked up by GNU make on all platforms

LDLIBS = -lm

all: multithread

multithread: bmp.o mandelbrot.o multithread.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) *.o
	$(RM) multithread

.PHONY: all clean
