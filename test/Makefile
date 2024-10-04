CFLAGS = -O1 -Wall -I../src
CCX = g++

LIBTINYFP = ../src/libtinyfp.a
APPNAME = test

all: $(APPNAME)

DEMOFILES = test.o

$(APPNAME): $(DEMOFILES)
	$(CCX) $(DEMOFILES)  $(LIBTINYFP)  -o $(APPNAME)  

test.o: test.cpp
	$(CCX) $(CFLAGS) -c test.cpp

clean:
	rm -f $(APPNAME) *.o

rebuild: clean all

t: clean all
	./test
