/*
 *
 * key_t.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines key_t datatype
 */

typedef unsigned long key_t;

#define less_key(a, b) ((bool) (a < b))
#define eq_key(a, b) ((bool) (a == b))
