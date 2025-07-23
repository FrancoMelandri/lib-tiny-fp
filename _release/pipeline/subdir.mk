
CPP_SRCS += \
../src/pipeline/Pipeline.cpp 

CPP_DEPS += \
./pipeline/Pipeline.d 

OBJS += \
./pipeline/Pipeline.o 

pipeline/%.o: ../src/pipeline/%.cpp pipeline/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O2 -g -Wall -c -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-pipeline

clean-pipeline:
	-$(RM) ./pipeline/Pipeline.d ./pipeline/Pipeline.o

.PHONY: clean-pipeline

