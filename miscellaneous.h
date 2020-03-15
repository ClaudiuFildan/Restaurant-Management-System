/****************************************************************
 * miscellaneous.h: Header file for miscellaneous functions     *
 * Copyright:       2017                                        *
 * License:         Technical University of Cluj-Napoca         *
 * Authors:         Claudiu Fildan  <claudiu.fildan@gmail.com>  *
 *                  Vlad Bugnariu   <vlad.bugnariu@gmail.com>   *
 * Version:         15-12-2017                                  *
 ****************************************************************/
#ifndef MISCELLANEOUS_H_INCLUDED
#define MISCELLANEOUS_H_INCLUDED

/* Headers required by the following definitions/declarations: */
#include <stdlib.h>

/* Constants definitions: */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
extern void review(char *);
extern void load_waiter_timetable(int ***, int, int);
extern void day_file_generator(int, int);
extern void stock_resupply_alert(char **, int *);
extern void what_waiter_serves_table(int, int, int, int, int **, int);

#endif /* MISCELLANEOUS_H_INCLUDED */
