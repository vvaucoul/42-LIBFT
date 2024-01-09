/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:48:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:50:38 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// Enum for log levels
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

// Function to initialize the logger
void logger_init(const char *filename);

// Function to set the log level
void logger_set_level(LogLevel level);

// Function to log a message
void logger_log(LogLevel level, const char *message);

// Function to log a debug message
void logger_debug(const char *message);

// Function to log an info message
void logger_info(const char *message);

// Function to log a warning message
void logger_warn(const char *message);

// Function to log an error message
void logger_error(const char *message);

// Function to log a fatal error message
void logger_fatal(const char *message);

// Function to close the logger
void logger_close(void);

#endif /* !LOGGER_H */