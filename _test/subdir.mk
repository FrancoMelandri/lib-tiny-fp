
CPP_SRCS += \
../test/test.cpp \
../test/either.cpp \
../test/option.cpp \
../test/pipeline.cpp \
../test/sequence.cpp \
../test/try.cpp \
../test/uber.cpp \
../test/extensions.flow.cpp \
../test/extensions.vector.cpp \

CPP_DEPS += \
./test.d \
./either.d \
./option.d \
./pipeline.d \
./sequence.d \
./try.d \
./uber.d \
./extensions.flow.d \
./extensions.vector.d \

OBJS += \
./test.o \
./either.o \
./option.o \
./pipeline.o \
./sequence.o \
./try.o \
./uber.o \
./extensions.flow.o \
./extensions.vector.o \

%.o: ../test/%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I../src -O2 -g -Wall -c -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean: clean-root

clean-root:
	-$(RM) ./test.d ./test.o \
		./either.d ./either.o \
		./option.d ./option.o \
		./pipeline.d ./pipeline.o \
		./sequence.d ./sequence.o \
		./try.d ./try.o \
		./uber.d ./uber.o \
		./extensions.flow.d ./extensions.flow.o \
		./extensions.vector.d ./extensions.vector.o \


.PHONY: clean-root

