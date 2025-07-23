
CPP_SRCS += \
../src/extensions/Extensions.cpp 

CPP_DEPS += \
./extensions/Extensions.d 

OBJS += \
./extensions/Extensions.o 

extensions/%.o: ../src/extensions/%.cpp extensions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-extensions

clean-extensions:
	-$(RM) ./extensions/Extensions.d ./extensions/Extensions.o

.PHONY: clean-extensions

