#pragma once
#ifdef AMC_WINDOW
	#ifdef AMC_DLL
		#define AMC_API __declspec(dllexport)
	#else
		#define AMC_API __declspec(dllimport)
	#endif // AMC_DLL

#endif // AMC_WINDOW
#define BIT(x) (1<<x)