/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>
#include <string.h>

void mapKeyPrint(MapKey key) {
	printf("%s \n", key.code);
}

void mapValuePrint(MapValue value) {
	countryPrint(&value);
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	return strcmp(key1.code,key2.code); 
}