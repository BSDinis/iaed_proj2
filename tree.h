/*
 *
 * tree.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for tree.c
 *
 * implements a red-black tree 
 */

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "item.h"

/* red-black flag */
typedef enum {RED = 0, BLACK = 1} colour;

#define negate_colour(a) ((a == RED) ? BLACK : RED)

/* define t_node */
typedef struct _t_node {
  item val;
  struct _t_node *l, *r, *p;
  colour c;
} t_node;

/* selectors */
#define val(a) ((a).val)
#define left(a) ((a).l)
#define right(a) ((a).r)
#define parent(a) ((a).p)
#define colour(a) ((a).c)

/* red-black tree */
typedef struct {
  t_node *root, *nil;
} tree;

/* selectors */
#define root(a) ((a).root)
#define nil(a) ((a).nil)

/* initialize t_node */
t_node *t_node_(item val, t_node *l, t_node *r, t_node *p, colour c);

/* initialize tree */
tree *tree_();

/* tests: test if a node is root or nil */
bool is_root(tree *t, t_node *n);
bool is_nil(tree *t, t_node *n);

/* check if a tree is empty */
bool empty_tree(tree *a);

/* insert an element */
void insert_t_node(tree *t, item val);

/* delete t_node */
key_t delete_t_node(tree *t, t_node *z);

/* return an item given a certain key */
item search_by_key(tree *t, key_t key);

/* free a tree */
void free_lnkd_list(tree *t);

#endif /* !TREE_H */
