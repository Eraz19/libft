# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by Copilot           #+#    #+#              #
#    Updated: 2026/01/02 23:40:50 by adouieb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   VARIABLES                                  #
# ============================================================================ #

# Output library name
NAME:=libft.a

# Project name for display
PROJECT:=libft

# Variable to control header printing (0 = print, 1 = suppress)
PREC_RULE:=0

# Compiler and flags
CC:=cc
CC_FLAGS:=-Werror -Wextra -Wall -fPIC

# Archiver and flags
AR:=ar
AR_FLAGS:=-rc

# Directories
HDR_DIR:=includes
SRC_DIR:=srcs
OBJ_DIR:=objs

# Subdirectories for source files
BUFFER_DIR:=${SRC_DIR}/buffer
CHAR_DIR  :=${SRC_DIR}/char
LIST_DIR  :=${SRC_DIR}/list
MATH_DIR  :=${SRC_DIR}/math
STRING_DIR:=${SRC_DIR}/string

# Source files by category
BUFFER_SRCS:=${BUFFER_DIR}/constructor/cbuf.c	\
		${BUFFER_DIR}/constructor/dbuf.c		\
		${BUFFER_DIR}/constructor/free.c		\
		${BUFFER_DIR}/method/insert.c			\
		${BUFFER_DIR}/method/shift.c
CHAR_SRCS:=${CHAR_DIR}/isalnum.c	\
		${CHAR_DIR}/isalpha.c		\
		${CHAR_DIR}/isascii.c		\
		${CHAR_DIR}/isdigit.c		\
		${CHAR_DIR}/isprint.c		\
		${CHAR_DIR}/tolower.c		\
		${CHAR_DIR}/toupper.c
LIST_SRCS:=${LIST_DIR}/constructor/free.c	\
		${LIST_DIR}/constructor/lst.c		\
		${LIST_DIR}/constructor/node.c		\
		${LIST_DIR}/method/get.c 			\
		${LIST_DIR}/method/insert.c			\
		${LIST_DIR}/method/iter.c
MATH_SRCS:=${MATH_DIR}/abs.c
STRING_SRCS:=${STRING_DIR}/constructor/cstr.c		\
		${STRING_DIR}/constructor/dstr.c			\
		${STRING_DIR}/constructor/free.c			\
		${STRING_DIR}/method/buffer_conversion.c	\
		${STRING_DIR}/method/char_conversion.c		\
		${STRING_DIR}/method/compare.c				\
		${STRING_DIR}/method/find.c					\
		${STRING_DIR}/method/insert.c				\
		${STRING_DIR}/method/int_conversion.c		\
		${STRING_DIR}/method/iter.c					\
		${STRING_DIR}/method/long_conversion.c		\
		${STRING_DIR}/method/print.c				\
		${STRING_DIR}/method/repeat.c				\
		${STRING_DIR}/method/shift.c				\
		${STRING_DIR}/method/split.c				\
		${STRING_DIR}/method/trim.c

# All source files
SRCS:=${BUFFER_SRCS}	\
	${CHAR_SRCS}		\
	${LIST_SRCS}		\
	${MATH_SRCS}		\
	${STRING_SRCS}

# Object files (flat naming with category prefixes to avoid collisions)
BUFFER_OBJS=$(addprefix $(OBJ_DIR)/buffer_,$(notdir $(BUFFER_SRCS:.c=.o)))
CHAR_OBJS=$(addprefix $(OBJ_DIR)/char_,$(notdir $(CHAR_SRCS:.c=.o)))
LIST_OBJS=$(addprefix $(OBJ_DIR)/list_,$(notdir $(LIST_SRCS:.c=.o)))
MATH_OBJS=$(addprefix $(OBJ_DIR)/math_,$(notdir $(MATH_SRCS:.c=.o)))
STRING_OBJS=$(addprefix $(OBJ_DIR)/string_,$(notdir $(STRING_SRCS:.c=.o)))

OBJS=${BUFFER_OBJS} ${CHAR_OBJS} ${LIST_OBJS} ${MATH_OBJS} ${STRING_OBJS}

# ============================================================================ #
#                                   HELPER                                     #
# ============================================================================ #

# Helper functions to map object files back to their source files
get-buffer-src = $(filter %/$(patsubst buffer_%.o,%.c,$(notdir $(1))),$(BUFFER_SRCS))
get-char-src = $(filter %/$(patsubst char_%.o,%.c,$(notdir $(1))),$(CHAR_SRCS))
get-list-src = $(filter %/$(patsubst list_%.o,%.c,$(notdir $(1))),$(LIST_SRCS))
get-math-src = $(filter %/$(patsubst math_%.o,%.c,$(notdir $(1))),$(MATH_SRCS))
get-string-src = $(filter %/$(patsubst string_%.o,%.c,$(notdir $(1))),$(STRING_SRCS))

# ============================================================================ #
#                                    RULES                                     #
# ============================================================================ #

.SECONDEXPANSION:

# Default rule: builds the library
all:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Build the library
	@$(MAKE) $(NAME) --no-print-directory

# Explicit compilation rules using secondexpansion to map sources to objects
$(BUFFER_OBJS): $(OBJ_DIR)/buffer_%.o: $$(call get-buffer-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(CHAR_OBJS): $(OBJ_DIR)/char_%.o: $$(call get-char-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(LIST_OBJS): $(OBJ_DIR)/list_%.o: $$(call get-list-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(MATH_OBJS): $(OBJ_DIR)/math_%.o: $$(call get-math-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@
$(STRING_OBJS): $(OBJ_DIR)/string_%.o: $$(call get-string-src,$$@)
	@mkdir -p $(OBJ_DIR)
	@echo " Generating $@"
	@${CC} ${CC_FLAGS} -I${HDR_DIR} -c $< -o $@

# Archives object files into the library
$(NAME): $(OBJS)
	@echo " \033[0;32mSUCCESSFULLY\033[0m generating ${NAME}"
	@$(AR) $(AR_FLAGS) $@ $(OBJS)

# Cleans object files
clean:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Delete object directory if it exists
	@if [ -d ${OBJ_DIR} ] && [ "$(wildcard ${OBJ_DIR}/*)" ]; then \
		rm -rf ${OBJ_DIR}/*; \
		echo " \033[0;31mDeleting\033[0m $(PROJECT) all obj files"; \
	else \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) all obj files"; \
	fi

# Cleans object files and the library
fclean:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Clean objects (suppress header)
	@$(MAKE) clean PREC_RULE=1 --no-print-directory
	@# Delete the library file
	@if [ -f ${NAME} ]; then \
		rm -f $(NAME); \
		echo " \033[0;31mDeleting\033[0m $(PROJECT) library"; \
	else \
		echo " \033[0;33mAlready\033[0m deleted $(PROJECT) library"; \
	fi

# Rebuilds everything from scratch
re:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Full clean (suppress header)
	@$(MAKE) fclean PREC_RULE=1 --no-print-directory
	@# Add a newline for readability if top-level
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo ; \
	fi
	@# Build all (suppress header)
	@$(MAKE) all PREC_RULE=1 --no-print-directory

.PHONY: all bonus clean fclean re
