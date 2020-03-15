/****************************************************************
 * order.c:   See order.h for copyright and info                *
 ****************************************************************/

/* System headers and application specific headers: */
#include <stdio.h>
#include <stdlib.h>

#include "order.h"

/* Private constants: */
#define MENUSIZE 3
#define VAT 19
/* Private types: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

/****************************************************************
 * FUNCTION NAME:   read_menu                                   *
 * DESCRIPTION:     Reads the menu from an external file        *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char **         name    I   The name of the product         *
 *  char **         desc    I   The description of the product  *
 *  double *        gram    I   The weight (grams) of a portion *
 *  double          price   I   The price of a portion          *
 *  int *           invent  I   The number of portions          *
 *                              remaining on the stock          *
 *  int *           id      I   The ID of the product           *
 * RETURN VALUE:												*
 *  int             -       O   1 on success, 0 on failure      *
 * CHANGES:         -                                           *
 ****************************************************************/
int read_menu(char **name, char **desc, double *gram, double *price, int *invent, int *id)
{
    int i = 0, ret = -1;
    FILE * menu_file;
    menu_file = fopen("menu.txt", "r+");
    if(menu_file != NULL)
    {
        for(i = 0; i < MENUSIZE; i++)
        {
            fscanf(menu_file,"%s",*(name+i));
            fscanf(menu_file,"%s",*(desc+i));
            fscanf(menu_file,"%lf",&gram[i]);
            fscanf(menu_file,"%lf",&price[i]);
            fscanf(menu_file,"%d",&invent[i]);
            fscanf(menu_file,"%d",&id[i]);
        }
        printf("The menu was successfully imported!\n");
        ret = 1;
    }
    else
    {
        printf("An error occurred when importing the menu. Please try again.\n");
        ret = 0;
        perror("Error");

    }
    fclose(menu_file);
    return ret;

}

/****************************************************************
 * FUNCTION NAME:   show_menu                                   *
 * DESCRIPTION:     Displays the menu items along with their    *
 *                  descriptions and specifications             *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char **         name    I   The name of the product         *
 *  char **         desc    I   The description of the product  *
 *  double *        gram    I   The weight (grams) of a portion *
 *  double *        price   I   The price of a portion          *
 *  int *           invent  I   The number of portions          *
 *                              remaining on the stock          *
 *  int *           id      I   The ID of the product           *
 * RETURN VALUE:												*
 *   void           -           Prints the menu                 *
 * CHANGES:         -                                           *
 ****************************************************************/
void show_menu(char **name, char **desc, double *gram, double *price, int *invent, int *id)
{
    int i = 0;
    printf("\t\t\t------ MENU ------\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("\tID\tName\t\t\t\t Weight\t\tPrice\t\tDescription\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < MENUSIZE; i++)
    {
        if(invent[i] > 0)
        {
            printf("\t%d\t%s\t\t\t%.2f g\t%.2f RON\t%s\n", id[i], *(name + i), gram[i], price[i], *(desc + i));
        }
    }

    printf("----------------------------------------------------------------------------------------------------\n");
}

/****************************************************************
 * FUNCTION NAME:   order_price                                 *
 * DESCRIPTION:     Computes the price for the current order    *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  double *        price   I   Price array                     *
 *  int *           pol     I   List of the quantities for each *
 *                              of the current ordered products *
 * RETURN VALUE:												*
 *  void            -       -   Prints the current price of the *
 *                              order                           *
 * CHANGES:         -                                           *
 ****************************************************************/
void order_price(double *price, int *pol)
{
    int i = 0;
    float current_price = 0.0f;

    for(i = 0; i < MENUSIZE; i++)
        current_price += (price[i] * *(pol + i));

    printf("Current price: %.2f RON.\n", current_price);
}

/****************************************************************
 * FUNCTION NAME:   take_order                                  *
 * DESCRIPTION:     Prompts the user to input his/her order     *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  int *           id      I   The ID of the product           *
 *  double *        price   I   The price of a portion          *
 *  int **          invent  I   The number of portions          *
 *                              remaining on the stock          *
 *  int **           pol    I   The portion order list          *
 * RETURN VALUE:												*
 *  void            -                                           *
 * CHANGES:         Records the user's order by ID and portion  *
 *                  numbers in a list                           *
 ****************************************************************/
void take_order(int *id, double *price, int **invent, int **pol)
{
    int num_por = 0, input = 0;

    do
    {
        printf("Insert the ID of the product or \"-1\" to pause: ");
        scanf("%d", &input);
        if(input == -1)
            return;

        printf("Insert the number of portions: ");
        scanf("%d", &num_por);
        if(*(*invent + id[input]) >= num_por)
        {
            *(*pol + id[input]) += num_por;
            *(*invent + id[input]) -= num_por;
        }
        else
        {
            printf("Something went wrong! Please try again.\n");
        }
    }while(input != -1 && num_por != -1);
}

/****************************************************************
 * FUNCTION NAME:   print_receipt                               *
 * DESCRIPTION:     Prints a detailed receipt of the order      *
 * ARGUMENT LIST:												*
 * Argument         Type    IO          Description             *
 * ---------------- ------- -- ---------------------------------*
 *  char **         name    I   The name of the ordered product *
 *  double *        price   I   The price of a portion          *
 *  int *           pol     I   The number of portions ordered  *
 * RETURN VALUE:												*
 *  void            -           Prints a receipt                *
 * CHANGES:         -                                           *
 ****************************************************************/
void print_receipt(char **name, double *price, int *pol)
{
    FILE *receipt;
    receipt = fopen("receipts.txt", "a");
    int   i = 0;
    double total_price = 0.0f;
    printf("-----------------------RECEIPT-----------------------\n");
    fprintf(receipt, "-----------------------RECEIPT-----------------------\n");
    for(i = 0; i < MENUSIZE; i++)
    {
        if(*(pol + i) != 0)
        {
            printf("%s\tx %d\t%.2f x %d\t%.2f RON\n", *(name + i), *(pol + i), price[i], pol[i], pol[i] * price[i]);
            fprintf(receipt, "%s\tx %d\t%.2f x %d\t%.2f RON\n", *(name + i), *(pol + i), price[i], pol[i], pol[i] * price[i]);

            total_price += pol[i] * price[i];
        }

    }
    printf("SUBTOTAL:\t%.2f RON\tVAT %d\t TOTAL %.2f\n", total_price, VAT, total_price + total_price*VAT/100);
    fprintf(receipt, "SUBTOTAL:\t%.2f RON\tVAT %d\t TOTAL %.2f\n", total_price, VAT, total_price + total_price*VAT/100);
    printf("------------------ENJOY YOUR LUNCH!------------------\n\n");
    fprintf(receipt, "------------------ENJOY YOUR LUNCH!------------------\n\n");

}
