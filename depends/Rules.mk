# **************************************************************************** #
#                                                                              #
#    Rules.mk - library build rules (out-of-tree, parallel-safe progress)     #
#                                                                              #
# **************************************************************************** #

TOTAL_OBJS := $(words $(OBJS))
COUNT_FILE := $(OBJ_DIR)/.count

# flock-guarded counter so `make -jN` prints correct "[i/total]" progress
# instead of racing (srcs/ itself is never touched - everything lands in
# $(BUILD_DIR), so `make fclean` is just one `rm -rf`).
define COMPILE_STEP
$(MKDIR) $(dir $@) $(dir $(COUNT_FILE))
n=$$(flock $(COUNT_FILE).lock -c ' \
	c=$$(cat $(COUNT_FILE) 2>/dev/null || echo 0); \
	c=$$((c + 1)); \
	echo $$c > $(COUNT_FILE); \
	echo $$c'); \
printf "$(_CLEAR_LINE)$(_BOLD)$(_LGREEN)[%3d/%-3d]$(_END) $(_WHITE)CC$(_END) %s\n" "$$n" "$(TOTAL_OBJS)" "$<"
$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(COMPILE_STEP)

## all: build the static library (default goal)
all: $(NAME)

$(NAME): $(OBJS)
	@$(RM) $(COUNT_FILE) $(COUNT_FILE).lock
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "$(_BOLD)$(_LCYAN)==>$(_END) $(_WHITE)%s $(_LGREEN)compiled successfully$(_END) $(_LGREEN)✓$(_END)\n" $(NAME)

## clean: remove build/ (object and dependency files)
clean:
	@$(RM) -r $(BUILD_DIR)
	@printf "$(_LYELLOW)Removed build artifacts ($(BUILD_DIR))$(_END)\n"

## fclean: clean + remove the library and test binary
fclean: clean
	@$(RM) $(NAME) $(TEST_NAME) compile_commands.json
	@printf "$(_LYELLOW)Removed $(NAME) and $(TEST_NAME)$(_END)\n"

## re: fclean then all
re: fclean all

## fast: re, parallelized across all detected CPU cores
fast:
	@$(MAKE) --no-print-directory -j$(NPROC) all

## debug: re, with -O0 -g3 (the default - alias for clarity)
debug:
	@$(MAKE) --no-print-directory re

## release: re, with -O2 and no debug info
release:
	@$(MAKE) --no-print-directory RELEASE=1 re

## strict: re, with -Werror added
strict:
	@$(MAKE) --no-print-directory STRICT=1 re

-include $(DEPS)

.PHONY: all clean fclean re fast debug release strict
