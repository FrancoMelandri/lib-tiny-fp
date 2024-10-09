CFLAGS = -O1 -Wall -I../src
CCX = g++

LIBTINYFP = ../src/libtinyfp.a
APPNAME = test

all: $(APPNAME)

DEMOFILES = test.o option.o either.o try.o uber.o prelude.o extensions.vector.o sequence.o

$(APPNAME): $(DEMOFILES)
	$(CCX) $(DEMOFILES)  $(LIBTINYFP) -o $(APPNAME)

%.o: %.cpp
	$(CCX) $(CFLAGS) -c $<

clean:
	rm -f $(APPNAME) $(DEMOFILES)

rebuild: clean all

t: clean all
	./test
