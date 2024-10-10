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
-include sequence/subdir.mk
-include extensions/subdir.mk

all: $(LIBOBJECTS) $(LIBNAME)

$(LIBNAME): $(LIBOBJECTS) 
	$(AR) scr $(LIBNAME) $(LIBOBJECTS)

clean:
	-$(RM) $(LIBOBJECTS)  *.a

rebuild:
	make clean && make all

install: clean all
	install -D $(LIBNAME) -t /usr/local/lib/$(LNAME) 
	install -D *.h -t /usr/local/inlcude/$(LNAME)
	install -D ./either/*.h -t /usr/local/inlcude/$(LNAME)/either/
	install -D ./option/*.h -t /usr/local/inlcude/$(LNAME)/option/
	install -D ./try/*.h -t /usr/local/inlcude/$(LNAME)/try/
	install -D ./try/*.h -t /usr/local/inlcude/$(LNAME)/sequence/
