/*
 *	Copyright © Gregory McLendon
 */

#ifndef DLL_H_
#define DLL_H_

#ifdef DTLIB_EXPORT					// Determine import or export of DLL
#define DTLIB __declspec(dllexport)
#else
#define DTLIB __declspec(dllimport)
#endif

#endif /* DLL_H_ */
