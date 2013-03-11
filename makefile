PYTHON ?= python2.7
CC ?= gcc

default:
	mkdir -p bin
	$(CC) call_test.c -o bin/call_test -Wall -std=c99 -I/usr/include/$(PYTHON)/ -l$(PYTHON)

run: default
	./bin/call_test


clean:
	rm -f bin/*
	rm -f *.pyc
