/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:48:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

void logger_init(const char *filename);
void logger_set_level(LogLevel level);
LogLevel logger_get_level(void);
int logger_is_open(void);
void logger_log(LogLevel level, const char *message);
void logger_logf(LogLevel level, const char *fmt, ...);
void logger_debug(const char *message);
void logger_info(const char *message);
void logger_warn(const char *message);
void logger_error(const char *message);
void logger_fatal(const char *message);
void logger_close(void);

#endif /* !LOGGER_H */
