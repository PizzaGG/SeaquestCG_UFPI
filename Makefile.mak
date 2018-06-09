CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = main.o \
         NovoArquivo.o \
         AppResource.res

LIBS   = -mwindows -static -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32 -lmingw32 -lSDLmain -lSDL
CFLAGS = -DGLUT_STATIC -I"Biblioteca SDL\SDL-1.2.15\include\SDL"

.PHONY: CG.exe clean clean-after

all: CG.exe

clean:
	$(RM) $(OBJS) CG.exe

clean-after:
	$(RM) $(OBJS)

CG.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.cpp
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

NovoArquivo.o: NovoArquivo.c
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

