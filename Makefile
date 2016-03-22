CC = gcc
CCFLAGS = -std=gnu99 -O2 -Wall -g


all: init scanner parser

scanner: scanner.c
	$(CC) $(CCFLAGS) $^ -o bin/$@

parser: parser.c
	$(CC) $(CCFLAGS) $^ -o bin/$@

scan: test_scanner.sh
	bash test_scanner.sh

parse: test_parser.sh
	test_parser.sh

init:
	mkdir -p bin test_output test_input
clean:
	rm bin/* test_output/*
