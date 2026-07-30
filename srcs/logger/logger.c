/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <logger.h>
#include <stdarg.h>

static FILE *log_file = NULL;
static LogLevel current_level = LOG_LEVEL_INFO;

void logger_init(const char *filename)
{
    if (log_file)
        fclose(log_file);
    log_file = fopen(filename, "a");
    if (!log_file)
    {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
}

void logger_set_level(LogLevel level)
{
    current_level = level;
}

LogLevel logger_get_level(void)
{
    return (current_level);
}

int logger_is_open(void)
{
    return (log_file != NULL);
}

static const char *logger_level_name(LogLevel level)
{
    if (level == LOG_LEVEL_DEBUG)
        return ("DEBUG");
    if (level == LOG_LEVEL_INFO)
        return ("INFO");
    if (level == LOG_LEVEL_WARN)
        return ("WARN");
    if (level == LOG_LEVEL_ERROR)
        return ("ERROR");
    if (level == LOG_LEVEL_FATAL)
        return ("FATAL");
    return ("UNKNOWN");
}

static int logger_should_log(LogLevel level)
{
    return (log_file != NULL && level >= current_level);
}

static void logger_write_header(LogLevel level)
{
    time_t now;
    char *date;

    now = time(NULL);
    date = ctime(&now);
    date[ft_strlen(date) - 1] = '\0';
    fprintf(log_file, "[%s] [%s] ", date, logger_level_name(level));
}

void logger_log(LogLevel level, const char *message)
{
    if (!logger_should_log(level))
        return ;
    if (!message)
        message = "";
    logger_write_header(level);
    fprintf(log_file, "%s\n", message);
    fflush(log_file);
}

void logger_logf(LogLevel level, const char *fmt, ...)
{
    va_list args;

    if (!logger_should_log(level) || !fmt)
        return ;
    logger_write_header(level);
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);
    fprintf(log_file, "\n");
    fflush(log_file);
}

void logger_debug(const char *message)
{
    logger_log(LOG_LEVEL_DEBUG, message);
}

void logger_info(const char *message)
{
    logger_log(LOG_LEVEL_INFO, message);
}

void logger_warn(const char *message)
{
    logger_log(LOG_LEVEL_WARN, message);
}

void logger_error(const char *message)
{
    logger_log(LOG_LEVEL_ERROR, message);
}

void logger_fatal(const char *message)
{
    logger_log(LOG_LEVEL_FATAL, message);
}

void logger_close(void)
{
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;
    }
}
