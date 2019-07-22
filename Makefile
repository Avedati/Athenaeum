OUT=bin/cWebScraper

all:
	gcc `pkg-config --cflags gtk+-3.0` -o $(OUT) src/*.c `pkg-config --libs gtk+-3.0`
