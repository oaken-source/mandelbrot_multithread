
# this is picked up by nmake on windows

all: multithread.exe

multithread.exe: bmp.obj mandelbrot.obj multithread.obj
	link $(LFLAGS) $** /out:multithread.exe

clean:
	-del *.obj
	-del multithread.exe
