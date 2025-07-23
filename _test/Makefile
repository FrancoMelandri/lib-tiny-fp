RM := rm

-include sources.mk
-include subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

BUILD_ARTIFACT_NAME := libtinyfp
BUILD_ARTIFACT_EXTENSION := so
BUILD_ARTIFACT_PREFIX := lib
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

all: main-build

main-build: libtinyfp-tests

libtinyfp-tests: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"../_release" -o "libtinyfp-tests" $(OBJS) $(USER_OBJS) $(LIBS) -ltinyfp
	@echo 'Finished building target: $@'
	@echo ' '

test: all
	@echo 'Running test suite...'
	@echo ' '
	LD_LIBRARY_PATH=../_release valgrind --leak-check=yes --error-exitcode=1 ./libtinyfp-tests 
	@echo 'Finished running test suite.'

clean:
	-$(RM) libtinyfp-tests
	-@echo ' '

.PHONY: all clean dependents main-build
