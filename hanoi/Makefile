CFLAGS = -I..
TARGETS = hanoi_coroutine hanoi_void_coroutine
TARGET_TESTS = $(addsuffix _test,$(TARGETS))
GENERATOR = hanoi_generator.py
GENERATOR_TEST = $(addsuffix _test,$(GENERATOR))
CHECKER = hanoi_check.py

default: $(TARGET_TESTS)

targets: $(TARGETS)

test_checker: $(GENERATOR_TEST)

all: default test_checker

clean:
	$(RM) $(TARGETS)

define DECLARE_test
$(1)_test : $(1) $(CHECKER)
	./$(1) | ./$(CHECKER)
endef

.PHONY: default targets test_checker all clean $(TARGET_TESTS) $(GENERATOR_TEST)

$(foreach prog,$(TARGETS) $(GENERATOR),$(eval $(call DECLARE_test,$(prog))))
