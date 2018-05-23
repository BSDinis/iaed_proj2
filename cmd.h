/*
 *
 * cmd.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the cmd datatype
 */

#ifndef CMD_H
#define CMD_H

typedef enum {ADD = 0, DUR, DEP, RM, PATH, FIRST, SECOND, EXIT, INVALID} cmd;

/* check if a command is valid */
#define valid_command(a) ((a) != INVALID)

#endif /* !CMD_H */
