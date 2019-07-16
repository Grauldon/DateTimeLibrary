/*
 *	Copyright © Gregory McLendon
 */

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>

BOOL init_libr(void);
BOOL close_libr(void);
void display_time_struct(struct tm *dis_time);

HINSTANCE dllhandle = NULL;

BOOL (*dt_fp_init)(struct tm *n) = NULL;
BOOL (*dt_fp_upd)(char *date, struct tm *n) = NULL;
time_t(*dt_fp_base)(struct tm *n);
char *(*dt_fp_wdname)(int x) = NULL;
BOOL(*dt_fp_cdttm_str)(char *date) = NULL;
BOOL(*dt_fp_cdttm)(struct tm *n) = NULL;

int main (int argc, char ** args)
{
	BOOL stop_process = 0;
	BOOL use_current = 1;

	char datetime[15] = "MMDDCCYYHHMMSS";

	struct tm date_time;
	struct tm *dt = &date_time;

	stop_process = init_libr();

	if (stop_process) {
		if (argc == 2) {
			if (strlen(args[1]) == 14) {
				for (int i = 0; i < 14; i++) {
					if (!isdigit(args[1][i])) {
						break;
					} else {
						if (i == 13) {
							use_current = 0;
						}
					}
				}
			}
		}

		if (use_current) {
			if (!dt_fp_cdttm_str(datetime)) {
				printf("Error - Getting current date as a string failed\n");
			}
		} else {
			strcpy_s(datetime, 15, args[1]);
		}

		if (!dt_fp_init(dt))
			printf("Error - Date initialization failed\n");

		if (!dt_fp_upd(datetime, dt)) {
			printf("Error - Update failed\n");
		} else {
			display_time_struct(dt);
		}

		printf("\n");

		if (dt_fp_cdttm(dt)) {
			display_time_struct(dt);
		} else {
			printf("Error - getting current and displaying current time failed.");
		}

		if (!close_libr()) {
			printf("Erroring closing library\n");
		}
	}

    return EXIT_SUCCESS;
}

BOOL init_libr(void)
{
	short success = 1;

	dllhandle = LoadLibrary((LPCSTR) "E:\\DateTimeLibrary\\x64\\Debug\\dtlib.dll");

	if (NULL != dllhandle) {

		dt_fp_init = (BOOL (*)(struct tm *n))GetProcAddress(dllhandle, "get_time_struct");
		if (NULL == dt_fp_init) {
			printf("Error linking - get_time_struct\tdt_fp_init is %p\n", dt_fp_init);
			success = 0;
		}

		dt_fp_upd = (BOOL (*)(char *date, struct tm *n))GetProcAddress(dllhandle, "update_time_struct");
		if (NULL == dt_fp_upd) {
			printf("Error linking - update_time_struct\tdt_fp_upd is %p\n", dt_fp_upd);
			success = 0;
		}

		dt_fp_base = (time_t (*)(struct tm *n))GetProcAddress(dllhandle, "basedate");
		if (NULL == dt_fp_base) {
			printf("Error linking - getting the time_t value\tdt_fp_base is %p\n", dt_fp_base);
			success = 0;
		}

		dt_fp_wdname = (char *(*)(int x))GetProcAddress(dllhandle, "getwdname");
		if (NULL == dt_fp_wdname) {
			printf("Error linking - get week day name\tdt_fp_wdname is %p\n", dt_fp_wdname);
			success = 0;
		}

		dt_fp_cdttm_str = (BOOL (*)(char *date))GetProcAddress(dllhandle, "get_curr_date_time_str");
		if (NULL == dt_fp_cdttm_str) {
			printf("Error linking - get current date and time string\tdt_fp_cdttm_str is %p\n", dt_fp_cdttm_str);
			success = 0;
		}

		dt_fp_cdttm = (BOOL (*)(struct tm *n))GetProcAddress(dllhandle, "get_curr_date_time");
		if (NULL == dt_fp_cdttm) {
			printf("Error linking - get current date and time\tdt_fp_cdttm is %p\n", dt_fp_cdttm);
			success = 0;
		}
	}
	else {
		printf("Error - loading library\n");
		success = 0;
	}

	return success;
}

BOOL close_libr(void)
{
	short success = 1;

	FreeLibrary(dllhandle);

	return success;
}

void display_time_struct(struct tm *display_time)
{
	printf("Date is %.2d/%.2d/%4d\n", (display_time->tm_mon), display_time->tm_mday, (display_time->tm_year));

	switch (display_time->tm_wday) {
	case 0:
		printf("It's %s, the 7th day of the week\n", dt_fp_wdname(display_time->tm_wday));
		break;
	case 1:
		printf("It's %s, the %dst day of the week\n", dt_fp_wdname(display_time->tm_wday), display_time->tm_wday);
		break;
	case 2:
		printf("It's %s, the %dnd day of the week\n", dt_fp_wdname(display_time->tm_wday), display_time->tm_wday);
		break;
	case 3:
		printf("It's %s, the %drd day of the week\n", dt_fp_wdname(display_time->tm_wday), display_time->tm_wday);
		break;
	default:
		printf("It's %s, the %dth day of the week\n", dt_fp_wdname(display_time->tm_wday), display_time->tm_wday);
		break;
	}

	switch (display_time->tm_yday % 10) {
	case 1:
		printf("It's the %dst day this year\n", display_time->tm_yday);
		break;
	case 2:
		printf("It's the %dnd day this year\n", display_time->tm_yday);
		break;
	case 3:
		printf("It's the %drd day this year\n", display_time->tm_yday);
		break;
	default:
		printf("It's the %dth day this year\n", display_time->tm_yday);
		break;
	}

	printf("The time is: %.2d:%.2d:%.2d\n\n", display_time->tm_hour, display_time->tm_min, display_time->tm_sec);
}
