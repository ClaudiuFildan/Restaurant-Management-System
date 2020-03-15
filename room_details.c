/****************************************************************
 * room_details.c:   See room_details.h for copyright and info  *
 ****************************************************************/

/* System headers and application specific headers: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "room_details.h"

/* Private constants: */

/* Private types: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

/****************************************************************
 * FUNCTION NAME:   day_reservation_file                        *
 * DESCRIPTION:     Returns the weekday as a digit between 0    *
 *                  and 6 or 8 in case of an error              *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char *          day     I   The day of the week             *
 * RETURN VALUE:												*
 *  int             -       O   The converted day               *
 * CHANGES:         -                                           *
 ****************************************************************/
int day_reservation_file(char *day)
{

    if(strcmp(day, "luni") == 0 || strcmp(day, "monday") == 0)
    {
        printf("You chose %s.\n", "Monday");
        return 0;
    }
    if(strcmp(day, "marti") == 0 || strcmp(day, "tuesday") == 0)
    {
        printf("You chose %s.\n", "Tuesday");
        return 1;
    }
    if(strcmp(day, "miercuri") == 0 || strcmp(day, "wednesday") == 0)
    {
        printf("You chose %s.\n", "Wednesday");
        return 2;
    }
    if(strcmp(day, "joi") == 0 || strcmp(day, "thursday") == 0)
    {
        printf("You chose %s.\n", "Thursday");
        return 3;
    }
    if(strcmp(day, "vineri") == 0 || strcmp(day, "friday") == 0)
    {
        printf("You chose %s.\n", "Friday");
        return 4;
    }
    if(strcmp(day, "sambata") == 0 || strcmp(day, "saturday") == 0)
    {
        printf("You chose %s.\n", "Saturday");
        return 5;
    }
    if(strcmp(day, "duminica") == 0 || strcmp(day, "sunday") == 0)
    {
        printf("You chose %s.\n", "Sunday");
        return 6;
    }
    printf("Something went wrong! Please try again.\n");
    return 8;
}

/****************************************************************
 * FUNCTION NAME:   draw_room                                   *
 * DESCRIPTION:     Graphically displays the room and which     *
 *                  tables are reserved                         *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   The table status matrix         *
 *  int             m       I   Number of matrix rows           *
 *  int             n       I   Number of matrix columns        *
 * RETURN VALUE:												*
 *  void            -       -   Prints the room map             *
 * CHANGES:         -                                           *
 ****************************************************************/
void draw_room(int **matrix, int m, int n)
{
    int i = 0, j = 0;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t------------");
        }
        printf("\n");
        for(j = 0; j < n; j++)
        {
            printf("\t| Table %d%d |", i, j);
        }
        printf("\n");
        for(j = 0; j < n; j++)
        {
            if(*(*(matrix + i) + j) == 1)
                printf("\t|(reserved)|");
            else
                printf("\t|  (free)  |");
        }
        printf("\n");
        for(j = 0; j < n; j++)
        {
            printf("\t------------");
        }
        printf("\n");
    }
    printf("\t\t\t\t\tENTRANCE\n");
}

/****************************************************************
 * FUNCTION NAME:   occupation_degree                           *
 * DESCRIPTION:     Displays the ratio between the number of    *
 *                  occupied and total tables                   *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   The matrix of the tables        *
 *  int             m       I   Number of matrix rows           *
 *  int             n       I   Number of matrix columns        *
 * RETURN VALUE:												*
 *   void           -       -   Prints the ratio and the        *
 *                              occupation percent of the room  *
 * CHANGES:         -                                           *
 ****************************************************************/
void occupation_degree(int **matrix, int m, int n)
{
    int i = 0, j = 0, no_occ = 0;
    float percent = 0.0f;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            no_occ += *(*(matrix + i) + j);
        }
    }
    percent = (float)(no_occ * 100)/(m * n);
    printf("Occupied tables: %d out of %d (%.2f %)\n",
            no_occ, m * n, percent);
}

/****************************************************************
 * FUNCTION NAME:   reservation_query                           *
 * DESCRIPTION:     Asks the user whether to make a reservation *
 *                  or not                                      *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *                                                              *
 * RETURN VALUE:												*
 *   int            -       O   1 for yes, 0 for no             *
 * CHANGES:         -                                           *
 ****************************************************************/
int reservation_query()
{
    char a = '\0';
    printf("Do you want to make a reservation?\n");
    do
    {
        printf("Insert Y/y for yes and N/n for no.\n");
        scanf("%c", &a);

        switch(a)
        {
            case 'Y':
            case 'y':
                printf("You chose to make a reservation.\n");
                return 1;
            case 'N':
            case 'n':
                printf("You chose not to make a reservation.\n");
                return 0;
            default:
                printf("Something went wrong, please try again.\n");
        }
    }while(1);
}

/****************************************************************
 * FUNCTION NAME:   insert_table_number                         *
 * DESCRIPTION:     Gets whether the user's input table is      *
 *                  occupied or not                             *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   The table status matrix         *
 *  int             m       I   Number of matrix rows           *
 *  int             n       I   Number of matrix columns        *
 * RETURN VALUE:												*
 *   int            -       O   -1 if occupied, table number if *
 *                              free                            *
 * CHANGES:         -                                           *
 ****************************************************************/
int insert_table_number(int **matrix, int m, int n)
{
    int num = 0, i = 0, j = 0;

    printf("Insert the table number: ");
    scanf("%d", &num);

    i = num/10;
    j = num%10;

    if(*(*(matrix + i) + j) == 0)
    {
        *(*(matrix + i) + j) = 1;
        printf("Table number %d was successfully reserved!\n", num);
        return num;
    }
    else
    {
        printf("We are sorry, but table number %d is already reserved.\n", num);
        return -1;
    }
}
