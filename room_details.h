/****************************************************************
 * room_details.h:  Header file for the details of the room     *
 * Copyright:       2017                                        *
 * License:         Technical University of Cluj-Napoca         *
 * Authors:         Claudiu Fildan  <claudiu.fildan@gmail.com>  *
 *                  Vlad Bugnariu   <vlad.bugnariu@gmail.com>   *
 * Version:         15-12-2017                                  *
 ****************************************************************/
#ifndef ROOM_DETAILS_H_INCLUDED
#define ROOM_DETAILS_H_INCLUDED

/* Headers required by the following definitions/declarations: */
#include <stdlib.h>

/* Constants definitions: */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
extern int  day_reservation_file(char *);
extern void draw_room(int **, int, int);
extern void occupation_degree(int **, int, int);
extern int  reservation_query();
extern int  insert_table_number(int **, int, int);
#endif /* ROOM_DETAILS_H_INCLUDED */
