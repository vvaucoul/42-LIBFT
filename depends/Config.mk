# **************************************************************************** #
#                                                                              #
#    Config.mk - directories, sources, compiler flags                        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                    TOOLS                                    #
################################################################################

# NOT `?=`: GNU Make predefines CC ("cc"), AR ("ar") and ARFLAGS ("rv",
# verbose) itself as part of its built-in implicit-rule database, so a
# conditional assignment here would silently never take effect - command
# line overrides (`make CC=clang`) still win over `:=` regardless.
CC       := gcc
AR       := ar
ARFLAGS  := rcs
RM       ?= rm -f
MKDIR    ?= mkdir -p

################################################################################
#                                 DIRECTORIES                                 #
################################################################################

SRC_DIR      := srcs
INC_DIR      := includes
BUILD_DIR    := build
OBJ_DIR      := $(BUILD_DIR)/obj
TEST_DIR     := tests
TEST_OBJ_DIR := $(BUILD_DIR)/tests-obj

NAME      := 42_PCC_LIBFT.a
TEST_NAME := lft_test

################################################################################
#                                   SOURCES                                   #
################################################################################

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TEST_SRCS := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_DEPS := $(TEST_OBJS:.o=.d)

################################################################################
#                                    FLAGS                                    #
################################################################################

INCLUDES := -I$(INC_DIR)
DEPFLAGS := -MMD -MP

WARN := -Wall -Wextra
ifeq ($(STRICT),1)
WARN += -Werror
endif

# `make debug` (default)        -> -O0 -g3
# `make release RELEASE=1`      -> -O2, no debug info
ifeq ($(RELEASE),1)
OPT := -O2
else
OPT := -O0 -g3
endif

# Usage: make san SANITIZE=address,undefined  (asan/ubsan/san already set this)
SANITIZE ?=
SANFLAGS := $(if $(SANITIZE),-fsanitize=$(SANITIZE) -fno-omit-frame-pointer -g3,)

CFLAGS := $(WARN) $(OPT) $(SANFLAGS) $(EXTRA_CFLAGS)

# Auto-detected core count, only used by `make fast` (never forced by default)
NPROC := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
