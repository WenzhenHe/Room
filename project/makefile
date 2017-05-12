ifeq ($(OS),Windows_NT)
LDFLAGS=-lfreeglut -lopengl32 -Wl,--subsystem,windows -lglu32
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