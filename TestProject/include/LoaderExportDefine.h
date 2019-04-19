#ifndef _LOADEREXPORTDEFINE_H_
#define _LOADEREXPORTDEFINE_H_


#ifdef LOADER_EXPORTS
#define LOADER_API __declspec(dllexport)
#else
#define LOADER_API __declspec(dllimport)
#endif


#endif
