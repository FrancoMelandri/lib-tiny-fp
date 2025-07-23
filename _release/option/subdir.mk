
CPP_SRCS += \
../src/option/Option.cpp 

CPP_DEPS += \
./option/Option.d 

OBJS += \
./option/Option.o 

option/%.o: ../src/option/%.cpp option/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-option

clean-option:
	-$(RM) ./option/Option.d ./option/Option.o

.PHONY: clean-option

