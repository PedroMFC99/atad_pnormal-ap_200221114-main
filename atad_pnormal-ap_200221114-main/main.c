#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "map.h"
#include "utils.h"

/**
 * @brief Prototype of printCommandsMenu function
 * 
 */
void printCommandsMenu();

/**
 * @brief Prototype of stringComparison function
 * 
 * @param str1 
 * @param str2 
 * @return int 
 */
int stringComparison(char str1[], char str2[]);

int main(int argc, char **argv)
{

    /*Declaration of variables*/
    PtList country_vaccinations = listCreate();
    PtMap country_data = mapCreate();

    String command;
    int quit = 0;

    while (!quit)
    {

        printCommandsMenu();

        scanf(" %s", command);

        if (stringComparison(command, "QUIT"))
        {

            quitCommand(&country_vaccinations, &country_data);

            quit = 1;
        }
        else if (stringComparison(command, "LOADC"))
        {
            if (mapIsEmpty(country_data))
            {
                printf("Loaded %d countries\n",loadc(&country_data));
            }
            else
            {
                printf("Country Map already contains values. USE CLEAR command to delete the values.");
            }
        }
        else if (stringComparison(command, "LOADV"))
        {
            if (listIsEmpty(country_vaccinations))
            {
                printf("Loaded %d vaccines\n",loadv(&country_vaccinations,&country_data));
            }
            else if (mapIsEmpty(country_data))
            {
                printf("Make sure country data has already been loaded. Use LOADC to load country data.");
            }
            else
            {
                printf("Vaccination List already contains values. Use CLEAR command to delete the values.");
            }
        }
        else if (stringComparison(command, "CLEAR"))
        {
            clear(country_vaccinations, country_data);
        }
        else if (stringComparison(command, "SHOWALL"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try the LOADV command to load information.");
            }
            else
            {
                char responseShowAll[10];

                printf("\n Do you want to view ALL of the vaccination data or just a SAMPLE of 100 records?");
                scanf(" %s", responseShowAll);
                showAll(&country_vaccinations, responseShowAll);
            }
        }
        else if (stringComparison(command, "SHOWC"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                char responseShowC[10];

                printf("\n Which Country do you want to see the vaccination data for?");
                scanf(" %s", responseShowC);
                showC(&country_vaccinations, responseShowC);
            }
        }
        else if (stringComparison(command, "LISTC"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                listC(&country_vaccinations);
            }
        }
        else if (stringComparison(command, "LISTV"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                listV(&country_vaccinations);
            }
        }
        else if (stringComparison(command, "AVERAGE"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                averageGlobal(country_vaccinations);
                averagePerCountry(country_vaccinations);
            }
        }
        else if (stringComparison(command, "SHOWV"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                showV(&country_vaccinations);
            }
        }
        else if (stringComparison(command, "TOPN"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try LOADV command to load information.\n");
            }
            else
            {
                int n;

                printf("\n For how many countries do you want to see vaccination data, sorted by percentage of people vaccinated?");
                scanf(" %d", &n);
                topN(country_vaccinations, n);
            }
        }
        else if (stringComparison(command, "PREVISION"))
        {
            if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try the LOADV command to load information.\n");
            }
            else
            {
                printf("Not Implemented.\n");
                //prevision(&country_vaccinations);
            }
        }
        else if (stringComparison(command, "COUNTRY_S"))
        {
            if (mapIsEmpty(country_data) || country_data == NULL)
            {
                printf("Country Map doesn't contain values. Try LOADC command to load information.\n");
            }
            else if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try the LOADV command to load information.\n");
            }
            else
            {
                countryS(&country_data);
            }
        }
        else if (stringComparison(command, "REGIONS"))
        {
            if (mapIsEmpty(country_data) || country_data == NULL)
            {
                printf("Country Map doesn't contain values. Try LOADC command to load information.\n");
            }
            else if (listIsEmpty(country_vaccinations) || country_vaccinations == NULL)
            {
                printf("Vaccination List doesn't contain values. Try the LOADV command to load information.\n");
            }
            else
            {
                regions(country_vaccinations, country_data);
            }
        }
        else
        {
            printf("%s : Command not found!\n", command);
        }
    }

    return (EXIT_SUCCESS);
}

/**
 * @brief Shows the program's main menu.
 * 
 */
void printCommandsMenu()
{
    printf("\n=====================================================================================");
    printf("\n            COVID-19 VACCINATION (Data Processing and Forecasting)           ");
    printf("\n=====================================================================================");
    printf("\nA. Base Commands (LOADC , LOADV , CLEAR).");
    printf("\nB. Simple Indicators (SHOWALL, SHOWC, LISTC, LISTV, AVERAGE, SHOWV, TOPN, PREVISION).");
    printf("\nC. Advanced indicators (COUNTRY_S, REGIONS)");
    printf("\nD. Exit (QUIT)\n\n");
    printf("COMMAND> ");
}

/**
 * @brief Compares two strings
 * 
 * @param str1 
 * @param str2 
 * @return int 
 */
int stringComparison(char str1[], char str2[])
{
    return (strcmp(str1, str2) == 0);
}