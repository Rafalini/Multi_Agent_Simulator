BUILDDIR = build
TESTDIR = tests
TARGETDIR = bin
SRCDIR = src_cpp
CFLAGS = -Wall -pedantic -Wno-long-long -I include -std=c++11
TESTFLAG = -lboost_unit_test_framework
INC = -I include -pthread
CC = g++

server:
	mkdir -p $(BUILDDIR)
	scons

serv:
	mkdir -p $(BUILDDIR)
	g++ -o src_cpp/Agents_Map.os -c -fPIC -Wall -pedantic -pthread -Wno-long-long -I include -std=c++11 -I/usr/include/python3.7 src_cpp/Agents_Map.cpp
	g++ -o src_cpp/City.os -c -fPIC -Wall -pedantic -pthread -Wno-long-long -I include -std=c++11 -I/usr/include/python3.7 src_cpp/City.cpp
	g++ -o src_cpp/Agent.os -c -fPIC -Wall -pedantic -pthread -Wno-long-long -I include -std=c++11 -I/usr/include/python3.7 src_cpp/Agent.cpp
	g++ -o src_cpp/Road.os -c -fPIC -Wall -pedantic -pthread -Wno-long-long -I include -std=c++11 -I/usr/include/python3.7 src_cpp/Road.cpp
	g++ -o build/libmap_module.so -Wall -pthread -shared src_cpp/Agents_Map.os src_cpp/City.os src_cpp/Agent.os src_cpp/Road.os -L/usr/lib/python3.7 -lboost_python37
	shutil.copy(src_cpp/Agents_Map.cpp, build/map_module)

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
