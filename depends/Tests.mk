# **************************************************************************** #
#                                                                              #
#    Tests.mk - test suite build/run rules                                    #
#                                                                              #
# **************************************************************************** #

TOTAL_TEST_OBJS := $(words $(TEST_OBJS))
TEST_COUNT_FILE := $(TEST_OBJ_DIR)/.count

define TEST_COMPILE_STEP
$(MKDIR) $(dir $@) $(dir $(TEST_COUNT_FILE))
n=$$(flock $(TEST_COUNT_FILE).lock -c ' \
	c=$$(cat $(TEST_COUNT_FILE) 2>/dev/null || echo 0); \
	c=$$((c + 1)); \
	echo $$c > $(TEST_COUNT_FILE); \
	echo $$c'); \
printf "$(_CLEAR_LINE)$(_BOLD)$(_LPURPLE)[%3d/%-3d]$(_END) $(_WHITE)CC$(_END) %s\n" "$$n" "$(TOTAL_TEST_OBJS)" "$<"
$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@
endef

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@$(TEST_COMPILE_STEP)

$(TEST_NAME): $(NAME) $(TEST_OBJS)
	@$(RM) $(TEST_COUNT_FILE) $(TEST_COUNT_FILE).lock
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o $(TEST_NAME)
	@printf "$(_BOLD)$(_LCYAN)==>$(_END) $(_WHITE)%s $(_LGREEN)compiled successfully$(_END) $(_LGREEN)✓$(_END)\n" $(TEST_NAME)

## test: build and run the full unit test suite (exit code reflects pass/fail)
test: $(TEST_NAME)
	@./$(TEST_NAME)

## test_verbose: same as test, with -v passed through to the test binary
test_verbose: $(TEST_NAME)
	@./$(TEST_NAME) -v

## re_test: fclean then build+run tests
re_test: fclean test

## asan: rebuild and run tests under AddressSanitizer
asan:
	@$(MAKE) --no-print-directory SANITIZE=address fclean test

## ubsan: rebuild and run tests under UndefinedBehaviorSanitizer
ubsan:
	@$(MAKE) --no-print-directory SANITIZE=undefined fclean test

## san: rebuild and run tests under ASan + UBSan together
san:
	@$(MAKE) --no-print-directory SANITIZE=address,undefined fclean test

## valgrind: rebuild and run tests under valgrind's memcheck
valgrind: fclean $(TEST_NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_NAME)

-include $(TEST_DEPS)

.PHONY: test test_verbose re_test asan ubsan san valgrind
