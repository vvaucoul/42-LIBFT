# 42-LIBFT

Post Common Core - LIBFT (Without restrictions &amp; without norme)

### LIBFT - FUNCTIONS

> ARRAY

```C
- bool ft_acof(const char **array, const char *str);
- size_t ft_asize(const char **array);
- size_t ft_alen(const char **array);
- char **ft_acpy(const char **arr);
- char **ft_split(const char *str, char del);
```

> ALLOCATIONS

```C
- void *ft_calloc(size_t size, size_t count);
- void ft_multifree(void **ptrs);
- void ft_afree(void **ptr);
- void ft_free(void *ptr);
- size_t ft_acol(const char **array);
- void **ft_aalloc(size_t size, size_t size_x, size_t size_y);
- void *ft_realloc(void *ptr, size_t newsize);
```

> MEMORY

```C
- void *ft_memset(void *ptr, int c, size_t len);
- void *ft_memcpy(void *dst, const void *restrict src, size_t len);
- void *ft_bzero(void *ptr, size_t len);
- void *ft_memlower(void *ptr, size_t len);
- void *ft_memupper(void *ptr, size_t len);
- void *ft_memcrm(void *ptr, char c, size_t len);
- void *ft_memsrm(void *ptr, char *str, size_t len);
- void *ft_memchr(const void *ptr, int value, size_t len);
- void *ft_memshr(const void *ptr, const void *cmp, size_t len, size_t nb);
- void *ft_memalloc(void **dst, const void *ref, size_t size, size_t len);
- void *ft_memmove(void *dest, const void *ptr, size_t len);
- int ft_memcmp(const void *ptr, const void *ptr_cmp, size_t len);
- int ft_memscmp(const void *ptr, const void *ptr_cmp, size_t len, size_t start);
- void ft_swap(int *ptr, int *ptr_swap);
- void ft_vswap(void **ptr, void **ptr2);
```

> CHAR

```C
- bool ft_ccof(char c, const char *str);
- bool ft_isascii(int c);
- bool ft_isalpha(int c);
- bool ft_isalnum(int c);
- bool ft_isdigit(int c);
- bool ft_isupper(int c);
- bool ft_islower(int c);
- bool ft_isspace(int c);
- int ft_toupper(int c);
- int ft_tolower(int c);
```

> STRINGS

```C
- bool ft_scof(const char *str, const char *cmp);
- bool ft_sncof(const char *str, const char *cmp, size_t len);
- size_t ft_lentc(const char *str, char c);
- size_t ft_lents(const char *str, const char *cmp);
- char *ft_strdup(const char *str);
- size_t ft_strlen(const char *str);
- int ft_strcmp(const char *str, const char *str2);
- int ft_strncmp(const char *str, const char *str2, size_t len);
- char *ft_strcpy(const char *str);
- char *ft_strncpy(const char *str, size_t len);
- char *ft_strchr(const char *str, int c);
- char *ft_strjoin(const char *str, const char *join);
- char *ft_fstrjoin(char *str, const char *join);
- char *ft_strcjoin(char *str, char c);
- char *ft_fstrcjoin(char *str, char c);
- char *ft_multijoin(const char **array);
- int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len);
- char *ft_strtrim(char *str);
- char *ft_strzap(char *str, const char *pat);
- char *ft_strsplit(char *src, char **words, const char *sep);
- char *ft_strremove(const char *str, char c);
- char *ft_strrep(char *src, const char *pat, const char *new_pat);
- char *ft_strrdbls(const char *str, char c);
- char *ft_substr(char *str, size_t start, size_t len);
- char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
```

> NUMBERS

```C
- size_t ft_nbrlen(int nbr);
```

> CONVERT

```C
- int ft_atoi(const char *str);
- char *ft_itoa(int n);
- char *ft_itoa_base(int nb, int base);
```

> LINKED LIST

```C
- void ft_lstadd_back(t_list **lst, t_list *new);
- void ft_lstadd_front(t_list **lst, t_list *new);
- size_t ft_lstsize(t_list *lst);
- t_list *ft_lstnew(void *data);
- t_list *ft_lstlast(t_list *lst);
- void ft_lstiter(t_list *lst, void (*f)(void *));
- void ft_lstdelone(t_list *lst, void (*f)(void *));
- void ft_lstclear(t_list **lst, void (*f)(void *));
```

> PRINT

```C
- void ft_putchar(char c);
- void ft_putendl(const char *str);
- void ft_putstr(const char *str);
- void ft_putnbr(int nbr);
- void ft_putsarray(const char **array);
```

### FT_PRINTF

- Lightweight printf

> Supported Flags
> - %
> - d
> - i
> - s

```C
- int ft_printf(const char *str, ...);
```

### AUTO-ALLOCATOR

- Library to auto allocate and free all memory used.

> Usage: 

- Use the function 'AA_allocate_ptr' to get a new ptr. Or, use the function 'AA_push_ptr' to push your own ptr.
- You can delete your ptr with the function 'AA_free_ptr'.
- Also, you can delete all your ptrs with the function 'AA_free' at the end of your program.

```C
- void *AA_allocate_ptr(size_t size, size_t var_size);
- void AA_free_ptr(void *ptr);
- void AA_push_ptr(void *ptr);
- void AA_free(void);
- size_t AA_get_node_size(void);
- void AA_print_nodes(void);
```

### BINARY-TREE

- Simple binary-tree, faster than linked list.

```C
- T_NODE *BT_new_node(void *data);
- T_NODE *BT_insert_node(T_NODE *root, void *data);
- T_NODE *BT_get_root(void);
- size_t BT_get_node_size(void);
- void BT_display_nodes(T_NODE *node);
- void *BT_delete_node(T_NODE *root, void *data, int delete_data);
- void BT_delete_tree(T_NODE *root, int delete_data);
```

