CFLAGS = -O1 -Wall -I../src
CCX = g++

LIBTINYFP = ../src/libtinyfp.a
APPNAME = test

all: $(APPNAME)

# DEMOFILES = test.o \
# 			option.o \
# 			either.o \
# 			try.o \
# 			uber.o \
# 			prelude.o \
# 			extensions.vector.o \
# 			sequence.o \
# 			extensions.flow.o \
# 			pipeline.o
DEMOFILES = test.o pipeline.o

$(APPNAME): $(DEMOFILES)
	$(CCX) $(DEMOFILES)  $(LIBTINYFP) -o $(APPNAME)

%.o: %.cpp
	$(CCX) $(CFLAGS) -c $<


clear:
	clear

clean:
	clear
	rm -f $(APPNAME) $(DEMOFILES)

rebuild: clean clear all

t: clean all
	valgrind --leak-check=yes --error-exitcode=1 ./test
