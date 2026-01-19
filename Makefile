# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by Copilot           #+#    #+#              #
#    Updated: 2026/01/19 19:44:56 by adouieb          ###   ########.fr        #
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
# Variable to catch norminette errors
NORM_ERRORS:=""

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
TEST_DIR:=test

CHAR_DIR  :=${SRC_DIR}/char
LIST_DIR  :=${SRC_DIR}/list
MATH_DIR  :=${SRC_DIR}/math
BUFFER_DIR:=${SRC_DIR}/buffer
STRING_DIR:=${SRC_DIR}/string
PRINTF_DIR:=${SRC_DIR}/printf

BUFFER_SRCS:=${BUFFER_DIR}/constructor/cbuf.c	\
		${BUFFER_DIR}/method/shift.c			\
		${BUFFER_DIR}/method/insert.c			\
		${BUFFER_DIR}/constructor/dbuf.c		\
		${BUFFER_DIR}/constructor/free.c
CHAR_SRCS:=${CHAR_DIR}/isalnum.c	\
		${CHAR_DIR}/isalpha.c		\
		${CHAR_DIR}/isascii.c		\
		${CHAR_DIR}/isdigit.c		\
		${CHAR_DIR}/isprint.c		\
		${CHAR_DIR}/isspace.c		\
		${CHAR_DIR}/tolower.c		\
		${CHAR_DIR}/toupper.c
LIST_SRCS:=${LIST_DIR}/constructor/free.c	\
		${LIST_DIR}/method/get.c 			\
		${LIST_DIR}/method/iter.c			\
		${LIST_DIR}/method/insert.c			\
		${LIST_DIR}/constructor/lst.c		\
		${LIST_DIR}/constructor/node.c
MATH_SRCS:=${MATH_DIR}/abs.c
PRINTF_SRCS:=${PRINTF_DIR}/printf.c			\
		${PRINTF_DIR}/parse.c					\
		${PRINTF_DIR}/rule.c					\
		${PRINTF_DIR}/flags.c					\
		${PRINTF_DIR}/flags_precision.c			\
		${PRINTF_DIR}/convert_args.c
STRING_SRCS:=${STRING_DIR}/constructor/cstr.c		\
		${STRING_DIR}/constructor/dstr.c			\
		${STRING_DIR}/constructor/free.c			\
		${STRING_DIR}/method/sub.c					\
		${STRING_DIR}/method/find.c					\
		${STRING_DIR}/method/iter.c					\
		${STRING_DIR}/method/trim.c					\
		${STRING_DIR}/method/print.c				\
		${STRING_DIR}/method/split.c				\
		${STRING_DIR}/method/shift.c				\
		${STRING_DIR}/method/insert.c				\
		${STRING_DIR}/method/repeat.c				\
		${STRING_DIR}/method/compare.c				\
		${STRING_DIR}/method/int_conversion.c		\
		${STRING_DIR}/method/long_conversion.c		\
		${STRING_DIR}/method/char_conversion.c		\
		${STRING_DIR}/method/buffer_conversion.c

SRCS:=${BUFFER_SRCS}	\
	${CHAR_SRCS}		\
	${LIST_SRCS}		\
	${MATH_SRCS}		\
	${PRINTF_SRCS}		\
	${STRING_SRCS}

# Object files (flat naming with category prefixes to avoid collisions)
CHAR_OBJS=$(addprefix $(OBJ_DIR)/char_,$(notdir $(CHAR_SRCS:.c=.o)))
LIST_OBJS=$(addprefix $(OBJ_DIR)/list_,$(notdir $(LIST_SRCS:.c=.o)))
MATH_OBJS=$(addprefix $(OBJ_DIR)/math_,$(notdir $(MATH_SRCS:.c=.o)))
BUFFER_OBJS=$(addprefix $(OBJ_DIR)/buffer_,$(notdir $(BUFFER_SRCS:.c=.o)))
PRINTF_OBJS=$(addprefix $(OBJ_DIR)/printf_,$(notdir $(PRINTF_SRCS:.c=.o)))
STRING_OBJS=$(addprefix $(OBJ_DIR)/string_,$(notdir $(STRING_SRCS:.c=.o)))

OBJS=${BUFFER_OBJS} ${CHAR_OBJS} ${LIST_OBJS} ${MATH_OBJS} ${PRINTF_OBJS} ${STRING_OBJS}

# ============================================================================ #
#                                   HELPER                                     #
# ============================================================================ #

# Helper functions to map object files back to their source files
get-char-src = $(filter %/$(patsubst char_%.o,%.c,$(notdir $(1))),$(CHAR_SRCS))
get-list-src = $(filter %/$(patsubst list_%.o,%.c,$(notdir $(1))),$(LIST_SRCS))
get-math-src = $(filter %/$(patsubst math_%.o,%.c,$(notdir $(1))),$(MATH_SRCS))
get-buffer-src = $(filter %/$(patsubst buffer_%.o,%.c,$(notdir $(1))),$(BUFFER_SRCS))
get-printf-src = $(filter %/$(patsubst printf_%.o,%.c,$(notdir $(1))),$(PRINTF_SRCS))
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
		NORM_ERRORS=$$(norminette $(SRC_DIR) $(HDR_DIR) 2>&1); \
		if [ $$? -ne 0 ]; then \
			echo " \033[0;35mChecking\033[0m norminette compliance \033[0;31m✗\033[0m"; \
			echo "$$NORM_ERRORS" | sed 's/^/ /'; \
			echo ; \
			echo " \033[0;31mNorminette errors found. Aborting build.\033[0m"; \
			exit 1; \
		else \
			echo " \033[0;35mChecking\033[0m norminette compliance \033[0;32m✓\033[0m"; \
		fi; \
	fi
	@# Build the library
	@if [ -f $(NAME) ] && [ -z "$$(find $(SRC_DIR) -newer $(NAME) 2>/dev/null)" ]; then \
		echo " \033[0;33mNothing\033[0m to be done for '$(NAME)' (already up to date)"; \
	else \
		$(MAKE) $(NAME) --no-print-directory -s; \
	fi

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
$(PRINTF_OBJS): $(OBJ_DIR)/printf_%.o: $$(call get-printf-src,$$@)
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

# ============================================================================ #
#                                    TESTS                                     #
# ============================================================================ #

TEST_NAME:=libft_tests

# Subdirectories for source files

CHAR_TEST_DIR  :=${TEST_DIR}/char
LIST_TEST_DIR  :=${TEST_DIR}/list
MATH_TEST_DIR  :=${TEST_DIR}/math
BUFFER_TEST_DIR:=${TEST_DIR}/buffer
STRING_TEST_DIR:=${TEST_DIR}/string
PRINTF_TEST_DIR:=${TEST_DIR}/printf

# Test source files
STRING_TEST_SRCS:=${STRING_TEST_DIR}/test_string_comprehensive.c \
		${STRING_TEST_DIR}/test_string_edge_cases.c

BUFFER_TEST_SRCS:=${BUFFER_TEST_DIR}/test_buffer_comprehensive.c \
		${BUFFER_TEST_DIR}/test_buffer_edge_cases.c

LIST_TEST_SRCS:=${LIST_TEST_DIR}/test_list_comprehensive.c \
		${LIST_TEST_DIR}/test_list_edge_cases.c

CHAR_TEST_SRCS:=${CHAR_TEST_DIR}/test_char_comprehensive.c

MATH_TEST_SRCS:=${MATH_TEST_DIR}/test_math_comprehensive.c

PRINTF_TEST_SRCS:=${PRINTF_TEST_DIR}/test_printf_comprehensive.c \
		${PRINTF_TEST_DIR}/test_printf_edge_cases.c

# Unified test runner
TEST_MAIN:=${TEST_DIR}/test_main.c

ALL_TEST_SRCS:=${TEST_MAIN} \
	${LIST_TEST_SRCS} 		\
	${CHAR_TEST_SRCS} 		\
	${MATH_TEST_SRCS}		\
	${PRINTF_TEST_SRCS}		\
	${STRING_TEST_SRCS} 	\
	${BUFFER_TEST_SRCS}

# Build unified test executable
test:
	@# Print header if this is the top-level call
	@if [ "$(PREC_RULE)" = "0" ]; then \
		echo " \033[0;34m----- libft -----\033[0m"; \
	fi
	@# Check norminette compliance (optional)
	@NORM_ERRORS=$$(norminette $(SRC_DIR) $(HDR_DIR) 2>&1); \
	if [ $$? -ne 0 ]; then \
		echo " \033[0;35mChecking\033[0m norminette compliance \033[0;31m✗\033[0m"; \
		echo "$$NORM_ERRORS" | sed 's/^/ /'; \
		echo ; \
		echo " \033[0;31mNorminette errors found. Aborting build.\033[0m"; \
		exit 1; \
	else \
		echo " \033[0;35mChecking\033[0m norminette compliance \033[0;32m✓\033[0m"; \
	fi
	@echo ;
	@echo " \033[0;34m----- Building Libft -----\033[0m"
	@# Clean objects (suppress header)
	@$(MAKE) all PREC_RULE=1 --no-print-directory
	@echo ;
	@echo " \033[0;34m----- Building Unified Test Suite -----\033[0m"
	@$(CC) $(CC_FLAGS) -Wno-format-zero-length -Wno-format-overflow -I./test -I${HDR_DIR} ${ALL_TEST_SRCS} -L. -lft -o ${TEST_NAME}
	@echo " \033[0;32mSUCCESSFULLY\033[0m generated ${TEST_NAME}"
	@echo ;
	@echo " \033[0;34m----- Running All Tests -----\033[0m"
	@./${TEST_NAME}
	@rm -f ${TEST_NAME}

test_clean:
	@rm -f ${TEST_NAME}
	@echo " \033[0;32mCleaned\033[0m test executables"

.PHONY: all bonus clean fclean re test test_clean

