/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf_edge_cases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:30:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 20:30:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"

#include <limits.h>
#include <string.h>
#include <unistd.h>

// Override TEST_ASSERT and TEST_SUMMARY to use printf-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT PRINTF_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY PRINTF_TEST_SUMMARY

// Test counters (shared from test_printf_comprehensive.c)
extern int g_printf_tests_run;
extern int g_printf_tests_passed;
extern int g_printf_tests_failed;

// ============================================================================
// CHARACTER EDGE CASES - %c
// ============================================================================

void test_c_edge_cases(void)
{
	TEST_START("%c - character edge cases");
	
	// NULL character
	TEST_PRINTF("%c with null char", "%c", '\0');
	TEST_PRINTF("%c with null char and spaces", " %c ", '\0');
	TEST_PRINTF("%c '0' null '1'", " %c %c %c ", '0', '\0', '1');
	TEST_PRINTF("%c null '1' '2'", " %c %c %c ", '\0', '1', '2');
	TEST_PRINTF("%c '2' '1' null", " %c %c %c ", '2', '1', '\0');
	
	// ASCII boundaries
	TEST_PRINTF("%c with ASCII 0", "%c", '\0');
	TEST_PRINTF("%c with ASCII 127", "%c", 127);
	TEST_PRINTF("%c with ASCII 255", "%c", (char)255);
	
	// Extended ASCII and overflow
	TEST_PRINTF("%c with '0'-256 (underflow)", "%c", '0' - 256);
	TEST_PRINTF("%c with '0'+256 (overflow)", "%c", '0' + 256);
	
	// Special characters
	TEST_PRINTF("%c with three spaces", " %c %c %c ", ' ', ' ', ' ');
	TEST_PRINTF("%c with '1' '2' '3'", " %c %c %c ", '1', '2', '3');
	TEST_PRINTF("%c with escape chars", "%c%c%c%c%c", '\t', '\n', '\r', '\v', '\f');
}

// ============================================================================
// STRING EDGE CASES - %s
// ============================================================================

void test_s_edge_cases(void)
{
	TEST_START("%s - string edge cases");
	
	const char *long_str = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";
	
	// Empty strings
	TEST_PRINTF("%s with empty string", "%s", "");
	TEST_PRINTF("%s empty with leading space", " %s", "");
	TEST_PRINTF("%s empty with trailing space", "%s ", "");
	TEST_PRINTF("%s empty with both spaces", " %s ", "");
	
	// Single character strings
	TEST_PRINTF("%s with single dash", " %s ", "-");
	TEST_PRINTF("%s empty then dash", " %s %s ", "", "-");
	TEST_PRINTF("%s dash then empty", " %s %s ", " - ", "");
	
	// Multiple strings with empty
	TEST_PRINTF("%s mixed with long string", " %s %s %s %s %s", " - ", "", "4", "", long_str);
	TEST_PRINTF("%s mixed with short strings", " %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	
	// NULL string handling
	TEST_PRINTF("%s NULL surrounded by text", " NULL %s NULL ", (char *)NULL);
	TEST_PRINTF("%s with just NULL", "%s", (char *)NULL);
	TEST_PRINTF("%s with two NULLs", "%s %s", (char *)NULL, (char *)NULL);
	TEST_PRINTF("%s NULL in middle", "%s %s %s", "start", (char *)NULL, "end");
	
	// Strings with special characters
	TEST_PRINTF("%s with all escape sequences", "%s", "\t\n\r\v\f");
	TEST_PRINTF("%s with newlines", "%s", "Line1\nLine2\nLine3");
	TEST_PRINTF("%s with tabs", "%s", "Tab\tseparated\tvalues");
}

// ============================================================================
// POINTER EDGE CASES - %p
// ============================================================================

void test_p_edge_cases(void)
{
	TEST_START("%p - pointer edge cases");
	
	// NULL pointer
	TEST_PRINTF("%p with NULL", "%p", NULL);
	TEST_PRINTF("%p NULL with spaces", " %p ", NULL);
	TEST_PRINTF("%p two NULLs", " %p %p ", NULL, NULL);
	
	// Small values
	TEST_PRINTF("%p with 0", " %p ", (void *)0);
	TEST_PRINTF("%p with 1", " %p ", (void *)1);
	TEST_PRINTF("%p with 15", " %p ", (void *)15);
	TEST_PRINTF("%p with 16", " %p ", (void *)16);
	TEST_PRINTF("%p with 17", " %p ", (void *)17);
	
	// Negative values (cast as pointers)
	TEST_PRINTF("%p with -1", " %p ", (void *)-1);
	TEST_PRINTF("%p with -14523", " %p ", (void *)-14523);
	
	// Boundary values
	TEST_PRINTF("%p with LONG_MIN and LONG_MAX", " %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	TEST_PRINTF("%p with INT_MIN and INT_MAX", " %p %p ", (void *)INT_MIN, (void *)INT_MAX);
	TEST_PRINTF("%p with ULONG_MAX and -ULONG_MAX", " %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	TEST_PRINTF("%p with two zeros", " %p %p ", (void *)0, (void *)0);
	
	// Large addresses
	TEST_PRINTF("%p with 0x7fffffffffffffff", "%p", (void *)0x7fffffffffffffff);
	TEST_PRINTF("%p with 0xffffffffffffffff", "%p", (void *)0xffffffffffffffff);
	TEST_PRINTF("%p with ULONG_MAX formatted", "0x%p-", (void *)ULONG_MAX);
	TEST_PRINTF("%p mixed boundaries", "%pp%p%p", (void *)LONG_MAX, (void *)0, (void *)INT_MAX);
}

// ============================================================================
// DECIMAL INTEGER EDGE CASES - %d
// ============================================================================

void test_d_edge_cases(void)
{
	TEST_START("%d - decimal integer edge cases");
	
	// Zero and boundary values
	TEST_PRINTF("%d with zero", " %d ", 0);
	TEST_PRINTF("%d with -0", " %d ", -0);
	TEST_PRINTF("%d with INT_MAX", " %d ", INT_MAX);
	TEST_PRINTF("%d with INT_MIN", " %d ", INT_MIN);
	
	// Multiple values with boundaries
	TEST_PRINTF("%d with INT_MIN and INT_MAX", " %d %d ", INT_MIN, INT_MAX);
	TEST_PRINTF("%d with 0, INT_MIN, INT_MAX", " %d %d %d ", 0, INT_MIN, INT_MAX);
	TEST_PRINTF("%d with -1, 0, 1, INT_MAX", " %d %d %d %d ", -1, 0, 1, INT_MAX);
	
	// Mixed with text
	TEST_PRINTF("%d INT_MIN with text", "Before %d after", INT_MIN);
	TEST_PRINTF("%d INT_MAX with text", "Before %d after", INT_MAX);
	
	// Near boundaries
	TEST_PRINTF("%d with INT_MAX-1", "%d", INT_MAX - 1);
	TEST_PRINTF("%d with INT_MIN+1", "%d", INT_MIN + 1);
}

// ============================================================================
// INTEGER EDGE CASES - %i
// ============================================================================

void test_i_edge_cases(void)
{
	TEST_START("%i - integer edge cases");
	
	// Same as %d tests
	TEST_PRINTF("%i with zero", " %i ", 0);
	TEST_PRINTF("%i with -0", " %i ", -0);
	TEST_PRINTF("%i with INT_MAX", " %i ", INT_MAX);
	TEST_PRINTF("%i with INT_MIN", " %i ", INT_MIN);
	
	TEST_PRINTF("%i with INT_MIN and INT_MAX", " %i %i ", INT_MIN, INT_MAX);
	TEST_PRINTF("%i with 0, INT_MIN, INT_MAX", " %i %i %i ", 0, INT_MIN, INT_MAX);
	TEST_PRINTF("%i with -1, 0, 1, INT_MAX", " %i %i %i %i ", -1, 0, 1, INT_MAX);
}

// ============================================================================
// UNSIGNED INTEGER EDGE CASES - %u
// ============================================================================

void test_u_edge_cases(void)
{
	TEST_START("%u - unsigned integer edge cases");
	
	// Zero and boundary
	TEST_PRINTF("%u with zero", " %u ", 0);
	TEST_PRINTF("%u with UINT_MAX", " %u ", UINT_MAX);
	
	// Negative numbers (interpreted as unsigned)
	TEST_PRINTF("%u with -1 (wraps to UINT_MAX)", " %u ", -1);
	TEST_PRINTF("%u with -42 (wraps)", " %u ", -42);
	TEST_PRINTF("%u with INT_MIN (wraps)", " %u ", INT_MIN);
	
	// Multiple values
	TEST_PRINTF("%u with 0 and UINT_MAX", " %u %u ", 0, UINT_MAX);
	TEST_PRINTF("%u with 0, -1, UINT_MAX", " %u %u %u ", 0, -1, UINT_MAX);
	
	// Near boundaries
	TEST_PRINTF("%u with UINT_MAX-1", "%u", UINT_MAX - 1);
	TEST_PRINTF("%u with 1", "%u", 1);
}

// ============================================================================
// HEXADECIMAL EDGE CASES - %x and %X
// ============================================================================

void test_x_edge_cases(void)
{
	TEST_START("%x - hexadecimal lowercase edge cases");
	
	// Zero and boundaries
	TEST_PRINTF("%x with zero", " %x ", 0);
	TEST_PRINTF("%x with UINT_MAX (ffffffff)", " %x ", UINT_MAX);
	TEST_PRINTF("%x with INT_MAX (7fffffff)", " %x ", INT_MAX);
	TEST_PRINTF("%x with INT_MIN (80000000)", " %x ", INT_MIN);
	
	// Negative numbers
	TEST_PRINTF("%x with -1 (ffffffff)", " %x ", -1);
	TEST_PRINTF("%x with -42 (ffffffd6)", " %x ", -42);
	
	// Multiple values
	TEST_PRINTF("%x with 0 and UINT_MAX", " %x %x ", 0, UINT_MAX);
	TEST_PRINTF("%x with 0, -1, UINT_MAX", " %x %x %x ", 0, -1, UINT_MAX);
	
	// Hex patterns
	TEST_PRINTF("%x with 0xdeadbeef", "%x", 0xdeadbeef);
	TEST_PRINTF("%x with 0xcafebabe", "%x", 0xcafebabe);
}

void test_X_edge_cases(void)
{
	TEST_START("%X - hexadecimal uppercase edge cases");
	
	// Same tests as lowercase
	TEST_PRINTF("%X with zero", " %X ", 0);
	TEST_PRINTF("%X with UINT_MAX (FFFFFFFF)", " %X ", UINT_MAX);
	TEST_PRINTF("%X with INT_MAX (7FFFFFFF)", " %X ", INT_MAX);
	TEST_PRINTF("%X with INT_MIN (80000000)", " %X ", INT_MIN);
	
	TEST_PRINTF("%X with -1 (FFFFFFFF)", " %X ", -1);
	TEST_PRINTF("%X with -42 (FFFFFFD6)", " %X ", -42);
	
	TEST_PRINTF("%X with 0 and UINT_MAX", " %X %X ", 0, UINT_MAX);
	TEST_PRINTF("%X with 0, -1, UINT_MAX", " %X %X %X ", 0, -1, UINT_MAX);
	
	TEST_PRINTF("%X with 0xDEADBEEF", "%X", 0xDEADBEEF);
	TEST_PRINTF("%X with 0xCAFEBABE", "%X", 0xCAFEBABE);
}

// ============================================================================
// PERCENT EDGE CASES
// ============================================================================

void test_percent_edge_cases(void)
{
	TEST_START("%% - percent escape edge cases");
	
	TEST_PRINTF("single %", "%%");
	TEST_PRINTF("% with spaces", " %% ");
	TEST_PRINTF("triple %", "%%%%%%");
	TEST_PRINTF("% separated by spaces", " %% %% %% ");
	TEST_PRINTF("five consecutive %", "%%%%%%%%%%%%");
	TEST_PRINTF("% with format chars", "%%s%%d%%c");
}

// ============================================================================
// COMPLEX MIX EDGE CASES
// ============================================================================

void test_complex_mix(void)
{
	TEST_START("Complex mixed format edge cases");
	
	// All formats together
	TEST_PRINTF("all formats with boundaries", "%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 
		'A', "42", 42, 42, 42, 42, 42, 
		'B', "-42", -42, -42, -42, -42, 42, 
		'C', "0", 0, 0, 0, 0, 42, 0);
	
	// Mix with NULL and boundaries
	TEST_PRINTF("all formats with NULLs and max values", "%s %p %d %i %u %x %X", (char *)NULL, NULL, INT_MIN, INT_MAX, UINT_MAX, -1, -1);
	
	// Empty and special
	TEST_PRINTF("empty strings with null chars", "%s%c%s%c%s", "", '\0', "", '\0', "");
	
	// Long format string
	TEST_PRINTF("long mixed format string", "Start %d Middle %s End %c More %p Final %x %X", 
		INT_MAX, (char *)NULL, '\0', (void *)0, UINT_MAX, UINT_MAX);
}

// ============================================================================
// WHITESPACE AND SPECIAL CHARACTERS
// ============================================================================

void test_whitespace_edge_cases(void)
{
	TEST_START("Whitespace and special character edge cases");
	
	// Leading/trailing spaces
	TEST_PRINTF("%d with leading space", " %d", 42);
	TEST_PRINTF("%d with trailing space", "%d ", 42);
	TEST_PRINTF("%d with many spaces", "   %d   ", 42);
	
	// Tabs and newlines
	TEST_PRINTF("%d with tabs", "\t%d\t", 42);
	TEST_PRINTF("%d with newlines", "\n%d\n", 42);
	TEST_PRINTF("%d with carriage returns", "\r%d\r", 42);
	
	// Mixed whitespace
	TEST_PRINTF("%d with mixed whitespace", " \t\n\r %d \t\n\r ", 42);
	
	// String with whitespace
	TEST_PRINTF("%s with whitespace string", "%s", " \t\n ");
	TEST_PRINTF("%s with whitespace and spaces", " %s ", " \t\n ");
}

// ============================================================================
// EMPTY FORMAT PATTERNS
// ============================================================================

void test_empty_patterns(void)
{
	TEST_START("Empty and minimal format patterns");
	
	// Just format specifiers
	TEST_PRINTF("%s with empty string", "%s", "");
	TEST_PRINTF("%c with null char", "%c", '\0');
	TEST_PRINTF("%d with zero", "%d", 0);
	
	// Format at start/end
	TEST_PRINTF("%d at start", "%dend", 42);
	TEST_PRINTF("%d at end", "start%d", 42);
	
	// Adjacent formats
	TEST_PRINTF("three adjacent %d", "%d%d%d", 1, 2, 3);
	TEST_PRINTF("three adjacent %s", "%s%s%s", "a", "b", "c");
	TEST_PRINTF("three adjacent %c", "%c%c%c", 'a', 'b', 'c');
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_printf_edge_case_tests(void)
{	
	TEST_WITH_TIMEOUT(test_c_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_s_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_p_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_d_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_i_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_u_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_x_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_X_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_percent_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_complex_mix, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_whitespace_edge_cases, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_empty_patterns, TEST_TIMEOUT_SECONDS);
	
	PRINTF_TEST_SUMMARY();
}
