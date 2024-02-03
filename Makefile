CC = clang
CFLAGS_DEBUG = -Wall -Wextra -ggdb
CFLAGS_RELEASE = -O3
TARGET = wrecktangles

debug: src/*
	$(CC) $(CFLAGS_DEBUG) src/* -o $(TARGET)

release: src/*
	$(CC) $(CFLAGS_RELEASE) src/* -o $(TARGET)
