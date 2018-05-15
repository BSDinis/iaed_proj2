/*
 *
 * lnkd_list.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for lnkd_list.c
 *
 * implements a (doubly) linked list
 *
 * note on implementation: two dummy nodes (head and tail) are used.
 */

#ifndef LNKD_LIST_H
#define LNKD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "item.h"

/* define l_node */
typedef struct _l_node {
  item val;
  struct _l_node *prev, *next;
} l_node;

/* selectors */
#define val(a) ((a).val)
#define prev(a) ((a).prev)
#define next(a) ((a).next)

/* doubly linked list */
typedef struct {
  l_node *head, *tail;
} lnkd_list;

/* selectors */
#define head(a) ((a).head)
#define tail(a) ((a).tail)

/* initialize l_node */
l_node *l_node_(item val, l_node *prev, l_node *next);

/* tests: test if a node is head or tail */
bool is_head(l_node *n);
bool is_tail(l_node *n);

/* goes to the next node: a verification if the node is a tail is needed */
l_node *go_next(l_node *n);

/* goes to the prev node: a verification if the node is a head is needed */
l_node *go_prev(l_node *n);

/* insert l_node after: returns false if src is tail */
bool insert_l_node_after(l_node *src, item val);

/* insert l_node before: returns false if src is head */
bool insert_l_node_before(l_node *src, item val);

/* remove l_node: returns false if src is head or tail */
bool remove_l_node(l_node *src);

/* free the memory allocated for a node */
void free_l_node(l_node *n);

/* initialize list */
lnkd_list *lnkd_list_();

/* check if a list is empty */
bool empty_list(lnkd_list *a);

/* add an element at the beginning of the linked list */
void add_at_beginning(lnkd_list *l, item val);

/* add an element at the end of the linked list */
void add_at_end(lnkd_list *l, item val);

/* free a list (and all its elements) */
void free_lnkd_list(lnkd_list *l);

#endif /* !LNKD_LIST_H */
