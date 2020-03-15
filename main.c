/****************************************************************
 * Restaurant application                                       *
 * Copyright:       2017                                        *
 * License:         Technical University of Cluj-Napoca         *
 * Authors:         Claudiu Fildan  <claudiu.fildan@gmail.com>  *
 *                  Vlad Bugnariu   <vlad.bugnariu@gmail.com>   *
 * Version:         15-12-2017                                  *
 ****************************************************************/

/* System headers and application specific headers: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reservation.h"
#include "room_details.h"
#include "order.h"
#include "miscellaneous.h"

/* Private constants: */
#define MENUSIZE 3
#define M 5
#define N 6

/* Private types: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

int main()
{
    /* Variable declarations */
    int     daycorect=0;
    int     **w_tt = NULL, **tables = NULL;
    int     tbl = 0, i = 0, cont = -1;
    int     id[MENUSIZE] = {0}, *invent, *pol;
    double  gram[MENUSIZE] = {0.0}, price[MENUSIZE] = {0.0};
    char    **name = NULL, **desc = NULL;
    char    *day = NULL, *c_name = NULL;
    char    dayfile[7][20] = {"monday.txt", "tuesday.txt", "wednesday.txt", "thursday.txt", "friday.txt", "saturday.txt", "sunday.txt"};



    /* Variable initialization */
    w_tt    = alloc_matrix(4, 7);
    tables  = alloc_matrix(M, N);
    day     = (char *)calloc(20, sizeof(char));
    name    = (char **)malloc(sizeof(char) * MENUSIZE);
    desc    = (char **)malloc(sizeof(char) * MENUSIZE);
    c_name  = (char *)calloc(25, sizeof(char));
    invent  = (int *)malloc(sizeof(int) * MENUSIZE);
    pol     = (int *)calloc(MENUSIZE, sizeof(int));

    for(i = 0 ; i < MENUSIZE; i++)
    {
        name[i] = (char *)malloc(sizeof(char) * 10);
        desc[i] = (char *)malloc(sizeof(char) * 20);
    }

    /* Function calls*/
    day_file_generator(M, N);
    load_waiter_timetable(&w_tt, 4, 7);
    if(read_menu(name, desc, gram, price, invent, id))
        system("cls");

    printf("Please, insert your name here: ");
    gets(c_name);
    if(reservation_query())
    {
        day = reservation_day();
        daycorect = day_reservation_file(day);
        read_reservation(tables, M, N, dayfile[daycorect]);
        while(daycorect == 8)
        {
            day = reservation_day();
            daycorect = day_reservation_file(day);
            read_reservation(tables, M, N, dayfile[daycorect]);
        }

        //read_reservation(tables, M, N, dayfile[dayc]);
        draw_room(tables, M, N);
        show_free_tables(tables, M, N, day);
        occupation_degree(tables, M, N);
        do
        {
            tbl = insert_table_number(tables, M, N);
        }while(tbl == -1);

        draw_room(tables, M, N);
        what_waiter_serves_table(tbl/10, tbl%10, M, N, w_tt, day_reservation_file(day));
        printf("\n");
    }
    show_menu(name, desc, gram, price, invent, id);
    do
    {
        take_order(id, price, &invent, &pol);
        order_price(price, pol);
        printf("Do you want to add anything? (1 for yes/0 for no): ");
        scanf("%d", &cont);
    }while(cont);
    stock_resupply_alert(name, invent);

    print_receipt(name, price, pol);

    review(c_name);
    /* Testing for debug purposes */



    /* Free allocated memory */
    free_matrix(w_tt, 4);
    free_matrix(tables, M);
    free(day);
    free(name);
    free(desc);
    free(invent);
    free(pol);

    return 0;
}
