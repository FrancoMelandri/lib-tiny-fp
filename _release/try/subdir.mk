
CPP_SRCS += \
../src/try/Try.cpp 

CPP_DEPS += \
./try/Try.d 

OBJS += \
./try/Try.o 

try/%.o: ../src/try/%.cpp try/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-try

clean-try:
	-$(RM) ./try/Try.d ./try/Try.o

.PHONY: clean-try

