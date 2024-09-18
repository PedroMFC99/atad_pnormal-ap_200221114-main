#include <stdio.h>
#include <string.h>
#include "vaccinations.h"
#include "date.h"


Vaccination vaccinationCreate(char country[35],Date date,int totalVaccination,int peopleVaccinated,int peopleFullyVaccinated,float dailyVaccination
, float totalVaccinationsPerHundred, float peopleVaccinatedPerHundred, float peopleFullyVaccinatedPerHundred, int dailyVaccinationsPerMillion,char vaccines[5][20],int number_vaccines){


    Vaccination TSvaccination;

    strcpy(TSvaccination.country, country);
    TSvaccination.date = date;
    TSvaccination.totalVaccination = totalVaccination;
    TSvaccination.peopleVaccinated = peopleVaccinated;
    TSvaccination.peopleFullyVaccinated = peopleFullyVaccinated;
    TSvaccination.dailyVaccination = dailyVaccination;
    TSvaccination.totalVaccinationsPerHundred = totalVaccinationsPerHundred;
    TSvaccination.peopleVaccinatedPerHundred = peopleVaccinatedPerHundred;
    TSvaccination.peopleFullyVaccinatedPerHundred = peopleFullyVaccinatedPerHundred;
    TSvaccination.dailyVaccinationsPerMillion = dailyVaccinationsPerMillion;
    TSvaccination.number_vaccines = number_vaccines;
    
    memcpy(TSvaccination.vaccines,vaccines,sizeof(TSvaccination.vaccines));


    return TSvaccination;
}



void vaccinationPrint(PtVaccination vac){


    printf("\n Country: %s , Date: %d / %d / %d , Total Vaccinations : %d , People Vaccinated : %d , People Fully Vaccinated : %d , Daily Vaccination : %f, Total Vaccinations per hunderd : %f, People Fully Vaccinated per hundred : %f, Daily Vaccinations per million : %d, Number of Vaccines : %d" , vac->country, vac->date.day, vac->date.month, vac->date.year, vac->totalVaccination,vac->peopleVaccinated, vac->peopleFullyVaccinated, vac->dailyVaccination, vac->totalVaccinationsPerHundred,vac->peopleFullyVaccinatedPerHundred,vac->dailyVaccinationsPerMillion,vac->number_vaccines);
    

}