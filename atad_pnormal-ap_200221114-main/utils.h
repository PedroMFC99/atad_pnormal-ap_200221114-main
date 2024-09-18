/**
 * @file utils.h
 * @authors Diogo Letras, Nº 200221114, Turma: 1
 * Luís Góias, Nº 200221134, Turma: 4
 * Pedro Cunha, Nº 200221086, Turma: 4
 * Tiago Vaz, Nº 200221089, Turma: 1
 * 
 * Docentes: Aníbal Ponte e Miguel López
 * 
 * @brief All console commands and auxiliary functions
 * @version 1.0
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief Loads data from the country_data_2020.csv file to a map
 * 
 * @param ptMap map where the data is saved to
 * @return int number of added countries
 */
int loadc(PtMap *ptMap);

/**
 * @brief Loads data from the country_vaccinations.csv file to a list
 * 
 * @param ptList List to add to
 * @param ptMap Coutry map
 * @return int Number of loaded vaccines
 */
int loadv(PtList *ptList, PtMap *ptMap);

/**
 * @brief Shows vaccination data
 * 
 * @param ptList Vaccine list
 * @param choice ALL or SAMPLE
 */
void showAll(PtList *ptList, char *choice);

/**
 * @brief Shows vaccination info of selected country
 * 
 * @param ptList Vaccine list
 * @param country Name of the country
 */
void showC(PtList *ptList, char *country);

/**
 * @brief Clears the data from both the list and map
 * 
 * @param ptList Vaccine list
 * @param ptMap Country list
 * @return int (0 if successful)
 */
int clear(PtList ptList, PtMap ptMap);

/**
 * @brief Clears the list and map to quit the program
 * 
 * @param ptList Vaccine list
 * @param ptMap Country list
 */
void quitCommand(PtList *ptList, PtMap *ptMap);

/**
 * @brief Calculates the daily global average of vaccination
 * 
 * @param ptList Vaccine list
 */
void averageGlobal(PtList ptList);

/**
 * @brief Calculates the daily average per country of vaccination
 * 
 * @param ptList Vaccine list
 */
void averagePerCountry(PtList ptList);

/**
 * @brief Get the reports of a certain country
 * 
 * @param list Vaccine list
 * @param country Name of a country
 * @param countryPickedList 
 */
void getReportsOfCountry(PtList list, char *country, PtList *countryPickedList);

/**
 * @brief Shows country data sorted by number of inhabitants in decreasing order.
 * 
 * @param map Country map
 */
void countryS(PtMap *map);

/**
 * @brief Sorts countries by habitants
 * 
 * @param map Country map
 * @return MapKey* 
 */
MapKey* sortCountryByHabitents(PtMap *map);

/**
 * @brief Shows the list of countries with vaccination data
 * 
 * @param ptList Vaccine list
 */
void listC(PtList *ptList);

/**
 * @brief Shows the list of vaccines in the vaccination records (unique names)
 * 
 * @param ptList Vaccine list
 */
void listV(PtList *ptList);

/**
 * @brief Shows for each of the known vaccines, the list of countries that used it in vaccination
 * 
 * @param ptList Vaccine list
 */
void showV(PtList *ptList);

/**
 * @brief Get unique countries
 * 
 * @param list Vaccine list
 * @return PtMap Map with unique countries
 */
PtMap getUniqueCountries(PtList list);

/**
 * @brief Get unique vaccines
 * 
 * @param list Vaccine list
 * @return PtMap Map with unique vaccines
 */
PtMap getUniqueVaccines(PtList list);

/**
 * @brief Shows in decreasing form the vaccination data of N countries, 
 * being the criterion descending by the attribute "peopleVaccinatedPerHundred"
 * 
 * @param ptList Vaccine list
 * @param n Number of countries
 */
void topN(PtList ptList, int n);

/**
 * @brief Auxiliary function, used to sort the topN List
 * 
 * @param ptList Vaccine list
 * @return PtList Sorted List
 */
PtList sortTopN(PtList ptList);

/**
 * @brief Auxiliary function, used to calculate the topN List
 * 
 * @param ptList Vaccine list
 * @return PtList Calculated List
 */
PtList calcTopN(PtList ptList);

/**
 * @brief Shows vaccination data, aggregated by world region and also the percentage of population (worldShare).
 * 
 * @param list Vaccine list
 * @param map Country map
 */
void regions(PtList list, PtMap map);

/**
 * @brief Auxiliary function, creates a List of world regions
 * 
 * @param map Country map
 * @return PtList List with world regions
 */
PtList regionsList(PtMap map);

/**
 * @brief Returns the latest vaccination data of the countries 
 * 
 * @param list Vaccine list
 * @return PtList List with the latest vaccination data
 */
PtList countryLatestData(PtList list);

