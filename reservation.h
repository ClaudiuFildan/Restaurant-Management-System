/****************************************************************
 * reservation.h:   Header file for table reservations status   *
 * Copyright:       2017                                        *
 * License:         Technical University of Cluj-Napoca         *
 * Authors:         Claudiu Fildan  <claudiu.fildan@gmail.com>  *
 *                  Vlad Bugnariu   <vlad.bugnariu@gmail.com>   *
 * Version:         15-12-2017                                  *
 ****************************************************************/
#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED

/* Headers required by the following definitions/declarations: */
#include <stdlib.h>

/* Constants definitions: */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
extern int  **alloc_matrix(int, int);
extern void free_matrix (int **, int);
extern void  read_reservation(int **, int, int, char *);
extern void show_free_tables(int **, int, int, char *);
extern char *reservation_day();

#endif /* RESERVATION_H_INCLUDED */
