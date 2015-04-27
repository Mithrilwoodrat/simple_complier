CC = gcc
CCFLAGS = -std=gnu99 -O2 -Wall -g


all: scanner parser

scanner: scanner.c
	$(CC) $(CCFLAGS) $^ -o bin/$@

parser: parser.c
	$(CC) $(CCFLAGS) $^ -o bin/$@


scan: 
	bin/scanner test_input/test1 test_output/test_out1
	bin/scanner test_input/test2 test_output/test_out2
	bin/scanner test_input/test3 test_output/test_out3
	bin/scanner test_input/test4 test_output/test_out4
parse:
	bin/parser test_output/test_out1
	bin/parser test_output/test_out2
	bin/parser test_output/test_out3
	bin/parser test_output/test_out4
init:
	mkdir bin test_output test_input
clean:
	rm bin/* test_output/*
