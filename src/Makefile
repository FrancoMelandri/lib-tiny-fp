# check if 32 or 64 bit system

LNAME = libtinyfp
CCX = g++
AR = ar
CXXFLAGS = -std=c++17 -Wall -O2 -fPIC -D_GNU_SOURCE
LIBS = 
LIBNAME = $(LNAME).a
RM = rm -rf

LIBOBJECTS =

-include option/subdir.mk
-include either/subdir.mk
-include try/subdir.mk

all: $(LIBOBJECTS) $(LIBNAME)

$(LIBNAME): $(LIBOBJECTS) 
	$(AR) scr $(LIBNAME) $(LIBOBJECTS)

clean:
	-$(RM) $(LIBOBJECTS)  *.a

rebuild:
	make clean && make all
