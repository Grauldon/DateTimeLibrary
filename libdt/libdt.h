/*
 *	Copyright © Gregory McLendon
 */

#ifndef LIBDT_H_
#define LIBDT_H_

#include <windows.h>
#include "dll.h"

#ifdef __cplusplus							// C interface export
extern "C" {
#endif

DTLIB BOOL get_time_struct(struct tm *n);
DTLIB BOOL update_time_struct(char *date, struct tm *n);
DTLIB time_t basedate(struct tm *n);
DTLIB char *getwdname(int x);
DTLIB BOOL get_curr_date_time_str(char *date);
DTLIB BOOL get_curr_date_time(struct tm *n);
int conv_dt_str_int (char *dt);

BOOL (*dt_fp_init)(struct tm *n);
BOOL (*dt_fp_upd)(char *date, struct tm *n);
time_t (*dt_fp_base)(struct tm *n);
char *(*dt_fp_wdname)(int x);
BOOL (*dt_fp_cdttm_str)(char *date);
BOOL (*dt_fp_cdttm)(struct tm *n);

char wdname[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#ifdef __cplusplus							// End of C interface export
}
#endif

#endif /* LIBDT_H_ */
