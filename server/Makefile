
CC = g++
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
TESTDIR = test
TARGET = server
TESTTARGET = test
#TESTSOURCE = server_test.cpp

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -std=c++11 -g -Wall
TESTFLAG = -lboost_unit_test_framework
INC = -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	$(CC) $^ -o ./$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

#tests:
#	@mkdir -p $(TARGETDIR)
#	@mkdir -p $(BUILDDIR)
#	$(CC) $(CFLAGS) $(INC) -c $(SRCDIR)/$(TARGET).cpp -o $(BUILDDIR)/$(TARGET).o
#	$(CC) $(CFLAGS) $(INC) -c $(TESTDIR)/$(TESTTARGET).cpp -o $(BUILDDIR)/$(TARGETTEST).o
#	$(CC) $(BUILDDIR)/$(TARGETTEST).o $(BUILDDIR)/$(TARGETTEST).o -o $(TARGET)_test -lboost_unit_test_framework

#run:
#	./$(TARGET)

#runtests:
#	./bin/$(TESTTARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGETDIR)"; $(RM) -r $(BUILDDIR) $(TARGETDIR)

.PHONY: clean
