#pragma once

#ifdef MYUPDATE_EXPORTS
#define MYUPDATE_DLL __declspec(dllexport)
#else
#define MYUPDATE_DLL __declspec(dllimport)
#endif