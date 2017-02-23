#pragma once

#ifdef TKSERIALIZE_EXPORTS
	#define TKSERIALIZE_API __declspec(dllexport)
#else
	#define TKSERIALIZE_API __declspec(dllimport)
#endif