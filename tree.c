/*
 *
 * tree.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the tree datatype
 *
 * implements a red-black tree
 */

#include "tree.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/* initialize a nil node */
static t_node *nil_(t_node *root);

/* free the memory allocated for a node */
static void free_t_node(t_node *n);

/* fixup after insertion */
static void insert_fixup(tree *t, t_node *x);

/* fixup after deletion */
static void delete_fixup(tree *t, t_node *x);

/* find the successor of a t_node */
static t_node *tree_successor(tree *t, t_node *x);

/* find the minimum of a subtree with root in x */
static t_node *tree_minimum(tree *t, t_node *x);

/* left-rotate a node */
static void left_rotate(tree *t, t_node *x);

/* right-rotate a node */
static void right_rotate(tree *t, t_node *y);

/* free a sub_tree */
static void free_sub_tree(tree *t, t_node *n);
/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/

/* 
 * function: t_node_
 *
 * construct a t_node 
 *   val: value (item)
 *   l: ptr to left child
 *   r: ptr to right child
 *   p: ptr to parent
 *
 * return: ptr to t_node
 */
t_node *t_node_(item val, t_node *l, t_node *r, t_node *p, colour c)
{
  t_node *n = (t_node *) malloc(sizeof(t_node));

  val(*n) = val;
  left(*n) = l;
  right(*n) = r;
  parent(*n) = p;
  colour(*n) = c;

  return n;
}


/*
 * function: nil_
 *
 * construct a nil
 *   root: ptr to root of the tree
 *
 * return: ptr to t_node (nil)
 */
static t_node *nil_(t_node *root)
{
  t_node *nil = t_node_(NULL, root, root, NULL, BLACK);
  return nil;
}


/* 
 * function: free_t_node
 *
 * destructor for t_node datatype
 * frees the memory allocated for a node 
 *   n: ptr to node
 */
static void free_t_node(t_node *n)
{
  if (n != NULL) {
    free_item(val(*n));
    free(n);
    n = NULL;
  }
}

/* 
 * function: tree_
 *
 * tree datatype constructor
 * 
 * return: ptr to tree
 *   initializes nil and an empty root
 */
tree *tree_()
{
  tree *t = (tree *) malloc(sizeof(tree));

  nil(*t) = nil_(NULL);
  root(*t) = t_node_(NULL, nil(*t), nil(*t), nil(*t), BLACK);

  return t;
}


/* 
 * function: is_nil
 *
 * t_node datatype test
 * check if a node is nil of a tree
 *   n: ptr to node
 * 
 * return: bool
 */
bool is_nil(tree *t, t_node *n)
{
  return n == nil(*t);
}


/* 
 * function: is_root
 *
 * t_node datatype test
 * check if a node is root of a tree
 *   t: ptr to tree
 *   n: ptr to node
 * 
 * return: bool
 */
bool is_root(tree *t, t_node *n)
{
  return n == root(*t);
}

/* 
 * function: empty_tree
 *
 * test for tree datatype
 * verifies if the tree is empty
 *   a: ptr to tree
 *
 * return: bool
 */
bool empty_tree(tree *t)
{
  return val(*root(*t)) == NULL;
}

/* 
 * function: insert_t_node
 *
 * modifier for tree datatype
 * inserts a new item in the tree
 *   t: ptr to tree
 *   val: new item
 */
void insert_t_node(tree *t, item val)
{
  t_node *x, *y;
  t_node *z;
  
  if (empty_tree(t)) {
    val(*root(*t)) = val;
    return;
  }

  x = root(*t);
  y = nil(*t);

  while (!is_nil(t, x)) {
    y = x;
    if ( less_key( get_key(val), get_key(val(*y)) ) ) {
      x = left(*x);
    }
    else {
      x = right(*x);
    }
  }

  /* colour is red by default, fixup then updates */
  z = t_node_(val, nil(*t), nil(*t), y, RED);
  if ( less_key( get_key(val(*z)), get_key(val(*y)) ) ) {
    left(*y) = z;
  }
  else {
    right(*y) = z;
  }

  insert_fixup(t, z);
}


/*
 * function: insert_fixup
 *
 * auxiliar function, balances tree after insertion
 *   t: ptr to tree
 *   x: ptr to inserted node
 *
 */
static void insert_fixup(tree *t, t_node *x)
{
  t_node *y;
  while (!is_root(t, x) && colour(*parent(*x)) == RED) {
    if (parent(*x) == left(*parent(*parent(*x)))) {
      y = right(*parent(*parent(*y)));

      if (colour(*y) == RED) {
        colour(*parent(*x)) = BLACK;
        colour(*y) = BLACK;
        colour(*parent(*parent(*x))) = RED;
        x = parent(*parent(*x));
      }
      else {
        if (x == right(*parent(*x))) {
          x = parent(*x);
          left_rotate(t, x);
        }

        colour(*parent(*x)) = BLACK;
        colour(*parent(*parent(*x))) = RED;
        right_rotate(t, parent(*parent(*x)));
      }
    }
    else {
      y = left(*parent(*parent(*y)));

      if (colour(*y) == RED) {
        colour(*parent(*x)) = BLACK;
        colour(*y) = BLACK;
        colour(*parent(*parent(*x))) = RED;
        x = parent(*parent(*x));
      }
      else {
        if (x == left(*parent(*x))) {
          x = parent(*x);
          right_rotate(t, x);
        }

        colour(*parent(*x)) = BLACK;
        colour(*parent(*parent(*x))) = RED;
        left_rotate(t, parent(*parent(*x)));
      }
    }
  }
}


/*
 * function: delete_t_node 
 *
 * modifier of the tree datatype
 *   t: ptr to tree
 *   z: ptr to node to delete
 *
 * return: key of the removed node
 */
key_t delete_t_node(tree* t, t_node *z)
{
  t_node *x, *y;
  key_t rmd_key = get_key(val(*z));

  if (is_nil(t, left(*z)) || is_nil(t, right(*z))) {
    y = z;
  }
  else {
    y = tree_successor(t, z);
  }

  if (!is_nil(t, left(*y))) {
    x = left(*y);
  }
  else {
    x = right(*y);
  }

  parent(*x) = parent(*y);
  if (is_root(t, parent(*y))) {
    root(*t) = x;
  }
  else {
    if (y == left(*parent(*(y)))) {
      left(*parent(*y)) = x;
    }
    else {
      right(*parent(*y)) = x;
    }
  }

  if (y != z) {
    val(*z) = val(*y);
  }
  if (colour(*y) == BLACK) {
    delete_fixup(t, x);
  }

  free_t_node(y);
  return rmd_key;
}


/* 
 * function: delete_fixup 
 * 
 * auxiliar function, balances tree after deletion
 *   t: ptr to tree
 *   x: ptr to deleted node
 */
static void delete_fixup(tree *t, t_node *x)
{
  t_node *w;
  while (!is_root(t, x) && colour(*x) == BLACK) {
    if (x == left(*parent(*x))) {
      w = right(*parent(*x));
      if (colour(*w) == RED) {
        colour(*w) = BLACK;
        left_rotate(t, parent(*x));
        w = right(*parent(*x));
      }
      if (colour(*left(*w)) == BLACK && colour(*right(*w)) == BLACK) {
        colour(*w) = RED;
        x = parent(*x);
      }
      else {
        if (colour(*right(*w)) == BLACK) {
          colour(*w) = RED;
          right_rotate(t, w);
          w = right(*parent(*x));
        }
        colour(*w) = colour(*parent(*x));
        colour(*parent(*x)) = BLACK;
        colour(*right(*w)) = BLACK;
        left_rotate(t, parent(*x));
      }
    }
    else{
      w = right(*parent(*x));
      if (colour(*w) == RED) {
        colour(*w) = BLACK;
        left_rotate(t, parent(*x));
        w = right(*parent(*x));
      }
      if (colour(*left(*w)) == BLACK && colour(*right(*w)) == BLACK) {
        colour(*w) = RED;
        x = parent(*x);
      }
      else {
        if (colour(*right(*w)) == BLACK) {
          colour(*w) = RED;
          right_rotate(t, w);
          w = right(*parent(*x));
        }
        colour(*w) = colour(*parent(*x));
        colour(*parent(*x)) = BLACK;
        colour(*right(*w)) = BLACK;
        left_rotate(t, parent(*x));
      }
    }
  }
  colour(*x) = BLACK;
}


/*
 * function: tree_successor
 *
 * computes the successor of a node in a tree
 *   t: ptr to tree
 *   x: ptr to t_node
 *
 * a successor is either the minimum of the right subtree or the "leftmost" 
 * root of the subtree that contains the node. That is, it bactraces the tree 
 * only by right edges.
 *
 * return: t_node ptr
 */
static t_node *tree_successor(tree *t, t_node *x)
{
  t_node *y;

  if (!is_nil(t, right(*x))) 
    return tree_minimum(t, right(*x));

  y = parent(*x);
  while (!is_nil(t, y) && x == right(*y)) {
    x = y;
    y = parent(*x);
  }

  return y;
}


/*
 * function: tree_minimum
 *
 * computes the minimum value of a sub-tree 
 *   t: ptr to tree
 *   x: ptr to t_node
 *
 * returns: minimum t_node of the subtree with root in x
 */
static t_node *tree_minimum(tree *t, t_node *x)
{
  for (; !is_nil(t, left(*x)); x = left(*x));
  return x;
}


/* 
 * function: left_rotate 
 *
 * modifier for tree datatype
 * given a tree and a node, rotates the subtree starting
 * in the node to the left
 *   t: ptr to tree
 *   x: ptr to node
 *
 * graphical description
 *                
 *    x                            y
 *   / \                          / \
 *  a   y          ==>           x   c
 *     / \                      / \
 *    b   c                    a   b
 */
static void left_rotate(tree *t, t_node *x)
{
  t_node *y = right(*x);
  right(*x) = left(*y);
  if (!is_nil(t, left(*y))) 
    parent(*left(*y)) = x;

  parent(*y) = parent(*x);
  if (is_root(t, x)) {
    root(*t) = y;
  }
  else if (x == left(*parent(*x))) {
    left(*parent(*x)) = y;
  }
  else {
    right(*parent(*x)) = y;
  }

  left(*y) = x;
  parent(*x) = y;
}


/* 
 * function: right_rotate 
 *
 * modifier for tree datatype
 * given a tree and a node, rotates the subtree starting
 * in the node to the rigth
 *   t: ptr to tree
 *   y: ptr to node
 *
 * graphical description
 *                
 *      y                            x
 *     / \                          / \
 *    x   c          ==>           a   y
 *   / \                              / \
 *  a   b                            b   c
 */
static void right_rotate(tree *t, t_node *y)
{
  t_node *x = left(*y);
  left(*y) = right(*x);

  if (!is_nil(t, right(*x))) 
    parent(*right(*x)) = y;

  parent(*x) = parent(*y);
  if (is_root(t, y)) {
    root(*t) = x;
  }
  else if (y == left(*parent(*y))) {
    left(*parent(*y)) = x;
  }
  else {
    right(*parent(*y)) = x;
  }

  right(*x) = y;
  parent(*y) = x;
}


/* 
 * function: search_by_key
 * 
 * search for a node with a certain key
 *   t: ptr to tree
 *   key: key to search for
 * 
 * return: ptr to t_node whith the key
 *   NULL if not found
 */
t_node *search_by_key(tree *t, key_t key)
{
  t_node *x = root(*t);
  key_t k;

  while (!is_nil(t, x)) {
    k = get_key(val(*x));
    if (eq_key(key, k)) {
      return x;
    }
    else if (less_key(key, get_key(val(*x)))) {
      x = left(*x);
    }
    else {
      x = right(*x);
    }
  }

  return NULL;
}


/* 
 * function: free_tree 
 *
 * destructor for tree datatype
 *   t: ptr to tree
 */
void free_tree(tree *t)
{
  if (t != NULL) {
    free_sub_tree(t, root(*t));
    free_t_node(nil(*t));
    free(t);
    t = NULL; 
  }
}


/*
 * function: free_sub_tree
 *
 * frees a sub-tree and the root of that sub-tree
 *   t: ptr to tree
 *   n: ptr to root of the sub-tree
 */
static void free_sub_tree(tree *t, t_node *n)
{
  if (!is_nil(t, n)) {
    free_sub_tree(t, left(*n));
    free_sub_tree(t, right(*n));
    free_t_node(n);
  }
}
