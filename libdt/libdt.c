/*
 *	Copyright © Gregory McLendon
 */

#define DTLIB_EXPORT

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "libdt.h"

DTLIB BOOL get_time_struct(struct tm *n)
{
	time_t timevalue;
	errno_t error;

	time(&timevalue);
	error = localtime_s(n, &timevalue);

	if (error)
		return FALSE;
	else
		return TRUE;
}

DTLIB BOOL update_time_struct(char * date, struct tm *n)
{
	char str[5];
	time_t result;

	n->tm_isdst = -1;

	strncpy_s(str, 5, date, 2);
	n->tm_mon = conv_dt_str_int (str);

	strncpy_s(str, 5, date+2, 2);
	n->tm_mday = conv_dt_str_int (str);

	strncpy_s(str, 5, date+4, 4);
	n->tm_year = conv_dt_str_int (str);
	str[2] = '\0';

	strncpy_s(str, 5, date+8, 2);
	n->tm_hour = conv_dt_str_int (str);

	strncpy_s(str, 5, date+10, 2);
	n->tm_min = conv_dt_str_int (str);

	strncpy_s(str, 5, date+12, 2);
	n->tm_sec = conv_dt_str_int (str);

	n->tm_year -= 1900;
	n->tm_mon--;

	result = mktime(n);

	n->tm_year += 1900;
	n->tm_mon++;

	if (result < 0) {
		printf("update_time_struct: Error in updating date information\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

DTLIB time_t basedate(struct tm *n)
{
    int x = 0;

    n->tm_mon = 1;
    n->tm_mday = 1;

    mktime (n);

    x = 7 - n->tm_wday;
    n->tm_mday += x;

    return mktime (n);
}

DTLIB char *getwdname(int x)
{
	char *pstr = wdname[x];

	if (x < 7)
		return pstr;
	else
		return "Invalid data";
}

DTLIB BOOL get_curr_date_time_str(char *date)
{
	struct tm time_info;
	struct tm * ti = &time_info;

	if (get_curr_date_time(ti)) {
		ti->tm_year -= 1900;
		ti->tm_mon--;

		if (strftime(date, 15, "%m%d%Y%H%M%S", ti)) {
			return TRUE;
		}
	}

	return FALSE;
}

DTLIB BOOL get_curr_date_time(struct tm *n)
{
	time_t timevalue;

	time(&timevalue);

	if (localtime_s(n, &timevalue)) {
		return FALSE;
	} else {
		n->tm_year += 1900;
		n->tm_mon++;
		return TRUE;
	}
}

int conv_dt_str_int (char *dt)
{

	double e = 0;
	double exp = 0;
	double n = 0;

	for (int i = ((int)strlen(dt) - 1); i >= 0; i--) {
		e = dt[i] - '0';
		n = n + (e*pow(10, exp));
		exp++;
	}

	return (int)n;
}
