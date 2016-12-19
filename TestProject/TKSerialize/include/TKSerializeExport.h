#pragma once

#ifdef TKSERIALIZE_EXPORTS
	#define TKSNSEXTENDUI_API __declspec(dllexport)
#else
	#define TKSNSEXTENDUI_API __declspec(dllimport)
#endif