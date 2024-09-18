#pragma once

typedef struct date {
	int day, month, year;
} Date;

/**
 * @brief Create a Date object
 * 
 * @param day [in] day of month.
 * @param month [in] month, where january = 1
 * @param year [in] year
 * @return Date object initialized with arguments. 
 */
Date createDate(int day, int month, int year);

/**
 * @brief Sums a specified amount of days to an existing Date.
 * 
 * @param d [in] a date to add days to.
 * @param days [in] number of days to add.
 * @return Resulting Date object
 */
Date addDaysToDate(Date d, int days);

/**
 * @brief Returns the difference (in days) between two dates.
 * 
 * @param d1 [in] a date.
 * @param d2 [in] another date.
 * @return the difference in days (d1 - d2)
 */
int daysDiffDate(Date d1, Date d2);

