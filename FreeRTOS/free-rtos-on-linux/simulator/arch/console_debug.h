
#ifndef __CONSOLE_DEBUG_H__
#define __CONSOLE_DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "simulator_config.h"

typedef int log_level_t;

#define console_print							printf

#define CONSOLE_DEBUG_LEVEL_VERBOSE				0
#define CONSOLE_DEBUG_LEVEL_INFO				1
#define CONSOLE_DEBUG_LEVEL_WARNING				2
#define CONSOLE_DEBUG_LEVEL_ERROR				3
#define CONSOLE_DEBUG_LEVEL_FATAL				4
#define CONSOLE_DEBUG_LEVEL_OFF					5

#if CONSOLE_DEBUG_ANSI_COLOR_ENABLE
#define CONSOLE_DEBUG_ANSI_COLOR_RED			"\033[0;31m"
#define CONSOLE_DEBUG_ANSI_COLOR_GRE			"\033[0;32m"
#define CONSOLE_DEBUG_ANSI_COLOR_YEL			"\033[0;33m"
#define CONSOLE_DEBUG_ANSI_COLOR_OFF			"\033[0m"
#else
#define CONSOLE_DEBUG_ANSI_COLOR_RED			NULL
#define CONSOLE_DEBUG_ANSI_COLOR_GRE			NULL
#define CONSOLE_DEBUG_ANSI_COLOR_YEL			NULL
#define CONSOLE_DEBUG_ANSI_COLOR_OFF			NULL
#endif

void console_debug_init(void);
void console_debug_begin(const char* ansi_color);
void console_debug_end(const char* ansi_color);
void console_debug_dump_hex(const void *data, int len,const char *tips);

#ifndef CONSOLE_DEBUG_LEVEL
#define CONSOLE_DEBUG_LEVEL						CONSOLE_DEBUG_LEVEL_VERBOSE
#endif

#define PRINT(_fmt_, ...)						console_print(_fmt_"\r\n", ##__VA_ARGS__)

#if CONSOLE_DEBUG_LEVEL <= CONSOLE_DEBUG_LEVEL_INFO
#define INFO(_fmt_, ...) \
	do{ \
		extern log_level_t g_log_level; \
		if(g_log_level <= CONSOLE_DEBUG_LEVEL_INFO){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_GRE); \
			console_print("[I] "_fmt_, ##__VA_ARGS__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF);\
		} \
	}while(0)

#define INFO_TAG(TAG, _fmt_, ...) \
	do{ \
		if((CONSOLE_DEBUG_LEVEL) <= CONSOLE_DEBUG_LEVEL_INFO){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_GRE); \
			console_print("[I]: [%s] "_fmt_, TAG, ##__VA_ARGS__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#else

#define INFO(_fmt_, ...) \
	do{}while(0)

#define INFO_TAG(TAG, _fmt_, ...) \
	do{}while(0)
#endif

#if MIIO_CONSOLE_DEBUG_LEVEL <= CONSOLE_DEBUG_LEVEL_WARNING
#define WARN(_fmt_, ...) \
	do{ \
		extern log_level_t g_log_level; \
		if(g_log_level <= CONSOLE_DEBUG_LEVEL_WARNING){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_YEL); \
			console_print("[W] "_fmt_" (%s, %d)", ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#define WARN_TAG(TAG, _fmt_, ...) \
	do{ \
		if((CONSOLE_DEBUG_LEVEL) <= CONSOLE_DEBUG_LEVEL_WARNING){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_YEL); \
			console_print("[W]: [%s] "_fmt_" (%s, %d)", TAG, ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#else
#define WARN(_fmt_, ...) \
	do{}while(0)
#define WARN_TAG(TAG, _fmt_, ...) \
	do{}while(0)
#endif

#if MIIO_CONSOLE_DEBUG_LEVEL <= CONSOLE_DEBUG_LEVEL_ERROR
#define ERROR(_fmt_, ...) \
	do{\
		extern log_level_t g_log_level; \
		if(g_log_level <= CONSOLE_DEBUG_LEVEL_ERROR){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_RED); \
			console_print("[E] "_fmt_" (%s, %d)", ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF);\
		} \
	}while(0)
#define ERROR_TAG(TAG, _fmt_, ...) \
	do{ \
		if((CONSOLE_DEBUG_LEVEL) <= CONSOLE_DEBUG_LEVEL_ERROR){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_RED); \
			console_print("[E]: [%s] "_fmt_" (%s,%d)", TAG, ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#else
#define ERROR(_fmt_, ...) \
	do{}while(0)
#define ERROR_TAG(TAG, _fmt_, ...) \
	do{}while(0)
#endif

#if MIIO_CONSOLE_DEBUG_LEVEL <= CONSOLE_DEBUG_LEVEL_FATAL
#define FATAL(_fmt_, ...) \
	do{\
		extern log_level_t g_log_level; \
		if(g_log_level <= CONSOLE_DEBUG_LEVEL_FATAL){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_RED); \
			console_print("[F] "_fmt_" (%s, %d)", ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#define FATAL_TAG(TAG, _fmt_, ...) \
	do{ \
		if((CONSOLE_DEBUG_LEVEL) <= CONSOLE_DEBUG_LEVEL_FATAL){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_RED); \
			console_print("[F]: [%s] "_fmt_" (%s, %d)", TAG, ##__VA_ARGS__, __FUNCTION__, __LINE__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)

#else
#define FATAL(_fmt_, ...) \
	do{}while(0)
#define FATAL_TAG(TAG, _fmt_, ...) \
	do{}while(0)
#endif

#if MIIO_CONSOLE_DEBUG_LEVEL <= CONSOLE_DEBUG_LEVEL_VERBOSE
#define DEBUG(_fmt_, ...) \
	do{\
		extern log_level_t g_log_level; \
		if(g_log_level <= CONSOLE_DEBUG_LEVEL_VERBOSE){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_GRE); \
			console_print("[D] "_fmt_, ##__VA_ARGS__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#define DEBUG_TAG(TAG, _fmt_, ...) \
	do{ \
		if((CONSOLE_DEBUG_LEVEL) <= CONSOLE_DEBUG_LEVEL_VERBOSE){ \
			console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_GRE); \
			console_print("[D]: [%s] "_fmt_, TAG, ##__VA_ARGS__); \
			console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF); \
		} \
	}while(0)
#else
#define DEBUG(_fmt_, ...) \
	do{}while(0)
#define DEBUG_TAG(TAG, _fmt_, ...) \
	do{}while(0)
#endif

// ---------------- Assertion -----------------

#define BREAKPOINT() \
	do { \
	} while (1)

#define ARCH_ASSERT(info, assertion) \
	do { \
		if(!(assertion)) { \
			console_print("[ASSERT] %s.\r\n"); \
		} \
	}while(0)

#ifdef __cplusplus
}
#endif

#endif /* __CONSOLE_DEBUG_H__ */

