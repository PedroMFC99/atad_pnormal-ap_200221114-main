
#include <stdio.h>
#include <string.h>
#include "countries.h"





Country countryCreate(char country[35], char region[20], int population, int area, int medianAge, float urbanPopulation, float worldShare){

    Country TScountry;

    strcpy(TScountry.country, country);
    strcpy(TScountry.region, region);
    TScountry.population = population;
    TScountry.area = area;
    TScountry.medianAge = medianAge;
    TScountry.urbanPopulation = urbanPopulation;
    TScountry.worldShare = worldShare;

    return TScountry;
}

void countryPrint(PtCountry count){

    printf("Area: %d , Country: %s, MedianAge: %d, Population: %d, Region: %s, UrbanPopulation: %.2f, WorldShare: %.2f \n",count->area,count->country,count->medianAge,count->population,count->region,count->urbanPopulation,count->worldShare);

}