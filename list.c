/*
 *
 * list.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the list datatype
 */

#include "list.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/

/* 
 * function: l_node_
 *
 * construct a l_node 
 *   val: value (item)
 *   prev: ptr to preceding node
 *   next: ptr to the next node
 *
 * return: ptr to l_node
 */
l_node *l_node_(l_item val, l_node *prev, l_node *next)
{
  l_node *n = (l_node *) malloc(sizeof(l_node));
  val(*n) = val;
  prev(*n) = prev;
  next(*n) = next;
  return n;
}


/* 
 * function: is_head
 *
 * checks if a node is a head of a linked list
 *   n: ptr to node
 *
 * return: true if n is head
 */
bool is_head(l_node *n)
{
  return prev(*n) == NULL;
}


/* 
 * function: is_tail
 *
 * checks if a node is a tail of a linked list
 *   n: node
 *
 * return: true if n is tail
 */
bool is_tail(l_node *n)
{
  return next(*n) == NULL;
}


/*
 * function: go_next
 *
 * advances to the next node in the linked list
 *   n: node
 *
 * return: next node
 *   if the node is a tail, return itself
 */
l_node *go_next(l_node *n)
{
  return (next(*n) == NULL) ? n : next(*n);
}

/*
 * function: go_prev
 *
 * returns to the previous node in the linked list
 *   n: node
 *
 * return: next node
 *   if the node is a head, return itself
 */
l_node *go_prev(l_node *n)
{
  return (prev(*n) == NULL) ? n : prev(*n);
}

/* 
 * function: insert_l_node_after
 *
 * inserts a node after the src
 *   src: ptr to node  
 *   val: value of the node to be inserted
 *
 * return: false if the src is a tail
 */
bool insert_l_node_after(l_node *src, l_item val)
{
  l_node *new_node;

  if (is_tail(src)) 
    return false;

  new_node = l_node_(val, src, next(*src));

  next(*src) = new_node;
  prev(*next(*new_node)) = new_node;

  return true;
}


/* 
 * function: insert_l_node_before
 *
 * inserts a node before the src
 *   src: ptr to node  
 *   new_node: ptr to node to be inserted
 *
 * return: false if the src is a head
 */
bool insert_l_node_before(l_node *src, l_item val)
{
  l_node *new_node;

  if (is_head(src))
    return false;

  new_node = l_node_(val, prev(*src), src);

  prev(*src) = new_node;
  next(*prev(*new_node)) = new_node;

  return true;
}


/* 
 * function: remove_l_node
 *
 * removes a l_node
 *   src: ptr to node  
 *
 * return: false if the src is a head or tail
 */
bool remove_l_node(l_node *src)
{
  if (is_head(src) || is_tail(src)) 
    return false;

  next(*prev(*src)) = next(*src);
  prev(*next(*src)) = prev(*src);

  free_l_node(src);
  free(src);

  return true;
}


/* 
 * function: remove_l_node
 *
 * free the memory allocated for a node 
 *   n: ptr to node
 */
void free_l_node(l_node *n)
{
  free_l_item(val(*n));
}


/* 
 * function: lnkd_list_
 *
 * constructor for lnkd_list
 * initializes a linked list
 *   l: ptr to lnkd_list
 *
 */
lnkd_list *lnkd_list_()
{
  lnkd_list *l = (lnkd_list *) malloc(sizeof(lnkd_list));

  head(*l) = (l_node *) malloc(sizeof(l_node));
  tail(*l) = (l_node *) malloc(sizeof(l_node));

  next(*head(*l)) = tail(*l);
  prev(*tail(*l)) = head(*l);

  prev(*head(*l)) = next(*tail(*l)) = NULL;

  return l;
}


/* 
 * function: empty_list
 *
 * test for the lnkd_list datatype
 * check if a list is empty
 *
 * return: true if the list is empty
 */
bool empty_list(lnkd_list *l)
{
  return is_tail( next(*head(*l)) );
}


/* 
 * function: add_at_beginning
 *
 * add an element at the beginning of the linked list
 *   l: ptr to list
 *   val: item
 */
void add_at_beginning(lnkd_list *l, l_item val)
{
  insert_l_node_after(head(*l), val);
}


/* 
 * function: add_at_end
 *
 * add an element at the end of the linked list
 *   l: ptr to list
 *   val: item
 */
void add_at_end(lnkd_list *l, l_item val)
{
  insert_l_node_before(tail(*l), val);
}


/* 
 * function: free_lnkd_list
 *
 * frees a list (and all its elements) 
 *   l: list
 */
void free_lnkd_list(lnkd_list *l)
{
  l_node *n;

  n = next(*next(*head(*l)));
  while (!is_tail(n)) {
    free_l_node(prev(*n));
    free(prev(*n));
    n = go_next(n);
  }

  free_l_node(prev(*tail(*l)));
  free(prev(*tail(*l)));
  free(head(*l));
  free(tail(*l));
  free(l);
}
