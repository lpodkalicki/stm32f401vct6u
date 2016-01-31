/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"

static volatile int _loglevel = LOGLEVEL_DEFAULT;

void
log_init(int level)
{

	setbuf(stdout, NULL);
	_loglevel = level;
}

void
log_fini(void)
{

	// TODO: block logging ability
}

void
log_setlevel(int level)
{

	_loglevel = level;
}

int
log_level(void)
{

	return _loglevel;
}

void
_log(int level, const char *format, ...)
{
	va_list args;
	char line[LOG_MAXLINE];
	int retval;

	/* Drop log if level is grater then value from logger context */
	if (_loglevel < level)
		return;

	va_start(args, format);
#ifdef	HAVE_VSNPRINTF
	retval = vsnprintf(line, sizeof(line), format, args);	/* this is safe */
#else
	retval = vsprintf(line, format, args); 			/* this is not safe */
#endif
	va_end(args);

	if (retval < 0)
		return;

	if (level >= 0) {
		retval = strlen(line);
		line[retval] = '\n';
		line[retval + 1] = '\0';;
	}

	fflush(stdout);
	fputs(line, stdout);
	fflush(stdout);
}
