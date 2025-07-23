
CPP_SRCS += \
../src/either/Either.cpp 

CPP_DEPS += \
./either/Either.d 

OBJS += \
./either/Either.o 

either/%.o: ../src/either/%.cpp either/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-either

clean-either:
	-$(RM) ./either/Either.d ./either/Either.o

.PHONY: clean-either

