# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 18:52:08 by vvaucoul          #+#    #+#              #
#    Updated: 2024/01/09 00:54:54 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

include depends/Colors.mk
include depends/Config.mk
include depends/Rules.mk
include depends/Tests.mk
include depends/Extras.mk

.DEFAULT_GOAL := all