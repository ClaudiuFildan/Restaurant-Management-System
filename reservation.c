/****************************************************************
 * reservation.c:   See reservation.h for copyright and info    *
 ****************************************************************/

/* System headers and application specific headers: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reservation.h"

/* Private constants: */

/* Private types: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

/****************************************************************
 * FUNCTION NAME:   alloc_matrix                                *
 * DESCRIPTION:     Allocates memory for a m by n               *
 *                  matrix of integers                          *
 * ARGUMENT LIST:                                               *
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int             m       I   Number of rows of the matrix    *
 *  int             n       I   Number of columns of the matrix *
 * RETURN VALUE:                                                *
 *  int **          -       O   Pointer to the allocated area   *
 *                              or NULL on failure              *
 * CHANGES:         -                                           *
 ****************************************************************/
int **alloc_matrix(int m, int n)
{
    int **matrix = NULL;
    int i = 0;
    matrix = (int **) malloc(m * sizeof(int *));
    if(!matrix)
        return NULL;
    for(i = 0; i < m; i++)
    {
        *(matrix + i) = (int *) malloc(n * sizeof(int));
        if(!(*(matrix + i)))
            return NULL;
    }
    return matrix;
}

/****************************************************************
 * FUNCTION NAME:   free_matrix                                 *
 * DESCRIPTION:     Deallocates memory for a m by n             *
 *                  matrix of integers                          *
 * ARGUMENT LIST:                                               *
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   The matrix to free              *
 *  int             m       I   Number of rows of the matrix    *
 * RETURN VALUE:                                                *
 *  void            -       O   -                               *
 * CHANGES:         Memory area freed can no longer be used     *
 ****************************************************************/
void free_matrix(int **matrix, int m)
{
    int i = 0;

    for(i = 0; i < m; i++)
    {
        free(*(matrix + i));
    }
    free(matrix);
}

/****************************************************************
 * FUNCTION NAME:   read_reservation                            *
 * DESCRIPTION:     Reads the table status matrix from the file *
 *                  corresponding to the selected day           *
 * ARGUMENT LIST:                                               *
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   Matrix of the selected day      *
 *  int             m       I   Number of rows of the matrix    *
 *  int             n       I   Number of columns of the matrix *
 *  char *          f_day   I   Name of the file to read from   *
 * RETURN VALUE:												*
 *  int             -       O   1 on success, 0 on failure      *
 * CHANGES:         Memory area previously reserved for storing *
 *                  the read matrix                             *
 ****************************************************************/
void read_reservation(int **matrix, int m, int n, char *f_day)
{
    FILE *the_file;
    the_file = fopen(f_day, "r");

    int i=0,j=0;
    if(the_file)
    {
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                fscanf(the_file,"%d", *(matrix + i)+j);
            }
        }
    }
    fclose(the_file);
}

/****************************************************************
 * FUNCTION NAME:   show_free_tables                            *
 * DESCRIPTION:     Displays a list of the free tables          *
 *                  in the selected day                         *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int **          matrix  I   The matrix of the tables        *
 *  int             m       I   Number of rows of the matrix    *
 *  int             n       I   Number of columns of the matrix *
 *  char *          day     I   The selected day of the week    *
 * RETURN VALUE:												*
 *   void           -       -   Displays the index numbers of   *
 *                              the free tables                 *
 * CHANGES:         -                                           *
 ****************************************************************/
void show_free_tables(int **matrix, int m, int n, char *day)
{
    int i = 0, j = 0;
    printf("On %s, our free tables are:", day);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(*(*(matrix + i) + j) == 0)
                printf(" %d%d,", i, j);
        }
    }
    printf("\b.\n");
}

/****************************************************************
 * FUNCTION NAME:   reservation_day                             *
 * DESCRIPTION:     Gets the user's reservation day             *
 * ARGUMENT LIST:	No arguments       							*
 * RETURN VALUE:												*
 *   char *         day     O   The user's input to lowercase   *                                            *
 * CHANGES:         -                                           *
 ****************************************************************/
char *reservation_day()
{
    char *day;
    day = (char *)calloc(20, sizeof(char));
    size_t i = 0;

    printf("Type the day in which you want to reserve the table: ");
    scanf("%s", day);

    for(i = 0; i < strlen(day); i++)
    {
        day[i] = tolower(day[i]);
    }
    return day;
}
