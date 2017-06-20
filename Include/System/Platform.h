#ifndef PLATFORM_H
#define PLATFORM_H

//
// NOTE:
//
// Define pre-processor macros for DLL export/import
// + system macros
//
#include <iostream>

#ifdef _WIN32
	#define EROS_SYS_WINDOWS

	// Defined to disable <windows.h> from defining the min/max macros (SDL has issues with this)
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif

#elif defined(__LINUX__)
	#define EROS_SYS_LINUX

#elif defined(__APPLE__)
	#define ERROS_SYS_MACOS
#endif

// NOTE:
// If you want to build a static library, it just builds directly into the library file.
// This can require put a strain on the hardware running it! We choose to build dynamically


// Dynamic build
#ifndef EROS_STATIC_BUILD

	#ifdef EROS_SYS_WINDOWS

		#ifdef EROS_NONCLIENT_BUILD
			#define EROS_API __declspec(dllexport)
		#else
			#define EROS_API __declspec(dllimport)
		#endif

		// Visual c++ compiler warning C4251 disable
		#ifdef _MSC_VER
			#pragma warning(disable : 4251)
		#endif

	#else // Linux / OSX

		// Check GNUC >= 4 (for linux development)
		#ifdef __GNUC__ >= 4

			#define EROS_API __attribute__ ((__visibility__("default")))
		#else

			#define EROS_API EROS_API
		#endif

	#endif

#else
	#define EROS_API EROS_API
#endif


// DEBUG 
#if EROS_ASSERTIONS_ENABLED // Used to strip assertions later 
#define EROS_TRAP(expr) \
if (expr) { } \
else \
{ \
do { \
_CrtDbgReport( \
_CRT_ASSERT, __FILE__, __LINE__, #expr, NULL); \
_CrtDbgBreak(); \
} while (1); \
}
#else
#define EROS_TRAP(expr) // do nothing
#endif



#endif /* PLATFORM_H */
