/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 18:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TEST_H
# define LIBFT_TEST_H

# include <stdio.h>

// ============================================================================
// COLOR CODES
// ============================================================================

# define COLOR_GREEN "\033[0;32m"
# define COLOR_RED "\033[0;31m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_RESET "\033[0m"

// ============================================================================
// TEST MACROS
// ============================================================================

/**
 * TEST_START - Prints the name of the test being run
 * 
 * Usage: TEST_START("test name");
 */
# define TEST_START(name) \
	do { \
		printf(COLOR_BLUE "Testing: %s" COLOR_RESET "\n", name); \
	} while(0)

/**
 * TEST_ASSERT - Asserts a condition and updates test counters
 * 
 * This macro checks a condition and prints a colored pass/fail message.
 * It automatically updates the global test counters.
 * 
 * Usage: TEST_ASSERT(condition, "description");
 * 
 * Requirements:
 * - Must have global variables in scope:
 *   - g_tests_run (or g_buf_tests_run, g_list_tests_run, etc.)
 *   - g_tests_passed (or g_buf_tests_passed, g_list_tests_passed, etc.)
 *   - g_tests_failed (or g_buf_tests_failed, g_list_tests_failed, etc.)
 */
# define TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_failed++; \
		} \
	} while(0)

/**
 * TEST_SUMMARY - Prints a summary of test results
 * 
 * This macro prints a formatted summary showing total tests run,
 * passed, and failed with appropriate colors.
 * 
 * Usage: TEST_SUMMARY();
 * 
 * Requirements:
 * - Must have global variables in scope with test counts
 */
# define TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_tests_run, g_tests_passed); \
		if (g_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

// ============================================================================
// LIBRARY-SPECIFIC TEST MACROS
// ============================================================================

/**
 * String library test counter names
 * Use these when testing string functions
 */
# ifndef STRING_TEST_COUNTERS
#  define STRING_TEST_COUNTERS \
	int g_tests_run = 0; \
	int g_tests_passed = 0; \
	int g_tests_failed = 0;
# endif

/**
 * Buffer library test counter names
 * Use these when testing buffer functions
 */
# ifndef BUFFER_TEST_COUNTERS
#  define BUFFER_TEST_COUNTERS \
	int g_buf_tests_run = 0; \
	int g_buf_tests_passed = 0; \
	int g_buf_tests_failed = 0;
# endif

/**
 * List library test counter names
 * Use these when testing list functions
 */
# ifndef LIST_TEST_COUNTERS
#  define LIST_TEST_COUNTERS \
	int g_list_tests_run = 0; \
	int g_list_tests_passed = 0; \
	int g_list_tests_failed = 0;
# endif

// ============================================================================
// LIBRARY-SPECIFIC ASSERT MACROS
// ============================================================================

/**
 * String-specific TEST_ASSERT
 * Uses g_tests_* counters
 */
# define STR_TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_failed++; \
		} \
	} while(0)

/**
 * Buffer-specific TEST_ASSERT
 * Uses g_buf_tests_* counters
 */
# define BUF_TEST_ASSERT(condition, message) \
	do { \
		g_buf_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_buf_tests_run, message); \
			g_buf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_buf_tests_run, message); \
			g_buf_tests_failed++; \
		} \
	} while(0)

/**
 * List-specific TEST_ASSERT
 * Uses g_list_tests_* counters
 */
# define LIST_TEST_ASSERT(condition, message) \
	do { \
		g_list_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_list_tests_run, message); \
			g_list_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_list_tests_run, message); \
			g_list_tests_failed++; \
		} \
	} while(0)

/**
 * Char-specific TEST_ASSERT
 * Uses g_char_tests_* counters
 */
# define CHAR_TEST_ASSERT(condition, message) \
	do { \
		g_char_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_char_tests_run, message); \
			g_char_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_char_tests_run, message); \
			g_char_tests_failed++; \
		} \
	} while(0)

/**
 * Math-specific TEST_ASSERT
 * Uses g_math_tests_* counters
 */
# define MATH_TEST_ASSERT(condition, message) \
	do { \
		g_math_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_math_tests_run, message); \
			g_math_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_math_tests_run, message); \
			g_math_tests_failed++; \
		} \
	} while(0)

/**
 * Printf-specific TEST_ASSERT
 * Uses g_printf_tests_* counters
 */
# define PRINTF_TEST_ASSERT(condition, message) \
	do { \
		g_printf_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_printf_tests_run, message); \
			g_printf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_printf_tests_run, message); \
			g_printf_tests_failed++; \
		} \
	} while(0)

// ============================================================================
// LIBRARY-SPECIFIC SUMMARY MACROS
// ============================================================================

/**
 * String-specific TEST_SUMMARY
 * Uses g_tests_* counters
 */
# define STR_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_tests_run, g_tests_passed); \
		if (g_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Buffer-specific TEST_SUMMARY
 * Uses g_buf_tests_* counters
 */
# define BUF_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_buf_tests_run, g_buf_tests_passed); \
		if (g_buf_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_buf_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * List-specific TEST_SUMMARY
 * Uses g_list_tests_* counters
 */
# define LIST_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("List Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_list_tests_run, g_list_tests_passed); \
		if (g_list_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_list_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Char-specific TEST_SUMMARY
 * Uses g_char_tests_* counters
 */
# define CHAR_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Char Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_char_tests_run, g_char_tests_passed); \
		if (g_char_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_char_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Math-specific TEST_SUMMARY
 * Uses g_math_tests_* counters
 */
# define MATH_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Math Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_math_tests_run, g_math_tests_passed); \
		if (g_math_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_math_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Printf-specific TEST_SUMMARY
 * Uses g_printf_tests_* counters
 */
# define PRINTF_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Printf Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_printf_tests_run, g_printf_tests_passed); \
		if (g_printf_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_printf_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

// ============================================================================
// PRINTF-SPECIFIC TEST MACRO
// ============================================================================

/**
 * TEST_PRINTF - Compare ft_printf output with standard printf
 * 
 * This macro captures the output of both printf and ft_printf using
 * fmemopen and file descriptor redirection, then compares both the
 * output strings and return values.
 * 
 * Usage: TEST_PRINTF("%d %s", 42, "hello");
 * 
 * Requirements:
 * - Must have global variables g_printf_tests_* in scope
 * - Must include <unistd.h> for dup/dup2
 * - Must include <string.h> for strcmp
 */
# define TEST_PRINTF(format, ...) \
	do { \
		char expected[1024] = {0}; \
		char actual[1024] = {0}; \
		int exp_ret, act_ret; \
		FILE *exp_fp = fmemopen(expected, sizeof(expected), "w"); \
		FILE *act_fp = fmemopen(actual, sizeof(actual), "w"); \
		int saved_stdout = dup(STDOUT_FILENO); \
		dup2(fileno(exp_fp), STDOUT_FILENO); \
		exp_ret = printf(format, ##__VA_ARGS__); \
		fflush(stdout); \
		fclose(exp_fp); \
		dup2(fileno(act_fp), STDOUT_FILENO); \
		act_ret = ft_printf(format, ##__VA_ARGS__); \
		fflush(stdout); \
		fclose(act_fp); \
		dup2(saved_stdout, STDOUT_FILENO); \
		close(saved_stdout); \
		g_printf_tests_run++; \
		if (exp_ret == act_ret && strcmp(expected, actual) == 0) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "\"" format "\"\n", g_printf_tests_run, ##__VA_ARGS__); \
			g_printf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "\"" format "\"\n", g_printf_tests_run, ##__VA_ARGS__); \
			printf("    Expected: \"%s\" (ret=%d)\n", expected, exp_ret); \
			printf("    Got:      \"%s\" (ret=%d)\n", actual, act_ret); \
			g_printf_tests_failed++; \
		} \
	} while(0)

// ============================================================================
// TEST HEADER BANNERS
// ============================================================================

/**
 * Prints a formatted test suite header
 */
# define TEST_HEADER(name) \
	do { \
		printf("\n"); \
		printf(COLOR_BLUE "════════════════════════════════════════════════════\n"); \
		printf("     %s\n", name); \
		printf("════════════════════════════════════════════════════\n" COLOR_RESET); \
		printf("\n"); \
	} while(0)

/**
 * Prints a formatted test suite section header
 */
# define TEST_SECTION(name) \
	do { \
		printf("\n"); \
		printf(COLOR_CYAN " ------- %s -------\n" COLOR_RESET); \
		printf("\n"); \
	} while(0)

#endif
