# **************************************************************************** #
#                                                                              #
#    Config.mk - directories, sources, compiler flags                        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                    TOOLS                                    #
################################################################################

# `:=` not `?=`: Make's built-in implicit rules already predefine these,
# so `?=` would never take effect; `make CC=clang` still overrides `:=`.
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
# ASan's use-after-return detection moves stack locals to a heap-backed
# "fake stack", which the gc module's conservative stack scan can't see -
# disabled here so gc_collect() keeps finding real stack-resident roots.
SANFLAGS += $(if $(findstring address,$(SANITIZE)),--param=asan-use-after-return=0,)

CFLAGS := $(WARN) $(OPT) $(SANFLAGS) $(EXTRA_CFLAGS)

# Auto-detected core count, only used by `make fast` (never forced by default)
NPROC := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
