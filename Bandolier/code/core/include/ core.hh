#ifndef BANDOLIER_CORE_HH
#define BANDOLIER_CORE_HH

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
/* Windows x64  */
#define BNDLR_PLATFORM_WINDOWS
#else
/* Windows x86 */
		#error "x86 not supported"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator not supported"
	#elif TARGET_OS_IPHONE == 1
		#define BNDLR_PLATFORM_IOS
		#error "IOS not supported"
	#elif TARGET_OS_MAC == 1
		#define BNDLR_PLATFORM_MACOS
		#error "MacOS not supported"
	#else
		#error "Unknown Apple platform"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define BNDLR_PLATFORM_ANDROID
	#error "Android not supported"
#elif defined(__linux__)
	#define BNDLR_PLATFORM_LINUX
	#error "Linux not supported"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform"
#endif // End of platform detection

#endif //BANDOLIER_CORE_HH
