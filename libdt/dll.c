/*
 *	Copyright © Gregory McLendon
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <windows.h>
#include "dll.h"

BOOL CDECL DllMain(HINSTANCE hinstDll, DWORD fwdReason, LPVOID lpvReserved)
{
	BOOL result = TRUE;

	switch (fwdReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return result;
}

#ifdef __cplusplus
}
#endif
