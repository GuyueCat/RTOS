#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "portmacro.h"

#include "console_debug.h"

log_level_t g_log_level = CONSOLE_DEBUG_LEVEL_INFO;

static SemaphoreHandle_t console_debug_mutex = NULL;
StaticSemaphore_t console_debug_mutex_buffer;

void console_debug_init(void)
{
#if configSUPPORT_STATIC_ALLOCATION
	console_debug_mutex = xSemaphoreCreateMutexStatic(&console_debug_mutex_buffer);
#endif
}

void console_debug_begin(const char* ansi_color)
{
	/* get date/hour/minute/second */
	static char timestr[40] = { 0 };
	time_t t;
	struct tm *nowtime;
	time(&t);
	nowtime = localtime(&t);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", nowtime);

	/* get ms */
	struct timeval tv;
	gettimeofday(&tv, NULL);

	if(console_debug_mutex)
		xSemaphoreTake(console_debug_mutex, portMAX_DELAY);

	if(ansi_color){
		console_print("%s%s.%03d ", ansi_color, timestr, (uint32_t)(tv.tv_usec / 1000 % 1000));
	}
	else{
		console_print("%s.%03d ", timestr, (uint32_t)(tv.tv_usec / 1000 % 1000));
	}
}

void console_debug_end(const char* ansi_color)
{
	if(ansi_color) {
		console_print("%s\r\n", ansi_color);
	}
	else {
		console_print("\r\n");
	}

	if(console_debug_mutex)
		xSemaphoreGive(console_debug_mutex);
}

void console_debug_hex(const void *data, int len,const char *tips)
{
	int i;
	char dump_buf[128] = { 0 };
	int dump_size = 0;
	const unsigned char *data_p = data;

	console_debug_begin(CONSOLE_DEBUG_ANSI_COLOR_GRE);

	if (tips) {
		console_print("%s: size=%d\r\n",tips, len);
	}

	for (i = 0; i < len; i++) {
		if (0 == ((i + 1) % 16)) {
			dump_size += sprintf(dump_buf + dump_size, "0x%02x,\r\n", data_p[i]);
			dump_buf[dump_size] = '\0';
			console_print("%s", dump_buf);
			dump_size = 0;
			continue;
		}
		else{
			dump_size += sprintf(dump_buf + dump_size, "0x%02x,", data_p[i]);
		}
	}

	if(dump_size) {
		console_print("%s",dump_buf);
	}

	console_debug_end(CONSOLE_DEBUG_ANSI_COLOR_OFF);

	return;
}
