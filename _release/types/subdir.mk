
CPP_SRCS += \
../src/types/Types.cpp 

CPP_DEPS += \
./types/Types.d 

OBJS += \
./types/Types.o 

types/%.o: ../src/types/%.cpp types/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-types

clean-types:
	-$(RM) ./types/Types.d ./types/Types.o

.PHONY: clean-types

