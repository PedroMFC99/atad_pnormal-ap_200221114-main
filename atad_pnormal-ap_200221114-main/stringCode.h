#pragma once

typedef char String[255];

typedef struct stringCode{
    String code;
} StringCode;

StringCode stringCodeCreate(char *str);