
CPP_SRCS += \
../src/prelude.cpp 

CPP_DEPS += \
./prelude.d 

OBJS += \
./prelude.o 

%.o: ../src/%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-root

clean-root:
	-$(RM) ./prelude.d ./prelude.o

.PHONY: clean-root

