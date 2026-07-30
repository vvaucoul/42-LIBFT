# 42-LIBFT

This is my libft from 42's Post Common Core, grown well past what the mandatory subject actually asks for. The original assignment wants a small set of string, memory and linked list helpers reimplemented in C89 under the school's norm. I kept the spirit of that (write your own primitives, don't lean on libc where the point is to build the thing yourself) but dropped the norm and the restrictions once the mandatory part was done, and kept adding modules whenever I wanted a piece of C infrastructure I'd normally just reach for in a bigger language: a red-black tree, a generic sort with an actual introsort behind it, a printf/scanf reimplementation, a small CLI argument parser, a conservative garbage collector, and so on.

Everything still compiles as a single static archive, `42_PCC_LIBFT.a`, with one public header, `libft.h`, pulling in every module.

## Building

```text
make            build the archive
make re         fclean then build
make fast       re, parallelized across every detected core
make debug      re with -O0 -g3 (this is already the default)
make release    re with -O2, no debug info
make strict     re with -Werror added on top of -Wall -Wextra
```

The source list is generated at build time with `find srcs -name '*.c'`, so dropping a new file into `srcs/` is enough to have it picked up; nothing in the Makefile needs touching.

## Testing

Tests live in `tests/` and run through a small homemade framework rather than a pulled-in dependency. Each `TEST(suite, name) { ... }` block registers itself automatically through a constructor, and every test runs in its own forked child with a five second alarm, so a segfault or an infinite loop in one test shows up as a single failing line instead of taking the whole suite down with it.

```text
make test          build and run every test
make test_verbose  same, but with -v for per-assertion output
make asan          rebuild and run under AddressSanitizer
make ubsan         rebuild and run under UndefinedBehaviorSanitizer
make san           both sanitizers at once
make valgrind      rebuild and run under valgrind's memcheck
```

The suite currently sits at 541 tests across every module, and stays green under `-Werror`, ASan+UBSan together, and valgrind with zero leaks. A GitHub Actions workflow rebuilds and re-runs everything on every push.

Worth calling out for anyone poking at the `gc` module specifically: ASan's stack use-after-return detection moves local variables off the real stack, which breaks conservative stack scanning outright. `make san` compiles with `--param=asan-use-after-return=0` for exactly that reason (see `depends/Config.mk`), otherwise `gc_collect()` would be scanning the wrong memory entirely.

## Layout

Each module gets its own directory under `srcs/` and, where the API is more than a couple of functions, its own header under `includes/` (the smallest, flattest modules share `libft.h` directly instead). Independent utility functions get one file per function; modules built around shared internal state, like the red-black tree, the logger, the sort engine, the parser, the printf/scanf engine or the garbage collector, are split by concern instead, with a private `_internal.h` header where the pieces need to share structs that callers never should.

Here's what each directory under `srcs/` actually is.

| Module | What it is |
| --- | --- |
| 📦 `alloc` | Allocation itself: calloc, a 2D allocator, realloc, batch-free helpers |
| 🔢 `array` | NULL-terminated and generic comparator-based array utilities |
| 🧠 `memory` | `<string.h>`-style buffer primitives, rebuilt from scratch |
| 🔤 `char` | `<ctype.h>` equivalents |
| 📝 `string` | Duplication, comparison, joining, splitting, trimming, search, case conversion |
| 🧮 `number` | abs, min/max/clamp, gcd/lcm, primality |
| 🔁 `convert` | String/number conversions: the atoi and itoa families |
| 🔀 `sort` | Five sorting algorithms behind one comparator convention |
| 🔗 `linked_list` | Singly linked list |
| 🔗 `dlinked_list` | Doubly linked list |
| 🌳 `rbtree` | Red-black tree |
| 🌳 `binary-tree` | Plain, non-balancing generic binary tree |
| 🗃️ `containers` | Vector, stack, queue, set, map, pair |
| 🖨️ `print` | Minimal 42 output primitives |
| 🖥️ `stdio` | Full printf/scanf family |
| 📁 `file` | File and directory operations |
| 📋 `logger` | Leveled logger |
| ⚙️ `parser` | Getopt-style CLI argument parser |
| 🔐 `crypto` | Hashing, base64, a XOR cipher, a CSPRNG wrapper, toy RSA |
| ♻️ `gc` | Conservative mark-and-sweep garbage collector |
| ⏱️ `time` | CPU timing, wall-clock timing, sleeping, date formatting |

## A note on naming

A few functions still carry names from when this was a strict 42 assignment (`ft_ccof`, `ft_lentc`, `ft_scof` and similar abbreviations that made more sense under a stricter naming convention than they do in isolation). I left them as they are rather than rename them purely for cosmetics; every non-obvious one has a short comment next to its prototype in `libft.h` explaining what it actually does.
