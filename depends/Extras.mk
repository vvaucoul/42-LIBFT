# **************************************************************************** #
#                                                                              #
#    Extras.mk - editor tooling, norm check, self-documenting help            #
#                                                                              #
# **************************************************************************** #

## compdb: generate compile_commands.json for clangd/VSCode intellisense
compdb:
	@printf "$(_LYELLOW)Generating compile_commands.json$(_END)\n"
	@printf '[\n' > compile_commands.json
	@first=1; \
	for f in $(SRCS) $(TEST_SRCS); do \
		if [ $$first -eq 0 ]; then printf ',\n' >> compile_commands.json; fi; \
		first=0; \
		printf '  {\n    "directory": "%s",\n    "file": "%s",\n    "command": "%s %s %s -c %s"\n  }' \
			"$$(pwd)" "$$f" "$(CC)" "$(CFLAGS) $(INCLUDES)" "" "$$f" >> compile_commands.json; \
	done
	@printf '\n]\n' >> compile_commands.json
	@printf "$(_LGREEN)-> compile_commands.json ($(words $(SRCS) $(TEST_SRCS)) entries)$(_END)\n"

## norm: run the 42 norminette over srcs/ and includes/ if it's installed
norm:
	@if command -v norminette >/dev/null 2>&1; then \
		norminette $(SRC_DIR) $(INC_DIR); \
	else \
		printf "$(_LRED)norminette not found in PATH - skipping$(_END)\n"; \
	fi

## help: list available targets with their one-line description
help:
	@printf "$(_BOLD)$(_LCYAN)42_PCC_LIBFT - available targets$(_END)\n\n"
	@sed -n 's/^## \([A-Za-z_-]*\): \(.*\)/\1|\2/p' $(MAKEFILE_LIST) | \
		awk -F '|' '{printf "  $(_LGREEN)%-14s$(_END) %s\n", $$1, $$2}'
	@printf "\n$(_BOLD)Variables:$(_END) STRICT=1 (-Werror)  RELEASE=1 (-O2)  SANITIZE=address,undefined\n"

.PHONY: compdb norm help
