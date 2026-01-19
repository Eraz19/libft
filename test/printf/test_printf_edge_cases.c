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
#include <stdio.h>
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
	TEST_PRINTF("%c", '\0');
	TEST_PRINTF(" %c ", '\0');
	TEST_PRINTF(" %c %c %c ", '0', '\0', '1');
	TEST_PRINTF(" %c %c %c ", '\0', '1', '2');
	TEST_PRINTF(" %c %c %c ", '2', '1', '\0');
	
	// ASCII boundaries
	TEST_PRINTF("%c", '\0');
	TEST_PRINTF("%c", 127);
	TEST_PRINTF("%c", (char)255);
	
	// Extended ASCII and overflow
	TEST_PRINTF("%c", '0' - 256);
	TEST_PRINTF("%c", '0' + 256);
	
	// Special characters
	TEST_PRINTF(" %c %c %c ", ' ', ' ', ' ');
	TEST_PRINTF(" %c %c %c ", '1', '2', '3');
	TEST_PRINTF("%c%c%c%c%c", '\t', '\n', '\r', '\v', '\f');
}

// ============================================================================
// STRING EDGE CASES - %s
// ============================================================================

void test_s_edge_cases(void)
{
	TEST_START("%s - string edge cases");
	
	const char *long_str = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";
	
	// Empty strings
	TEST_PRINTF("%s", "");
	TEST_PRINTF(" %s", "");
	TEST_PRINTF("%s ", "");
	TEST_PRINTF(" %s ", "");
	
	// Single character strings
	TEST_PRINTF(" %s ", "-");
	TEST_PRINTF(" %s %s ", "", "-");
	TEST_PRINTF(" %s %s ", " - ", "");
	
	// Multiple strings with empty
	TEST_PRINTF(" %s %s %s %s %s", " - ", "", "4", "", long_str);
	TEST_PRINTF(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	
	// NULL string handling
	TEST_PRINTF(" NULL %s NULL ", (char *)NULL);
	TEST_PRINTF("%s", (char *)NULL);
	TEST_PRINTF("%s %s", (char *)NULL, (char *)NULL);
	TEST_PRINTF("%s %s %s", "start", (char *)NULL, "end");
	
	// Strings with special characters
	TEST_PRINTF("%s", "\t\n\r\v\f");
	TEST_PRINTF("%s", "Line1\nLine2\nLine3");
	TEST_PRINTF("%s", "Tab\tseparated\tvalues");
}

// ============================================================================
// POINTER EDGE CASES - %p
// ============================================================================

void test_p_edge_cases(void)
{
	TEST_START("%p - pointer edge cases");
	
	// NULL pointer
	TEST_PRINTF("%p", NULL);
	TEST_PRINTF(" %p ", NULL);
	TEST_PRINTF(" %p %p ", NULL, NULL);
	
	// Small values
	TEST_PRINTF(" %p ", (void *)0);
	TEST_PRINTF(" %p ", (void *)1);
	TEST_PRINTF(" %p ", (void *)15);
	TEST_PRINTF(" %p ", (void *)16);
	TEST_PRINTF(" %p ", (void *)17);
	
	// Negative values (cast as pointers)
	TEST_PRINTF(" %p ", (void *)-1);
	TEST_PRINTF(" %p ", (void *)-14523);
	
	// Boundary values
	TEST_PRINTF(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	TEST_PRINTF(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
	TEST_PRINTF(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	TEST_PRINTF(" %p %p ", (void *)0, (void *)0);
	
	// Large addresses
	TEST_PRINTF("%p", (void *)0x7fffffffffffffff);
	TEST_PRINTF("%p", (void *)0xffffffffffffffff);
	TEST_PRINTF("0x%p-", (void *)ULONG_MAX);
	TEST_PRINTF("%pp%p%p", (void *)LONG_MAX, (void *)0, (void *)INT_MAX);
}

// ============================================================================
// DECIMAL INTEGER EDGE CASES - %d
// ============================================================================

void test_d_edge_cases(void)
{
	TEST_START("%d - decimal integer edge cases");
	
	// Zero and boundary values
	TEST_PRINTF(" %d ", 0);
	TEST_PRINTF(" %d ", -0);
	TEST_PRINTF(" %d ", INT_MAX);
	TEST_PRINTF(" %d ", INT_MIN);
	
	// Multiple values with boundaries
	TEST_PRINTF(" %d %d ", INT_MIN, INT_MAX);
	TEST_PRINTF(" %d %d %d ", 0, INT_MIN, INT_MAX);
	TEST_PRINTF(" %d %d %d %d ", -1, 0, 1, INT_MAX);
	
	// Mixed with text
	TEST_PRINTF("Before %d after", INT_MIN);
	TEST_PRINTF("Before %d after", INT_MAX);
	
	// Near boundaries
	TEST_PRINTF("%d", INT_MAX - 1);
	TEST_PRINTF("%d", INT_MIN + 1);
}

// ============================================================================
// INTEGER EDGE CASES - %i
// ============================================================================

void test_i_edge_cases(void)
{
	TEST_START("%i - integer edge cases");
	
	// Same as %d tests
	TEST_PRINTF(" %i ", 0);
	TEST_PRINTF(" %i ", -0);
	TEST_PRINTF(" %i ", INT_MAX);
	TEST_PRINTF(" %i ", INT_MIN);
	
	TEST_PRINTF(" %i %i ", INT_MIN, INT_MAX);
	TEST_PRINTF(" %i %i %i ", 0, INT_MIN, INT_MAX);
	TEST_PRINTF(" %i %i %i %i ", -1, 0, 1, INT_MAX);
}

// ============================================================================
// UNSIGNED INTEGER EDGE CASES - %u
// ============================================================================

void test_u_edge_cases(void)
{
	TEST_START("%u - unsigned integer edge cases");
	
	// Zero and boundary
	TEST_PRINTF(" %u ", 0);
	TEST_PRINTF(" %u ", UINT_MAX);
	
	// Negative numbers (interpreted as unsigned)
	TEST_PRINTF(" %u ", -1);
	TEST_PRINTF(" %u ", -42);
	TEST_PRINTF(" %u ", INT_MIN);
	
	// Multiple values
	TEST_PRINTF(" %u %u ", 0, UINT_MAX);
	TEST_PRINTF(" %u %u %u ", 0, -1, UINT_MAX);
	
	// Near boundaries
	TEST_PRINTF("%u", UINT_MAX - 1);
	TEST_PRINTF("%u", 1);
}

// ============================================================================
// HEXADECIMAL EDGE CASES - %x and %X
// ============================================================================

void test_x_edge_cases(void)
{
	TEST_START("%x - hexadecimal lowercase edge cases");
	
	// Zero and boundaries
	TEST_PRINTF(" %x ", 0);
	TEST_PRINTF(" %x ", UINT_MAX);
	TEST_PRINTF(" %x ", INT_MAX);
	TEST_PRINTF(" %x ", INT_MIN);
	
	// Negative numbers
	TEST_PRINTF(" %x ", -1);
	TEST_PRINTF(" %x ", -42);
	
	// Multiple values
	TEST_PRINTF(" %x %x ", 0, UINT_MAX);
	TEST_PRINTF(" %x %x %x ", 0, -1, UINT_MAX);
	
	// Hex patterns
	TEST_PRINTF("%x", 0xdeadbeef);
	TEST_PRINTF("%x", 0xcafebabe);
}

void test_X_edge_cases(void)
{
	TEST_START("%X - hexadecimal uppercase edge cases");
	
	// Same tests as lowercase
	TEST_PRINTF(" %X ", 0);
	TEST_PRINTF(" %X ", UINT_MAX);
	TEST_PRINTF(" %X ", INT_MAX);
	TEST_PRINTF(" %X ", INT_MIN);
	
	TEST_PRINTF(" %X ", -1);
	TEST_PRINTF(" %X ", -42);
	
	TEST_PRINTF(" %X %X ", 0, UINT_MAX);
	TEST_PRINTF(" %X %X %X ", 0, -1, UINT_MAX);
	
	TEST_PRINTF("%X", 0xDEADBEEF);
	TEST_PRINTF("%X", 0xCAFEBABE);
}

// ============================================================================
// PERCENT EDGE CASES
// ============================================================================

void test_percent_edge_cases(void)
{
	TEST_START("%% - percent escape edge cases");
	
	TEST_PRINTF("%%");
	TEST_PRINTF(" %% ");
	TEST_PRINTF("%%%%%%");
	TEST_PRINTF(" %% %% %% ");
	TEST_PRINTF("%%%%%%%%%%%%");
	TEST_PRINTF("%%s%%d%%c");
}

// ============================================================================
// COMPLEX MIX EDGE CASES
// ============================================================================

void test_complex_mix(void)
{
	TEST_START("Complex mixed format edge cases");
	
	// All formats together
	TEST_PRINTF("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 
		'A', "42", 42, 42, 42, 42, 42, 
		'B', "-42", -42, -42, -42, -42, 42, 
		'C', "0", 0, 0, 0, 0, 42, 0);
	
	// Mix with NULL and boundaries
	TEST_PRINTF("%s %p %d %i %u %x %X", (char *)NULL, NULL, INT_MIN, INT_MAX, UINT_MAX, -1, -1);
	
	// Empty and special
	TEST_PRINTF("%s%c%s%c%s", "", '\0', "", '\0', "");
	
	// Long format string
	TEST_PRINTF("Start %d Middle %s End %c More %p Final %x %X", 
		INT_MAX, (char *)NULL, '\0', (void *)0, UINT_MAX, UINT_MAX);
}

// ============================================================================
// WHITESPACE AND SPECIAL CHARACTERS
// ============================================================================

void test_whitespace_edge_cases(void)
{
	TEST_START("Whitespace and special character edge cases");
	
	// Leading/trailing spaces
	TEST_PRINTF(" %d", 42);
	TEST_PRINTF("%d ", 42);
	TEST_PRINTF("   %d   ", 42);
	
	// Tabs and newlines
	TEST_PRINTF("\t%d\t", 42);
	TEST_PRINTF("\n%d\n", 42);
	TEST_PRINTF("\r%d\r", 42);
	
	// Mixed whitespace
	TEST_PRINTF(" \t\n\r %d \t\n\r ", 42);
	
	// String with whitespace
	TEST_PRINTF("%s", " \t\n ");
	TEST_PRINTF(" %s ", " \t\n ");
}

// ============================================================================
// EMPTY FORMAT PATTERNS
// ============================================================================

void test_empty_patterns(void)
{
	TEST_START("Empty and minimal format patterns");
	
	// Just format specifiers
	TEST_PRINTF("%s", "");
	TEST_PRINTF("%c", '\0');
	TEST_PRINTF("%d", 0);
	
	// Format at start/end
	TEST_PRINTF("%dend", 42);
	TEST_PRINTF("start%d", 42);
	
	// Adjacent formats
	TEST_PRINTF("%d%d%d", 1, 2, 3);
	TEST_PRINTF("%s%s%s", "a", "b", "c");
	TEST_PRINTF("%c%c%c", 'a', 'b', 'c');
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_printf_edge_case_tests(void)
{	
	test_c_edge_cases();
	test_s_edge_cases();
	test_p_edge_cases();
	test_d_edge_cases();
	test_i_edge_cases();
	test_u_edge_cases();
	test_x_edge_cases();
	test_X_edge_cases();
	test_percent_edge_cases();
	test_complex_mix();
	test_whitespace_edge_cases();
	test_empty_patterns();
	
	TEST_SUMMARY();
}
