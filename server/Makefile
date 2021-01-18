BUILDDIR = build
TESTDIR = tests
TARGETDIR = bin
SRCDIR = src_cpp
CFLAGS = -Wall -pedantic -Wno-long-long -I include -std=c++11 -fPIC
TESTFLAG = -lboost_unit_test_framework
INC = -I /usr/include/python3.7
SHARED_LIBRARY_FLAGS = -pthread -lboost_python37
CC = g++

server: $(BUILDDIR)/Agents_Map.o $(BUILDDIR)/City.o $(BUILDDIR)/Agent.o $(BUILDDIR)/Road.o $(BUILDDIR)
	$(CC) $(BUILDDIR)/*.o $(INC) $(SHARED_LIBRARY_FLAGS) -shared -o $(BUILDDIR)/map_module.so

$(BUILDDIR)/Agents_Map.o: $(SRCDIR)/Agents_Map.cpp $(BUILDDIR)
	$(CC) -c $(SRCDIR)/Agents_Map.cpp $(INC) -o $(BUILDDIR)/Agents_Map.o $(CFLAGS)

$(BUILDDIR)/City.o: $(SRCDIR)/City.cpp $(BUILDDIR)
	$(CC) -c $(SRCDIR)/City.cpp -o $(BUILDDIR)/City.o $(CFLAGS)

$(BUILDDIR)/Agent.o: $(SRCDIR)/Agent.cpp $(BUILDDIR)
	$(CC) -c $(SRCDIR)/Agent.cpp -o $(BUILDDIR)/Agent.o  $(CFLAGS)

$(BUILDDIR)/Road.o: $(SRCDIR)/Road.cpp $(BUILDDIR)
	$(CC) -c $(SRCDIR)/Road.cpp -o $(BUILDDIR)/Road.o  $(CFLAGS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

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
	$(CC) $(CFLAGS) $(INC) -c $(SRCDIR)/Road.cpp -o $(BUILDDIR)/Road.o
	$(CC) $(CFLAGS) $(INC) -c $(SRCDIR)/Agent.cpp -o $(BUILDDIR)/Agent.o -pthread
	$(CC) $(CFLAGS) $(INC) -c $(TESTDIR)/Agent_test.cpp -o $(BUILDDIR)/Agent_test.o -pthread
	$(CC) $(CFLAGS) $(INC) -c $(SRCDIR)/City.cpp -o $(BUILDDIR)/City.o -pthread
	$(CC) $(CFLAGS) $(INC) -c $(TESTDIR)/City_test.cpp -o $(BUILDDIR)/City_test.o -pthread
	$(CC) $(BUILDDIR)/City.o $(BUILDDIR)/Agent.o $(BUILDDIR)/Agent_test.o $(BUILDDIR)/Road.o -o $(TARGETDIR)/test_agent $(TESTFLAG) -pthread
	$(CC) $(BUILDDIR)/City.o $(BUILDDIR)/City_test.o $(BUILDDIR)/Road.o -o $(TARGETDIR)/test_city $(TESTFLAG) -pthread
	./bin/test_city
	./bin/test_agent
