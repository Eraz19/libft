/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf_comprehensive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 20:00:00 by Copilot          ###   ########.fr       */
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

// Test counters (shared across test files)
int g_printf_tests_run = 0;
int g_printf_tests_passed = 0;
int g_printf_tests_failed = 0;

// ============================================================================
// SIMPLE FORMAT TESTS
// ============================================================================

void test_simple_formats(void)
{
	TEST_START("Simple formats and %% escape");
	
	// No format
	TEST_PRINTF("empty string", "");
	TEST_PRINTF("plain text 'hello world'", "hello world");
	TEST_PRINTF("special escape sequences", "\x01\x02\a\v\b\f\r\n");
	
	// Percent escape
	TEST_PRINTF("single %", "%%");
	TEST_PRINTF("% with spaces", " %%");
	TEST_PRINTF("% followed by c", "%%c");
	TEST_PRINTF("triple %", "%%%%%%");
	TEST_PRINTF("% mixed with %c", "%%%c", 'x');
}

// ============================================================================
// CHARACTER FORMAT TESTS - %c
// ============================================================================

void test_c_format(void)
{
	TEST_START("%c - character format");
	
	TEST_PRINTF("%c with 'x'", "%c", 'x');
	TEST_PRINTF("%c with leading space", " %c", 'x');
	TEST_PRINTF("%c with trailing space", "%c ", 'x');
	TEST_PRINTF("%c with tab character", "%c%c%c", 'a', '\t', 'b');
	TEST_PRINTF("multiple %c with literals", "%cc%cc%c", 'a', '\t', 'b');
	TEST_PRINTF("%c mixed with 's'", "%cs%cs%c", 'c', 'b', 'a');
	TEST_PRINTF("%c with null character (0)", "%c", 0);
	TEST_PRINTF("%c with ASCII 127", "%c", 127);
}

// ============================================================================
// STRING FORMAT TESTS - %s
// ============================================================================

void test_s_format(void)
{
	TEST_START("%s - string format");
	
	TEST_PRINTF("%s with empty string", "%s", "");
	TEST_PRINTF("%s with NULL", "%s", (char *)NULL);
	TEST_PRINTF("%s with 'hello world'", "%s", "hello world");
	TEST_PRINTF("%s with literal % inside", "%s", "some string with %s hehe");
	TEST_PRINTF("%s with tabs and newlines", " %s", "can it handle \t and \n?");
	TEST_PRINTF("%s with special chars", "%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	TEST_PRINTF("multiple %s concatenated", "%s%s%s", "And ", "some", "joined");
	TEST_PRINTF("%s mixed with literals", "%ss%ss%ss", "And ", "some other", "joined");
}

// ============================================================================
// POINTER FORMAT TESTS - %p
// ============================================================================

void test_p_format(void)
{
	TEST_START("%p - pointer format");
	
	TEST_PRINTF("%p with empty string address", "%p", "");
	TEST_PRINTF("%p with NULL", "%p", NULL);
	TEST_PRINTF("%p with negative value", "%p", (void *)-14523);
	TEST_PRINTF("%p with ULONG_MAX", "0x%p-", (void *)ULONG_MAX);
	TEST_PRINTF("multiple %p mixed", "%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	TEST_PRINTF("%p with large hex value", "%p", (void *)0x123456789abcdef);
}

// ============================================================================
// DECIMAL FORMAT TESTS - %d
// ============================================================================

void test_d_format(void)
{
	TEST_START("%d - decimal integer format");
	
	TEST_PRINTF("%d with zero", "%d", 0);
	TEST_PRINTF("%d with -10", "%d", -10);
	TEST_PRINTF("%d with -200000", "%d", -200000);
	TEST_PRINTF("%d with -6000023", "%d", -6000023);
	TEST_PRINTF("%d with 10", "%d", 10);
	TEST_PRINTF("%d with 10000", "%d", 10000);
	TEST_PRINTF("%d with 100023", "%d", 100023);
	TEST_PRINTF("%d with INT_MAX", "%d", INT_MAX);
	TEST_PRINTF("%d with INT_MIN", "%d", INT_MIN);
	TEST_PRINTF("%d mixed with text", "dgs%dxx", 10);
	TEST_PRINTF("multiple %d with negatives", "%d%dd%d", 1, 2, -3);
}

// ============================================================================
// INTEGER FORMAT TESTS - %i
// ============================================================================

void test_i_format(void)
{
	TEST_START("%i - integer format");
	
	TEST_PRINTF("%i with zero", "%i", 0);
	TEST_PRINTF("%i with -10", "%i", -10);
	TEST_PRINTF("%i with -200000", "%i", -200000);
	TEST_PRINTF("%i with -6000023", "%i", -6000023);
	TEST_PRINTF("%i with 10", "%i", 10);
	TEST_PRINTF("%i with 10000", "%i", 10000);
	TEST_PRINTF("%i with 100023", "%i", 100023);
	TEST_PRINTF("%i with INT_MAX", "%i", INT_MAX);
	TEST_PRINTF("%i with INT_MIN", "%i", INT_MIN);
	TEST_PRINTF("%i mixed with text", "dgs%ixx", 10);
	TEST_PRINTF("multiple %i with negatives", "%i%ii%i", 1, 2, -3);
}

// ============================================================================
// UNSIGNED FORMAT TESTS - %u
// ============================================================================

void test_u_format(void)
{
	TEST_START("%u - unsigned integer format");
	
	TEST_PRINTF("%u with zero", "%u", 0);
	TEST_PRINTF("%u with 10", "%u", 10);
	TEST_PRINTF("%u with 10000", "%u", 10000);
	TEST_PRINTF("%u with 100023", "%u", 100023);
	TEST_PRINTF("%u with INT_MAX", "%u", INT_MAX);
	TEST_PRINTF("%u with INT_MIN (unsigned)", "%u", INT_MIN);
	TEST_PRINTF("%u with UINT_MAX", "%u", UINT_MAX);
	TEST_PRINTF("%u mixed with text", "dgs%uxx", 10);
	TEST_PRINTF("multiple %u with negative", "%u%uu%u", 1, 2, -3);
	TEST_PRINTF("%u with -10 (wraps)", "%u", (unsigned int)-10);
	TEST_PRINTF("%u with -200000 (wraps)", "%u", (unsigned int)-200000);
}

// ============================================================================
// HEXADECIMAL LOWERCASE FORMAT TESTS - %x
// ============================================================================

void test_x_format(void)
{
	TEST_START("%x - hexadecimal lowercase format");
	
	TEST_PRINTF("%x with zero", "%x", 0);
	TEST_PRINTF("%x with 10 (a)", "%x", 10);
	TEST_PRINTF("%x with 10000 (2710)", "%x", 10000);
	TEST_PRINTF("%x with 100023 (186b7)", "%x", 100023);
	TEST_PRINTF("%x with 0xabcdef", "%x", 0xabcdef);
	TEST_PRINTF("%x with 0x7fedcba1", "%x", 0x7fedcba1);
	TEST_PRINTF("%x with INT_MAX", "%x", INT_MAX);
	TEST_PRINTF("%x with INT_MIN", "%x", INT_MIN);
	TEST_PRINTF("%x with UINT_MAX", "%x", UINT_MAX);
	TEST_PRINTF("%x mixed with text", "dgs%xxx", 10);
	TEST_PRINTF("multiple %x with negative", "%x%xx%x", 1, 2, -3);
	TEST_PRINTF("%x with -10 (wraps)", "%x", (unsigned int)-10);
	TEST_PRINTF("%x with -200000 (wraps)", "%x", (unsigned int)-200000);
}

// ============================================================================
// HEXADECIMAL UPPERCASE FORMAT TESTS - %X
// ============================================================================

void test_X_format(void)
{
	TEST_START("%X - hexadecimal uppercase format");
	
	TEST_PRINTF("%X with zero", "%X", 0);
	TEST_PRINTF("%X with 10 (A)", "%X", 10);
	TEST_PRINTF("%X with 10000 (2710)", "%X", 10000);
	TEST_PRINTF("%X with 100023 (186B7)", "%X", 100023);
	TEST_PRINTF("%X with 0xABCDEF", "%X", 0xabcdef);
	TEST_PRINTF("%X with 0x7FEDCBA1", "%X", 0x7fedcba1);
	TEST_PRINTF("%X with INT_MAX", "%X", INT_MAX);
	TEST_PRINTF("%X with INT_MIN", "%X", INT_MIN);
	TEST_PRINTF("%X with UINT_MAX", "%X", UINT_MAX);
	TEST_PRINTF("%X mixed with text", "dgs%Xxx", 10);
	TEST_PRINTF("multiple %X with negative", "%X%Xx%X", 1, 2, -3);
	TEST_PRINTF("%X with -10 (wraps)", "%X", (unsigned int)-10);
	TEST_PRINTF("%X with -200000 (wraps)", "%X", (unsigned int)-200000);
}

// ============================================================================
// MIXED FORMAT TESTS
// ============================================================================

void test_mixed_formats(void)
{
	TEST_START("Mixed format specifiers");
	
	TEST_PRINTF("%d %s %c combination", "%d %s %c", 42, "hello", 'x');
	TEST_PRINTF("%c %s %d %p combination", "%c %s %d %p", 'A', "test", -100, (void *)0x123);
	TEST_PRINTF("%x %X %u %d with 255", "%x %X %u %d", 255, 255, 255, 255);
	TEST_PRINTF("escaped % with formats", "%%d = %d, %%s = %s", 100, "string");
	TEST_PRINTF("all format specifiers", "%s%c%d%i%u%x%X%p%%", "str", 'c', 1, 2, 3, 4, 5, (void *)6);
}

// ============================================================================
// EDGE CASES AND BOUNDARY TESTS
// ============================================================================

void test_edge_cases(void)
{
	TEST_START("Edge cases and boundary conditions");
	
	// Empty and NULL
	TEST_PRINTF("empty format string", "");
	TEST_PRINTF("%s with NULL pointer", "%s", (char *)NULL);
	TEST_PRINTF("%p with NULL pointer", "%p", NULL);
	
	// Boundary values
	TEST_PRINTF("%d with INT_MIN boundary", "%d", INT_MIN);
	TEST_PRINTF("%d with INT_MAX boundary", "%d", INT_MAX);
	TEST_PRINTF("%u with UINT_MAX boundary", "%u", UINT_MAX);
	TEST_PRINTF("%x with UINT_MAX boundary", "%x", UINT_MAX);
	TEST_PRINTF("%X with UINT_MAX boundary", "%X", UINT_MAX);
	
	// Special characters
	TEST_PRINTF("%c with 0, 127, 255", "%c%c%c", 0, 127, 255);
	TEST_PRINTF("%s with escape sequences", "%s", "\n\t\r\v\f");
	
	// Multiple nulls
	TEST_PRINTF("three NULL strings", "%s %s %s", (char *)NULL, (char *)NULL, (char *)NULL);
	TEST_PRINTF("three NULL pointers", "%p %p %p", NULL, NULL, NULL);
}

// ============================================================================
// RETURN VALUE TESTS
// ============================================================================

void test_return_values(void)
{
	TEST_START("Return value correctness");
	
	// Should return number of characters printed
	TEST_PRINTF("return value: 'hello' (5)", "hello");
	TEST_PRINTF("return value: %d 42 (2)", "%d", 42);
	TEST_PRINTF("return value: 'test string' (11)", "%s", "test string");
	TEST_PRINTF("return value: %c x3 (3)", "%c%c%c", 'a', 'b', 'c');
	TEST_PRINTF("return value: empty (0)", "");
	TEST_PRINTF("return value: % (1)", "%%");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_printf_comprehensive_tests(void)
{	
	test_simple_formats();
	test_c_format();
	test_s_format();
	test_p_format();
	test_d_format();
	test_i_format();
	test_u_format();
	test_x_format();
	test_X_format();
	test_mixed_formats();
	test_edge_cases();
	test_return_values();
	
	TEST_SUMMARY();
}
