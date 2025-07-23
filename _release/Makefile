RM := rm

-include sources.mk
-include subdir.mk
-include either/subdir.mk
-include extensions/subdir.mk
-include option/subdir.mk
-include pipeline/subdir.mk
-include sequence/subdir.mk
-include try/subdir.mk
-include types/subdir.mk

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

main-build: libtinyfp.so

libtinyfp.so: $(OBJS) $(USER_OBJS) makefile
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -W -shared -o "libtinyfp.so" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	-$(RM) libtinyfp.so
	-@echo ' '

.PHONY: all clean dependents main-build
