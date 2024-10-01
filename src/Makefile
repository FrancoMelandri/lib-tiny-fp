# check if 32 or 64 bit system
ARCH := $(shell getconf LONG_BIT)
ifeq ($(ARCH),32)
LNAME = libtinyfp
else
LNAME = libtinyfp-64
endif


CCX = g++
AR = ar
CXXFLAGS = -std=c++17 -Wall -O2 -fPIC -D_GNU_SOURCE
LIBS = 
LIBNAME = $(LNAME).a
LIBOBJECTS = Option.o

all: $(LIBOBJECTS) $(LIBNAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

$(LIBNAME): $(LIBOBJECTS)
	$(AR) scr $(LIBNAME) $(LIBOBJECTS)

clean:
	rm -f *.o *.a
