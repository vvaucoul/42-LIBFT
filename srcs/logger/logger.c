/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:49:25 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:50:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <logger.h>

static FILE *log_file = NULL;
static LogLevel current_level = LOG_LEVEL_INFO;

void logger_init(const char *filename) {
    log_file = fopen(filename, "a");
    if (!log_file) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
}

void logger_set_level(LogLevel level) {
    current_level = level;
}

void logger_log(LogLevel level, const char *message) {
    if (level < current_level || !log_file) {
        return;
    }

    const char *level_str = "";
    switch (level) {
        case LOG_LEVEL_DEBUG: level_str = "DEBUG"; break;
        case LOG_LEVEL_INFO: level_str = "INFO"; break;
        case LOG_LEVEL_WARN: level_str = "WARN"; break;
        case LOG_LEVEL_ERROR: level_str = "ERROR"; break;
        case LOG_LEVEL_FATAL: level_str = "FATAL"; break;
    }

    time_t now = time(NULL);
    char *date = ctime(&now);
    date[ft_strlen(date) - 1] = '\0';  // Remove the newline character

    fprintf(log_file, "[%s] [%s] %s\n", date, level_str, message);
}

void logger_debug(const char *message) {
    logger_log(LOG_LEVEL_DEBUG, message);
}

void logger_info(const char *message) {
    logger_log(LOG_LEVEL_INFO, message);
}

void logger_warn(const char *message) {
    logger_log(LOG_LEVEL_WARN, message);
}

void logger_error(const char *message) {
    logger_log(LOG_LEVEL_ERROR, message);
}

void logger_fatal(const char *message) {
    logger_log(LOG_LEVEL_FATAL, message);
}

void logger_close(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}