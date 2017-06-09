ifeq ($(OS),Windows_NT)
LDFLAGS=libSOIL.a -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
EXECUTABLE=main.exe
else
LDFLAGS=-lGL -lglut
EXECUTABLE=main
endif

CFLAGS=-g -DDEBUG

all:
	g++ main.cpp -c -o main.o $(CFLAGS)
	g++ main.o $(LDFLAGS) -o $(EXECUTABLE)

clean:
	rm main.o $(EXECUTABLE)