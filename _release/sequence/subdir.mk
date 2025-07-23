
CPP_SRCS += \
../src/sequence/sequence.cpp 

CPP_DEPS += \
./sequence/sequence.d 

OBJS += \
./sequence/sequence.o 

sequence/%.o: ../src/sequence/%.cpp sequence/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-sequence

clean-sequence:
	-$(RM) ./sequence/sequence.d ./sequence/sequence.o

.PHONY: clean-sequence

