
LIBOBJECTS += \
	./prelude.o

%o: ../src/%.c
	$(CCX) $(CXXFLAGS) -c prelude.c -o prelude.o