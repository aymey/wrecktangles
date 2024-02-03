CC = clang
LIBS = -lSDL2 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CFLAGS_DEBUG = -Wall -Wextra -ggdb $(LIBS)
CFLAGS_RELEASE = -O3 -w $(LIBS)
TARGET = wrecktangles

debug: src/*.c
	$(CC) $(CFLAGS_DEBUG) src/*.c -o $(TARGET)

release: src/*
	$(CC) $(CFLAGS_RELEASE) src/*.c -o $(TARGET)
