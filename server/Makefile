BUILDDIR = build
TESTDIR = tests
TARGETDIR = bin
SRCDIR = src_cpp
CFLAGS = -std=c++11 -g -Wall
TESTFLAG = -lboost_unit_test_framework
INC = -I include
CC = g++

server:
	mkdir -p $(BUILDDIR)
	scons

run: server
	python3 server.py

clean:
	rm -r -f $(BUILDDIR)
	rm -r -f $(TARGETDIR)
	rm -f .sconsign.dblite
	rm -f */*.so
	rm -f */*.os

test:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c $(SRCDIR)/City.cpp -o $(BUILDDIR)/City.o
	$(CC) $(CFLAGS) $(INC) -c $(TESTDIR)/City_test.cpp -o $(BUILDDIR)/City_test.o
	$(CC) $(BUILDDIR)/City.o  $(BUILDDIR)/City_test.o -o $(TARGETDIR)/test_city $(TESTFLAG)

runtests:
	./bin/test_city
