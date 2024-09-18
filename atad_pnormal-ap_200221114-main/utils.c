#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

#include "list.h"
#include "map.h"
#include "countries.h"
#include "stringutils.h"
#include "stringCode.h"
#include "vaccinations.h"
#include "utils.h"


int loadc(PtMap *ptMap)
{

    FILE *stream = fopen("csv_data/country_data_2020.csv", "r");

    StringCode key;

    int count = 0;

    if (!stream)
        return 0;

    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        count++;

        char *tmp = strdup(line);

        char **tokens = splitString(tmp, 7, ";");

        replace(tokens[5], ',', '.');
        replace(tokens[6], ',', '.');
        Country tcountry = countryCreate(tokens[0], tokens[1], atoi(tokens[2]), atoi(tokens[3]), atoi(tokens[4]), atof(tokens[5]), atof(tokens[6]));
        key = stringCodeCreate(tokens[0]);
        mapPut(*ptMap, key, tcountry);
        free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}


int loadv(PtList *ptList, PtMap *ptMap)
{

    FILE *stream = fopen("csv_data/country_vaccinations.csv", "r");


    int count = 0;

    if (!stream)
        return 0;

    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        count++;

        char *tmp = strdup(line);

        char **tokens = splitString(tmp, 11, ";");

        if (!strcmp(tokens[2], "N.A."))
        {
            tokens[2] = "-1";
        }
        if (!strcmp(tokens[3], "N.A."))
        {
            tokens[3] = "-1";
        }
        if (!strcmp(tokens[4], "N.A."))
        {
            tokens[4] = "-1";
        }

        replace(tokens[5], ',', '.');
   
        char vaccines[5][20];
        int nvac = 0;
        for (int i = 6; i < 11; i++)
        {
            if (!strstr(tokens[i], "N.A."))
            {
                strcpy(vaccines[i - 6], tokens[i]);
                nvac++;
            }
            else
            {
                strcpy(vaccines[i - 6], "");
            }
        }

        MapValue peopleInC;
        mapGet(*ptMap, stringCodeCreate(tokens[0]), &peopleInC);

        char **date = splitString(tokens[1], 3, "/");

        Vaccination tvac = vaccinationCreate(tokens[0],
            createDate(atoi(date[0]),
            atoi(date[1]),
            atoi(date[2])),
            atoi(tokens[2]),
            atoi(tokens[3]),
            atoi(tokens[4]),
            atof(tokens[5]),
            (strcmp(tokens[2], "-1") == 0 ? -1 :(float)((atof(tokens[2]) / peopleInC.population) * 100)),
            (strcmp(tokens[3], "-1") == 0 ? -1 :(float)((atof(tokens[3]) / peopleInC.population) * 100)),
            (strcmp(tokens[4], "-1") == 0 ? -1 :(float)((atof(tokens[4]) / peopleInC.population) * 100)),
            (strcmp(tokens[5], "-1") == 0 ? -1 :((atof(tokens[5]) / peopleInC.population) * 1000000)),
            vaccines,
            nvac);
        listAdd(*ptList, count - 1, tvac);
        free(tokens);
        free(date);
        free(tmp);
    }

    fclose(stream);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            ListElem elem1, elem2, elemO;
            listGet(*ptList, j, &elem1);
            listGet(*ptList, j + 1, &elem2);
            if (strcmp(elem1.country, elem2.country) > 0)
            {
                listSet(*ptList, j + 1, elem1, &elemO);
                listSet(*ptList, j, elem2, &elemO);
            }
            else if (strcmp(elem1.country, elem2.country) == 0)
            {
                if (elem1.peopleVaccinatedPerHundred < elem2.peopleVaccinatedPerHundred)
                {
                    listSet(*ptList, j + 1, elem1, &elemO);
                    listSet(*ptList, j, elem2, &elemO);
                }
            }
        }
    }

    return count;
}


int clear(PtList ptList, PtMap ptMap)
{
    int size = 0, count = 0, code = 0;
    if (!(listIsEmpty(ptList) && mapIsEmpty(ptMap)))
    {
        //List clear
        ListElem *ptElem = malloc(sizeof(ListElem));

        listSize(ptList, &size);

        for (int i = 0; i < size; i++)
        {
            code = listRemove(ptList, i, ptElem);
            if (code == 0)
            {
                count++;
                size--;
            }
            else
            {
                printf("%d\n", code);
            }
        }
        listClear(ptList);
        printf("%d records deleted from Vaccines\n", count);

        count = 0, size = 0;

        free(ptElem);

        //Map clear
        MapKey *key;
        MapValue *ptValue = malloc(sizeof(MapValue));

        key = mapKeys(ptMap);

        mapSize(ptMap, &size);

        for (int i = 0; i < size; i++)
        {
            code = mapRemove(ptMap, key[i], ptValue);
            if (code == 0)
            {
                count++;
            }
            else
            {
                printf("%d\n", code);
            }
        }

        mapClear(ptMap);

        printf("%d records deleted from Countries\n", count);

        count = 0;

        free(key);
        free(ptValue);

        return 0;
    }
    return 3;
}


void quitCommand(PtList *ptList, PtMap *ptMap)
{
    listDestroy(ptList);
    mapDestroy(ptMap);
    printf("Memory Cleared!\n");
}


void showAll(PtList *ptList, char *choice)
{
    int size = 0;
    listSize(*ptList, &size);
    if (strcmp(choice, "ALL") == 0)
    {
        for (int i = 0; i <= size; i++)
        {
            ListElem elem;
            listGet(*ptList, i, &elem);
            printf("\n Country: %s", elem.country);
            printf("\n Date: %d/%d/%d", elem.date.day, elem.date.month, elem.date.year);
            printf("\n Vaccines: ");
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(elem.vaccines[j], "") != 0)
                {
                    printf("%s, ", elem.vaccines[j]);
                }
            }
            printf("\n Daily Vaccination: %f  Daily Vaccinations Per Million: %d", elem.dailyVaccination, elem.dailyVaccinationsPerMillion);
            printf("\n People Fully Vaccinated: %d  People Fully Vaccinated Per Hundred: %f  People Vaccinated: %d  People Vaccinated Per Hundred: %f", elem.peopleFullyVaccinated,
                   elem.peopleFullyVaccinatedPerHundred, elem.peopleVaccinated, elem.peopleVaccinatedPerHundred);
            printf("\n Number of Vaccines: %d  Total Vaccination: %d  Total Vaccinations Per Hundred: %f", elem.number_vaccines,
                   elem.totalVaccination, elem.totalVaccinationsPerHundred);
            printf("\n-------------------------------------------------------------------------");
        }
    }
    else if (strcmp(choice, "SAMPLE") == 0)
    {
        for (int i = 0; i <= 100; i++)
        {
            int randomSample = (rand() % size);
            ListElem elem;
            listGet(*ptList, randomSample, &elem);
            printf("\n Country: %s", elem.country);
            printf("\n Date: %d/%d/%d", elem.date.day, elem.date.month, elem.date.year);
            printf("\n Vaccines: ");
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(elem.vaccines[j], "") != 0)
                {
                    printf("%s, ", elem.vaccines[j]);
                }
            }
            printf("\n Daily Vaccination: %f  Daily Vaccinations Per Million: %d", elem.dailyVaccination, elem.dailyVaccinationsPerMillion);
            printf("\n People Fully Vaccinated: %d  People Fully Vaccinated Per Hundred: %f  People Vaccinated: %d  People Vaccinated Per Hundred: %f", elem.peopleFullyVaccinated,
                   elem.peopleFullyVaccinatedPerHundred, elem.peopleVaccinated, elem.peopleVaccinatedPerHundred);
            printf("\n Number of Vaccines: %d  Total Vaccination: %d  Total Vaccinations Per Hundred: %f", elem.number_vaccines,
                   elem.totalVaccination, elem.totalVaccinationsPerHundred);
            printf("\n-------------------------------------------------------------------------");
        }
    }
    else
    {
        printf("\n Please type the correct command");
    }
}


void showC(PtList *ptList, char *country)
{

    PtList countryChoice = listCreate();

    getReportsOfCountry(*ptList, country, &countryChoice);

    int sizeCountryList = 0;
    listSize(countryChoice, &sizeCountryList);
    if (sizeCountryList == 0)
    {
        printf("\n Vaccination data not available for %s", country);
    }
    else
    {
        for (int i = 0; i <= sizeCountryList; i++)
        {
            ListElem elem;
            listGet(countryChoice, i, &elem);
            printf("\n Country: %s", elem.country);
            printf("\n Date: %d/%d/%d", elem.date.day, elem.date.month, elem.date.year);
            printf("\n Vaccines: ");
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(elem.vaccines[j], "") != 0)
                {
                    printf("%s, ", elem.vaccines[j]);
                }
            }
            printf("\n Daily Vaccination: %f  Daily Vaccinations Per Million: %d", elem.dailyVaccination, elem.dailyVaccinationsPerMillion);
            printf("\n People Fully Vaccinated: %d  People Fully Vaccinated Per Hundred: %f  People Vaccinated: %d  People Vaccinated Per Hundred: %f", elem.peopleFullyVaccinated,
                   elem.peopleFullyVaccinatedPerHundred, elem.peopleVaccinated, elem.peopleVaccinatedPerHundred);
            printf("\n Number of Vaccines: %d  Total Vaccination: %d  Total Vaccinations Per Hundred: %f", elem.number_vaccines,
                   elem.totalVaccination, elem.totalVaccinationsPerHundred);
            printf("\n-------------------------------------------------------------------------");
        }
    }
    listDestroy(&countryChoice);
}


void topN(PtList ptList, int n)
{
    PtList calculatedTopN = calcTopN(ptList);
    PtList sortedTopN = sortTopN(calculatedTopN);



    printf("%-3s %-17s %-15s %-15s", "RK", "Country", "People Vac.", "People Full Vac.\n");
    for (int i = 0; i < n; i++)
    {
        ListElem elem;
        listGet(calculatedTopN, i, &elem);
        printf("%-3d %-17s %-15.2f %-15.2f\n", i+1, elem.country, elem.peopleVaccinatedPerHundred, elem.peopleFullyVaccinatedPerHundred);
    }
    listDestroy(&calculatedTopN);
    sortedTopN = NULL;

}


PtList sortTopN(PtList ptList)
{
    PtList sortTopN = ptList;
    int size;
    listSize(sortTopN, &size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            ListElem elem1, elem2, elemO;
            listGet(sortTopN, j, &elem1);
            listGet(sortTopN, j + 1, &elem2);
            if (elem1.peopleVaccinatedPerHundred < elem2.peopleVaccinatedPerHundred)
            {
                listSet(sortTopN, j + 1, elem1, &elemO);
                listSet(sortTopN, j, elem2, &elemO);
            }
        }
    }
    return sortTopN;
}

PtList calcTopN(PtList list)
{
    int size;
    listSize(list, &size);

    PtList countryList = listCreate();
    int countryListSize;
    for (int i = 0; i < size; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        listSize(countryList, &countryListSize);
        int count = 0;
        for (int j = 0; j < countryListSize; j++)
        {
            ListElem elemAux;
            listGet(countryList, j, &elemAux);
            if (strcmp(elem.country, elemAux.country) == 0)
            {
                if (daysDiffDate(elem.date, elemAux.date) < 0)
                {
                    
                    if ( elemAux.peopleVaccinatedPerHundred != -1
                        && elemAux.peopleFullyVaccinatedPerHundred != -1)
                    {
                        ListElem oldElem;
                        listRemove(countryList, j, &oldElem);
                        strcpy(oldElem.country, elemAux.country);

                        oldElem.peopleVaccinatedPerHundred = elemAux.peopleVaccinatedPerHundred;
                        oldElem.peopleFullyVaccinatedPerHundred = elemAux.peopleFullyVaccinatedPerHundred;
                        oldElem.date = elemAux.date;
                        listAdd(countryList, j, oldElem);
                    }
                }
                count++;
            }
        }
        if (count == 0)
        {
            ListElem countryAdd;
            strcpy(countryAdd.country, elem.country);
            countryAdd.peopleVaccinatedPerHundred = (elem.peopleVaccinatedPerHundred == -1 ? 0 : elem.peopleVaccinatedPerHundred);
            countryAdd.peopleFullyVaccinatedPerHundred = (elem.peopleFullyVaccinatedPerHundred == -1 ? 0 : elem.peopleFullyVaccinatedPerHundred);
            countryAdd.date = elem.date;
            listAdd(countryList, countryListSize, countryAdd);
        }
    }
    return countryList;
}

void averageGlobal(PtList ptList)
{
    int size = 0, count = 0;
    float avgGlobal = 0;

    ListElem *ptElem = malloc(sizeof(ListElem));

    listSize(ptList, &size);

    for (int i = 0; i < size; i++)
    {
        listGet(ptList, i, ptElem);

        if (ptElem->dailyVaccination >= 0)
        {
            avgGlobal = avgGlobal + (int)ptElem->dailyVaccination;
        }

        count++;
    }

    avgGlobal /= count;

    printf("Population Average of Daily Vaccinations = %.2f\n", avgGlobal);

    free(ptElem);
}

void averagePerCountry(PtList ptList)
{
    int size = 0, count = 0;
    float avgPerCountry = 0;

    listSize(ptList, &size);
    PtMap mapAux = mapCreate();

    printf("\nPopulation Average of Daily Vaccination by Country");
    for (int i = 0; i < size; i++)
    {
        ListElem ptElem;
        listGet(ptList, i, &ptElem);
        MapValue aux, auxDelete;
        if (!mapContains(mapAux, stringCodeCreate(ptElem.country)))
        {
            aux.urbanPopulation = ptElem.dailyVaccination;
            aux.area = 1;
            mapPut(mapAux, stringCodeCreate(ptElem.country), aux);
        }
        else
        {
            mapGet(mapAux, stringCodeCreate(ptElem.country), &aux);
            aux.urbanPopulation += ptElem.dailyVaccination;
            aux.area++;
            mapRemove(mapAux, stringCodeCreate(ptElem.country), &auxDelete);
            mapPut(mapAux, stringCodeCreate(ptElem.country), aux);
        }
    }

    int sizeAux;
    mapSize(mapAux, &sizeAux);
    MapKey *keys = mapKeys(mapAux);

    for (int i = 0; i < sizeAux; i++)
    {
        MapValue aux;
        mapGet(mapAux, keys[i], &aux);
        printf("\n%35s %.0f", keys[i].code, aux.urbanPopulation / aux.area);
    }

    mapDestroy(&mapAux);
    free(keys);
}

void getReportsOfCountry(PtList list, char *country, PtList *countryPickedList)
{
    int size = 0;
    listSize(list, &size);

    int sizeCountryList = 0;

    for (int i = 0; i <= size; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        if (strcmp(country, elem.country) == 0)
        {
            listAdd(*countryPickedList, sizeCountryList - 1, elem);
            sizeCountryList++;
        }
    }
}

void countryS(PtMap *map)
{

    MapKey *keys;

    keys = sortCountryByHabitents(map);

    MapValue c1;

    int n;
    mapSize(*map, &n);

    for (int i = 0; i < n; i++)
    {
        mapGet(*map, keys[i], &c1);
        mapValuePrint(c1);
    }

    free(keys);
}

MapKey *sortCountryByHabitents(PtMap *map)
{

    int i, j;
    MapValue *c1, *c2;

    int n;
    mapSize(*map, &n);

    MapKey *keys;
    MapKey keySafe;

    c1 = malloc(sizeof(MapValue));
    c2 = malloc(sizeof(MapValue));

    keys = mapKeys(*map);

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
        {
            mapGet(*map, keys[j], c1);
            mapGet(*map, keys[j + 1], c2);
            if (c1->population > c2->population)
            {
                keySafe = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = keySafe;
            }
        }

    free(c1);
    free(c2);

    return keys;
}

void listC(PtList *ptList)
{
    PtMap uniqueCountries = getUniqueCountries(*ptList);

    MapKey *keys = mapKeys(uniqueCountries);

    int size;
    mapSize(uniqueCountries, &size);
    for (int i = 0; i < size; i++)
    {
        printf("\n Country: %s", keys[i].code);
    }
    free(keys);
    mapDestroy(&uniqueCountries);
}

void listV(PtList *ptList)
{

    PtMap uniqueVaccines = getUniqueVaccines(*ptList);

    MapKey *keys = mapKeys(uniqueVaccines);

    int size;
    mapSize(uniqueVaccines, &size);
    for (int i = 0; i < size; i++)
    {
        printf("\n Vaccine: %s", keys[i].code);
    }
    printf("\n");

    free(keys);
    mapDestroy(&uniqueVaccines);
}

void showV(PtList *ptList)
{
    PtMap uniqueVaccines = getUniqueVaccines(*ptList);

    int sizeUV, size;

    MapKey *keysUV = mapKeys(uniqueVaccines);

    listSize(*ptList, &size);
    mapSize(uniqueVaccines, &sizeUV);
    for (int i = 0; i < sizeUV; i++)
    {
        printf("\n\nCountries that use %s vacinne\n", keysUV[i].code);
        for (int j = 0; j < size; j++)
        {
            ListElem countryAuxElem, countryAuxElem2;
            listGet(*ptList, j, &countryAuxElem);
            listGet(*ptList, j + 1, &countryAuxElem2);
            for (int k = 0; k < 5; k++)
            {
                if (strcmp(keysUV[i].code, countryAuxElem.vaccines[k]) == 0)
                {
                    if (strcmp(countryAuxElem.country, countryAuxElem2.country) != 0)
                    {
                        printf("%s\n", countryAuxElem.country);
                    }
                }
            }
        }
    }
    free(keysUV);
    mapDestroy(&uniqueVaccines);
}

PtMap getUniqueVaccines(PtList list)
{

    int size;
    listSize(list, &size);

    PtMap uniqueVaccinesMap = mapCreate();

    for (int i = 0; i <= size; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        for (int j = 0; j < 5; j++)
        {
            if (strcmp(elem.vaccines[j], "") != 0)
            {
                char *pos;
                if ((pos = strchr(elem.vaccines[j], '\r')) != NULL)
                {
                    *pos = '\0';
                }
                StringCode keyVaccines = stringCodeCreate(elem.vaccines[j]);

                if (!mapContains(uniqueVaccinesMap, keyVaccines))
                {
                    Country vaccineAux;
                    mapPut(uniqueVaccinesMap, keyVaccines, vaccineAux);
                }
            }
        }
    }

    return uniqueVaccinesMap;
}

PtMap getUniqueCountries(PtList list)
{

    PtMap countryUniqueMap = mapCreate();

    int size = 0;
    listSize(list, &size);

    for (int i = 0; i <= size; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        if (elem.dailyVaccination > 0)
        {
            StringCode keyCountry = stringCodeCreate(elem.country);
            if (!mapContains(countryUniqueMap, keyCountry))
            {
                
                Country countryAux = countryCreate("","",0,0,0,0,0);
                mapPut(countryUniqueMap, keyCountry, countryAux);
            }
        }
    }
    return countryUniqueMap;
}

void regions(PtList list, PtMap map)
{
    PtList regions = regionsList(map);

    PtList countries = countryLatestData(list);

    MapValue *values = mapValues(map);

    int regionSize, size;
    listSize(regions, &regionSize);
    mapSize(map, &size);
    printf("Region               %%WordS  %%TVac  %%PVac %%PFVac   DVac_Million\n");
    float ttVH = 0, tpVH = 0, tpFVH = 0;

    int countrySize;
    listSize(countries, &countrySize);
    for (int i = 0; i < countrySize; i++)
    {
        ListElem countryElem;
        listGet(countries, i, &countryElem);
        ttVH += (countryElem.totalVaccinationsPerHundred == -1 ? 0 : countryElem.totalVaccinationsPerHundred);
        tpVH += (countryElem.peopleVaccinatedPerHundred == -1 ? 0 : countryElem.peopleVaccinatedPerHundred);
        tpFVH += (countryElem.peopleFullyVaccinatedPerHundred == -1 ? 0 : countryElem.peopleFullyVaccinatedPerHundred);
    }

    for (int i = 0; i < regionSize; i++)
    {
        float worldShare = 0, tVH = 0, pVH = 0, pFVH = 0, dVM = 0;
        ListElem region;
        listGet(regions, i, &region);
        for (int j = 0; j < size; j++)
        {
            if (strcmp(values[j].region, region.country) == 0)
            {
                int countrySize;
                listSize(countries, &countrySize);
                for (int z = 0; z < countrySize; z++)
                {
                    ListElem countryElem;
                    listGet(countries, z, &countryElem);
                    if (strcmp(values[j].country, countryElem.country) == 0)
                    {
                        tVH += countryElem.totalVaccinationsPerHundred;
                        pVH += countryElem.peopleVaccinatedPerHundred;
                        pFVH += countryElem.peopleFullyVaccinatedPerHundred;
                        dVM += countryElem.dailyVaccinationsPerMillion;
                        worldShare += values[j].worldShare;
                    }
                }
            }
        }

        printf("%-20s | %-4.2f%% | %-4.2f%% | %-4.2f%% | %-4.2f%% | %-4.0f\n", region.country, worldShare, (tVH / ttVH * 100), (pVH / tpVH * 100), (pFVH / tpFVH * 100), dVM);
    }

    listDestroy(&regions);
    listDestroy(&countries);
    free(values);
}

PtList regionsList(PtMap map)
{
    MapValue *regionsAux = mapValues(map);
    int size;
    mapSize(map, &size);

    PtList regionsList = listCreate();
    int regionListSize;
    for (int i = 0; i < size; i++)
    {
        listSize(regionsList, &regionListSize);
        int count = 0;
        for (int j = 0; j < regionListSize; j++)
        {
            ListElem elem;
            listGet(regionsList, j, &elem);
            if (strcmp(regionsAux[i].region, elem.country) == 0)
            {
                count++;
            }
        }
        if (count == 0)
        {
            ListElem regionAdd;
            strcpy(regionAdd.country, regionsAux[i].region);
            listAdd(regionsList, regionListSize, regionAdd);
        }
    }
    free(regionsAux);
    return regionsList;
}

PtList countryLatestData(PtList list)
{
    int size;
    listSize(list, &size);

    PtList countryList = listCreate();
    int countryListSize;
    for (int i = 0; i < size; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        listSize(countryList, &countryListSize);
        int count = 0;
        for (int j = 0; j < countryListSize; j++)
        {
            ListElem elemAux;
            listGet(countryList, j, &elemAux);
            if (strcmp(elem.country, elemAux.country) == 0)
            {
                if (daysDiffDate(elem.date, elemAux.date) < 0)
                {
                    
                    if (elemAux.totalVaccinationsPerHundred != -1 
                        && elemAux.peopleVaccinatedPerHundred != -1
                        && elemAux.peopleFullyVaccinatedPerHundred != -1
                        && elemAux.dailyVaccinationsPerMillion != -1)
                    {
                        ListElem oldElem;
                        listRemove(countryList, j, &oldElem);
                        strcpy(oldElem.country, elemAux.country);

                        oldElem.totalVaccinationsPerHundred = elemAux.totalVaccinationsPerHundred;
                        oldElem.peopleVaccinatedPerHundred = elemAux.peopleVaccinatedPerHundred;
                        oldElem.peopleFullyVaccinatedPerHundred = elemAux.peopleFullyVaccinatedPerHundred;
                        oldElem.dailyVaccinationsPerMillion = elemAux.dailyVaccinationsPerMillion;
                        oldElem.date = elemAux.date;
                        listAdd(countryList, j, oldElem);
                    }
                }
                count++;
            }
        }
        if (count == 0)
        {
            ListElem countryAdd;
            strcpy(countryAdd.country, elem.country);
            countryAdd.totalVaccinationsPerHundred = (elem.totalVaccinationsPerHundred == -1 ? 0 : elem.totalVaccinationsPerHundred);
            countryAdd.peopleVaccinatedPerHundred = (elem.peopleVaccinatedPerHundred == -1 ? 0 : elem.peopleVaccinatedPerHundred);
            countryAdd.peopleFullyVaccinatedPerHundred = (elem.peopleFullyVaccinatedPerHundred == -1 ? 0 : elem.peopleFullyVaccinatedPerHundred);
            countryAdd.dailyVaccinationsPerMillion = (elem.dailyVaccinationsPerMillion == -1 ? 0 : elem.dailyVaccinationsPerMillion);
            countryAdd.date = elem.date;
            listAdd(countryList, countryListSize, countryAdd);
        }
    }
    return countryList;
}