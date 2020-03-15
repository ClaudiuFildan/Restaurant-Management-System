/****************************************************************
 * miscellaneous.c: See miscellaneous.h for copyright and info  *
 ****************************************************************/

/* System headers and application specific headers: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miscellaneous.h"

/* Private constants: */
#define MENUSIZE 3

/* Private types: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

/****************************************************************
 * FUNCTION NAME:   review                                      *
 * DESCRIPTION:     Prompts the client to express his opinion   *
 *                  both as text and as a grade from 1 to 10    *
 *                  and stores them in files                    *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char *          c_name  I   The name of the current client  *
 * RETURN VALUE:												*
 *   void           -       -                                   *
 * CHANGES:         Stores data in files                        *
 ****************************************************************/
void review(char *c_name)
{
    char rev[500];
    int  grade = 0;
    FILE *t_review;

    t_review = fopen("reviews.txt", "a+");

    printf("Please, provide us with your feedback (use\"_\" instead spaces):\n");
    scanf("%s", rev);

    fprintf(t_review, "\"%s\"\n - %s\n\n", rev, c_name);

    fclose(t_review);

    FILE  *g_review;

    g_review = fopen("rating.txt", "a+");

    printf("Please, rate us! On a scale from 1 to 10: \n");
    scanf("%d", &grade);

    fprintf(g_review, "%d /10 -%s\n", grade, c_name);

    printf("Thank you! See you next time! Have a good day!\n");

    fclose(g_review);

}

/****************************************************************
 * FUNCTION NAME:   stock_resupply_alert                        *
 * DESCRIPTION:     Whenever the stock for a product drops      *
 *                  under 10 pieces, the function writes in a   *
 *                  file that the certain product needs to be   *
 *                  restocked                                   *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char **         name    I   The name of the product         *
 *  int *           invent  I   The inventory list of products  *
 * RETURN VALUE:												*
 *  void            -       -                                   *
 * CHANGES:         Prints in a file                            *
 ****************************************************************/
void stock_resupply_alert(char **name, int *invent)
{
    int i = 0;
    FILE *stock_alert;
    stock_alert = fopen("stockalert.txt", "w");

    for(i = 0; i < MENUSIZE; i++)
    {
        if(invent[i] < 10)
            fprintf(stock_alert, "%s needs to be restocked!\n", *(name + i));
    }

}

/****************************************************************
 * FUNCTION NAME:   day_file_generator                          *
 * DESCRIPTION:     Checks whether the files for each have the  *
 *                  correct dimensions for the matrix           *
 *                  restocked                                   *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int             m       I   Number of matrix rows           *
 *  int             n       I   Number of matrix columns        *
 * RETURN VALUE:												*
 *  void            -       -                                   *
 * CHANGES:         Reads and prints in a files                 *
 ****************************************************************/
void day_file_generator(int m, int n)
{
    int array[100], count = 0, i = 0, j = 0, k = 0;
    FILE *day_file;
    for(k = 0; k < 7; k++)
    {
        switch(k)
        {
            case 0:
                day_file = fopen("monday.txt", "w+");
                break;
            case 1:
                day_file = fopen("tuesday.txt", "w+");
                break;
            case 2:
                day_file = fopen("wednesday.txt", "w+");
                break;
            case 3:
                day_file = fopen("thursday.txt", "w+");
                break;
            case 4:
                day_file = fopen("friday.txt", "w+");
                break;
            case 5:
                day_file = fopen("saturday.txt", "w+");
                break;
            case 6:
                day_file = fopen("sunday.txt", "w+");
                break;

        }
        int randomBit = -1;
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
            {
                randomBit = rand() % 2;
                fprintf(day_file, "%d ", randomBit);
            }
            fprintf(day_file, "\n");
        }
        fclose(day_file);
    }
}

/****************************************************************
 * FUNCTION NAME:   load_waiter_timetable                       *
 * DESCRIPTION:     Imports the waiter timetable from a file    *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char ***        w_tt    I   The matrix that stores the      *
 *                              timetable                       *
 * RETURN VALUE:												*
 *  void            -       -                                   *
 * CHANGES:         Stores information in the parameter         *
- ****************************************************************/
void load_waiter_timetable(int ***w_tt, int m, int n)
{
    FILE *tt;
    int i = 0, j = 0;
    tt = fopen("timetable.txt", "r");
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            fscanf(tt, "%d", *(*w_tt + i) + j);
        }
    }
    fclose(tt);
}

/****************************************************************
 * FUNCTION NAME:   what_waiter_serves_table                    *
 * DESCRIPTION:     Displays which waiter will serve at the     *
 *                  respective table                            *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int             i       I   The row of the table            *
 *  int             j       I   The column of the table         *
 *  int             m       I   Number of room rows             *
 *  int             n       I   Number of room columns          *
 *  char **         w_tt    I   The matrix of waiters           *
 *  int             day     I   The encoded day (0 -> 6)        *
 * RETURN VALUE:												*
 *  void            -       -   -                               *
 * CHANGES:         Prints the waiter's name                    *
 ****************************************************************/
void what_waiter_serves_table(int i, int j, int m, int n, int **w_tt, int day)
{
    if(i < m/2)
    {
        if(j < n/2)
        {
            printf("Table %d%d will be served by waiter %d.\n", i, j, *(*(w_tt + 0) + day));
        }
        else
        {
            printf("Table %d%d will be served by waiter %d.\n", i, j, *(*(w_tt + 1) + day));
        }
    }
    else
    {
        if(j < n/2)
        {
            printf("Table %d%d will be served by waiter %d.\n", i, j, *(*(w_tt + 2) + day));
        }
        else
        {
            printf("Table %d%d will be served by waiter %d.\n", i, j, *(*(w_tt + 3) + day));
        }
    }
}
