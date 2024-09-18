#pragma once

#include "date.h"

typedef struct vaccination {
    char country[35];
    Date date;
    int totalVaccination;
    int peopleVaccinated;
    int peopleFullyVaccinated;
    float dailyVaccination;
    float totalVaccinationsPerHundred;
    float peopleVaccinatedPerHundred;
    float peopleFullyVaccinatedPerHundred;
    int dailyVaccinationsPerMillion;
    char vaccines[5][20];
    int number_vaccines;
} Vaccination;


typedef struct vaccination* PtVaccination;

Vaccination vaccinationCreate(char country[35],Date date,int totalVaccination,int peopleVaccinated,int peopleFullyVaccinated,float dailyVaccination
, float totalVaccinationsPerHundred, float peopleVaccinatedPerHundred, float peopleFullyVaccinatedPerHundred, int dailyVaccinationsPerMillion,char vaccines[5][20],int number_vaccines);


void vaccinationPrint(PtVaccination count);