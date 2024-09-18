#pragma once

typedef struct country_struct {
    char country[35];
    char region[20];
    int population;
    int area;
    int medianAge;
    float urbanPopulation;
    float worldShare;
} Country;

typedef struct country_struct* PtCountry;

Country countryCreate(char country[35], char region[20], int population, int area, int medianAge, float urbanPopulation, float worldShare);


void countryPrint(PtCountry count);