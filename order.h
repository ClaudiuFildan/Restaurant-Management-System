/****************************************************************
 * order.h:         Header file for functions related to orders *                *
 * Copyright:       2017                                        *
 * License:         Technical University of Cluj-Napoca         *
 * Authors:         Claudiu Fildan  <claudiu.fildan@gmail.com>  *
 *                  Vlad Bugnariu   <vlad.bugnariu@gmail.com>   *
 * Version:         15-12-2017                                  *
 ****************************************************************/
#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

/* Headers required by the following definitions/declarations: */
#include <stdlib.h>

/* Constants definitions: */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
extern int read_menu(char **, char **, double *, double*, int *, int *);
extern void show_menu(char **, char **, double *, double*, int *, int *);
extern void order_price(double *, int *);
extern void take_order(int *, double *, int **, int **);
extern void print_receipt(char **, double *, int *);

#endif /* ORDER_H_INCLUDED */
