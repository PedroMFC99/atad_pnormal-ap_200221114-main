#include <string.h>
#include "stringCode.h"


StringCode stringCodeCreate(char *str){

    StringCode string;
    strcpy(string.code, str);
    return string;
}