#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include <list.h>

int DLL_EXPORT compare(list_t * list1);
void DLL_EXPORT reaction(list_t * list1);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
