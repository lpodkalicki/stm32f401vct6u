/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#ifndef	_PROJECT_LOG_H_
#define	_PROJECT_LOG_H_

/** @brief Custom log format (NOTE: format not contains a log-level prefix and is not terminated by new line) */
#define	LOGLEVEL_NONE		(-1)
/** @brief system is unusable */
#define LOGLEVEL_EMERG		(0)
/** @brief action must be taken immediately */
#define LOGLEVEL_ALERT		(1)
/** @brief critical conditions */
#define LOGLEVEL_CRIT		(2)
/** @brief error conditions */
#define LOGLEVEL_ERR		(3)
/** @brief warning conditions */
#define LOGLEVEL_WARNING	(4)
/** @brief normal but signification condition */
#define LOGLEVEL_NOTICE		(5)
/** @brief informational */
#define LOGLEVEL_INFO		(6)
/** @brief debug-level messages */
#define LOGLEVEL_DEBUG0		(7)
/** @brief debug-level2 messages */
#define LOGLEVEL_DEBUG1		(8)
/** @brief debug-level2 messages */
#define LOGLEVEL_DEBUG2		(9)
/** @brief default logging-level */
#define	LOGLEVEL_DEFAULT	LOGLEVEL_ERR

/** @brief Max length for single log line */
#define	LOG_MAXLINE		(512)

/**
 * @brief Initialize logger context.
 * @param[in] level logging level (err, debug, etc..) as cardinal 
 */
void log_init(int level);

/**
 * @brief Finalize logger context. 
 */
void log_fini(void);

/**
 * @brief Set logging level (err, debug, etc..).
 * @param[in] type logging level (err, debug, etc..) as cardinal
 */
void log_setlevel(int level);

/**
 * @brief Get logging level (err, debug, etc..).
 * @return
 *	logging level (err, debug, etc..) as integer
 */
int log_level(void);

/**
 * @brief Main (internal) logger function.
 * @param[in] level logging level as cardinal
 * @param[in] format single log format (similar to "printf" function format) as string
 * @param[in] ... format arguments (similar to "printf" function arguments) as list of mixed
 */
void _log(int level, const char *format, ...);

#ifdef DEBUG
# define	log(...)		_log(LOGLEVEL_NONE, "" __VA_ARGS__)
# define	log_emerg(...)		_log(LOGLEVEL_EMERG, "[ EMERG ] " __VA_ARGS__)
# define	log_alert(...)		_log(LOGLEVEL_ALERT, "[ ALERT ] " __VA_ARGS__)
# define	log_critical(...)	_log(LOGLEVEL_CRIT, "[  CRIT ] " __VA_ARGS__)
# define	log_error(...)		_log(LOGLEVEL_ERR, "[ ERROR ] " __VA_ARGS__)
# define	log_warning(...)	_log(LOGLEVEL_WARNING, "[  WARN ] " __VA_ARGS__)
# define	log_notice(...)		_log(LOGLEVEL_NOTICE, "[ NOTICE] " __VA_ARGS__)
# define	log_info(...)		_log(LOGLEVEL_INFO, "[  INFO ] " __VA_ARGS__)
# define	log_debug(...)		_log(LOGLEVEL_DEBUG0, "[DEBUG-0] " __VA_ARGS__)
# define	log_debug1(...)		_log(LOGLEVEL_DEBUG1, "[DEBUG-1] " __VA_ARGS__)
# define	log_debug2(...)		_log(LOGLEVEL_DEBUG2, "[DEBUG-2] " __VA_ARGS__)
#else /* !DEBUG */
# define	log(...)
# define	log_emerg(...)
# define	log_alert(...)
# define	log_critical(...)
# define	log_error(...)
# define	log_warning(...)
# define	log_notice(...)
# define	log_info(...)
# define	log_debug(...)
# define	log_debug1(...)
# define	log_debug2(...)
#endif

#endif	/* !_PROJECT_LOG_H_ */
