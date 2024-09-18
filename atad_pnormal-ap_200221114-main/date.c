#include "date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Date createDate(int day, int month, int year){
    Date d;
    d.day=day;
    d.month=month;
    d.year=year;
    return d;
}

Date addDaysToDate(Date d,int days) {
    Date newDate;
    struct tm tm;
   
    memset(&tm,0,sizeof(struct tm));
    tm.tm_year = d.year-1900; 
    tm.tm_mon = d.month-1; // 0 = Jan, 1 = Feb etc
    tm.tm_mday = d.day;
    tm.tm_mday += days;
    mktime(&tm);
    newDate.day = tm.tm_mday;
    newDate.month = tm.tm_mon+1;
    newDate.year =  tm.tm_year+1900;
    return newDate;
}

int daysDiffDate(Date d1,Date d2) {

    struct tm time1, time2;
    double seconds;

    memset(&time1,0,sizeof(struct tm));
    memset(&time2,0,sizeof(struct tm));

    time1.tm_mday = d1.day; 
    time1.tm_mon = d1.month-1;   
    time1.tm_year = d1.year-1900;
    
    time2.tm_mday = d2.day; 
    time2.tm_mon = d2.month-1;   
    time2.tm_year = d2.year-1900;

    seconds = difftime(mktime(&time1),mktime(&time2));

    return (int) (seconds / (3600*24));
}




