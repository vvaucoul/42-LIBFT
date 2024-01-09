/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:56:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:45:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "auto-allocator.h"
#include "binary-tree.h"
#include "ft_printf.h"

#include "classes/vector.h"

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      TYPES                                     ||
// ! ||--------------------------------------------------------------------------------||

typedef int (*CompareFunc)(const void *, const void *);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      ENUMS                                     ||
// ! ||--------------------------------------------------------------------------------||

typedef enum {
    false,
    true
} bool;

typedef enum { RED,
               BLACK
} Color;

// ! ||--------------------------------------------------------------------------------||
// ! ||                                   STRUCTURES                                   ||
// ! ||--------------------------------------------------------------------------------||

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

typedef struct s_dlist {
    void *data;
    struct s_dlist *next;
    struct s_dlist *prev;
} t_dlist;

typedef struct Node {
    void *data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    CompareFunc compare;
} RBTree;

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      ARRAY                                     ||
// ! ||--------------------------------------------------------------------------------||

bool ft_acof(const char **array, const char *str);
size_t ft_asize(const char **array);
size_t ft_alen(const char **array);
char **ft_acpy(const char **arr);
char **ft_split(const char *str, char del);

void sort_array(void *array, size_t size, size_t elem_size, CompareFunc compare);
void ft_reverse_array(void *array, size_t size, size_t elem_size);
int ft_max_in_array(void *array, size_t size, size_t elem_size);
int ft_min_in_array(void *array, size_t size, size_t elem_size);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      ALLOC                                     ||
// ! ||--------------------------------------------------------------------------------||

void *ft_calloc(size_t size, size_t count);
void ft_multifree(void **ptrs);
void ft_afree(void **ptr, size_t size);
void ft_free(void *ptr);
size_t ft_acol(const char **array);
void **ft_aalloc(size_t size, size_t size_x, size_t size_y);
void *ft_realloc(void *ptr, size_t newsize);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      SORT                                      ||
// ! ||--------------------------------------------------------------------------------||

void ft_qsort(void *array, int low, int high, size_t size, CompareFunc compare);
void ft_bsort(void *array, size_t size, size_t elem_size, CompareFunc compare);
void ft_isort(void *array, size_t size, size_t elem_size, CompareFunc compare);

void ft_sswap(void *a, void *b, size_t elem_size);
int is_sorted(void *array, size_t size, size_t elem_size, CompareFunc compare);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                COMPARE FUNCTIONS                               ||
// ! ||--------------------------------------------------------------------------------||

int compare_int(const void *a, const void *b);
int compare_char(const void *a, const void *b);
int compare_str(const void *a, const void *b);
int compare_double(const void *a, const void *b);
int compare_float(const void *a, const void *b);
int compare_long(const void *a, const void *b);
int compare_ulong(const void *a, const void *b);
int compare_llong(const void *a, const void *b);
int compare_ullong(const void *a, const void *b);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     MEMORY                                     ||
// ! ||--------------------------------------------------------------------------------||

void *ft_memset(void *ptr, int c, size_t len);
void *ft_memcpy(void *dst, const void *restrict src, size_t len);
void *ft_bzero(void *ptr, size_t len);
void *ft_memlower(void *ptr, size_t len);
void *ft_memupper(void *ptr, size_t len);
void *ft_memcrm(void *ptr, char c, size_t len);
void *ft_memsrm(void *ptr, char *str, size_t len);
void *ft_memchr(const void *ptr, int value, size_t len);
void *ft_memshr(const void *ptr, const void *cmp, size_t len, size_t nb);
void *ft_memalloc(void **dst, const void *ref, size_t size, size_t len);
void *ft_memmove(void *dest, const void *ptr, size_t len);
int ft_memcmp(const void *ptr, const void *ptr_cmp, size_t len);
int ft_memscmp(const void *ptr, const void *ptr_cmp, size_t len, size_t start);
void ft_swap(int *ptr, int *ptr_swap);
void ft_vswap(void **ptr, void **ptr2);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      CHAR                                      ||
// ! ||--------------------------------------------------------------------------------||

// - FT [Char Contain One Of] => Char contain one of char in str
bool ft_ccof(char c, const char *str);

bool ft_isascii(int c);
bool ft_isalpha(int c);
bool ft_isalnum(int c);
bool ft_isdigit(int c);
bool ft_isupper(int c);
bool ft_islower(int c);
bool ft_isspace(int c);

int ft_toupper(int c);
int ft_tolower(int c);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     STRINGS                                    ||
// ! ||--------------------------------------------------------------------------------||

// - FT [String Contain One Of] => String contain one of char in str
bool ft_scof(const char *str, const char *cmp);
bool ft_sncof(const char *str, const char *cmp, size_t len);

// - Length to Char c [Start with ptr str]
size_t ft_lentc(const char *str, char c);
size_t ft_lents(const char *str, const char *cmp);
char *ft_strdup(const char *str);
size_t ft_strlen(const char *str);
int ft_strcmp(const char *str, const char *str2);
int ft_strncmp(const char *str, const char *str2, size_t len);
char *ft_strcpy(char *dest, const char *str);
char *ft_strncpy(const char *str, size_t len);
char *ft_strchr(const char *str, int c);
char *ft_strjoin(const char *str, const char *join);
char *ft_fstrjoin(char *str, const char *join);
char *ft_strcjoin(char *str, char c);
char *ft_fstrcjoin(char *str, char c);
char *ft_multijoin(const char **array);
int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len);
char *ft_strtrim(char *str);
char *ft_strzap(char *str, const char *pat);
char *ft_strsplit(char *src, char **words, const char *sep);
char *ft_strremove(const char *str, char c);
// Replace pattern in src by new_pattern
char *ft_strrep(char *src, const char *pat, const char *new_pat);
// FT - [STR Remove Doublons] -> Remove doublons in string str
char *ft_strrdbls(const char *str, char c);
char *ft_substr(char *str, size_t start, size_t len);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     NUMBERS                                    ||
// ! ||--------------------------------------------------------------------------------||

size_t ft_nbrlen(int nbr);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     CONVERT                                    ||
// ! ||--------------------------------------------------------------------------------||

int ft_atoi(const char *str);
char *ft_itoa(int n);
char *ft_itoa_base(int nb, int base);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                   LINKED LIST                                  ||
// ! ||--------------------------------------------------------------------------------||

void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstadd_front(t_list **lst, t_list *new);
size_t ft_lstsize(t_list *lst);
t_list *ft_lstnew(void *data);
t_list *ft_lstlast(t_list *lst);
void ft_lstiter(t_list *lst, void (*f)(void *));
void ft_lstdelone(t_list *lst, void (*f)(void *));
void ft_lstclear(t_list **lst, void (*f)(void *));

// ! ||--------------------------------------------------------------------------------||
// ! ||                               DOUBLE LINKED LIST                               ||
// ! ||--------------------------------------------------------------------------------||

void ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void ft_dlstclear(t_dlist **lst, void (*del)(void *));
void ft_dlstdelone(t_dlist **alst, void (*del)(void *));
void ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist *ft_dlstlast(t_dlist *lst);
t_dlist *ft_dlstnew(void *data);
size_t ft_dlstsize(t_dlist *lst);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     RB TREE                                    ||
// ! ||--------------------------------------------------------------------------------||

Node *createNode(void *data, Color color, Node *parent);
RBTree *createRBTree();
void rotateLeft(RBTree *tree, Node *x);
void rotateRight(RBTree *tree, Node *y);
void fixInsert(RBTree *tree, Node *k);
void insert(RBTree *tree, void *key);
int is_left_child(Node *node);
void freeNode(Node *node);
void freeRBTree(RBTree *tree);
void printNode(Node *node);
void printRBTree(RBTree *tree);
void printRBTreeIndented(RBTree *tree);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                     PRINT                                      ||
// ! ||--------------------------------------------------------------------------------||

void ft_putchar(char c);
void ft_putendl(const char *str);
void ft_putstr(const char *str);
void ft_putnbr(int nbr);
void ft_putsarray(const char **array);

// ! ||--------------------------------------------------------------------------------||
// ! ||                                      TIME                                      ||
// ! ||--------------------------------------------------------------------------------||

void startTimer(clock_t *start);
double stopTimer(clock_t start);

#endif