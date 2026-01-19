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
	TEST_PRINTF("");
	TEST_PRINTF("hello world");
	TEST_PRINTF("\x01\x02\a\v\b\f\r\n");
	
	// Percent escape
	TEST_PRINTF("%%");
	TEST_PRINTF(" %%");
	TEST_PRINTF("%%c");
	TEST_PRINTF("%%%%%%");
	TEST_PRINTF("%%%c", 'x');
}

// ============================================================================
// CHARACTER FORMAT TESTS - %c
// ============================================================================

void test_c_format(void)
{
	TEST_START("%c - character format");
	
	TEST_PRINTF("%c", 'x');
	TEST_PRINTF(" %c", 'x');
	TEST_PRINTF("%c ", 'x');
	TEST_PRINTF("%c%c%c", 'a', '\t', 'b');
	TEST_PRINTF("%cc%cc%c", 'a', '\t', 'b');
	TEST_PRINTF("%cs%cs%c", 'c', 'b', 'a');
	TEST_PRINTF("%c", 0);
	TEST_PRINTF("%c", 127);
}

// ============================================================================
// STRING FORMAT TESTS - %s
// ============================================================================

void test_s_format(void)
{
	TEST_START("%s - string format");
	
	TEST_PRINTF("%s", "");
	TEST_PRINTF("%s", (char *)NULL);
	TEST_PRINTF("%s", "hello world");
	TEST_PRINTF("%s", "some string with %s hehe");
	TEST_PRINTF(" %s", "can it handle \t and \n?");
	TEST_PRINTF("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	TEST_PRINTF("%s%s%s", "And ", "some", "joined");
	TEST_PRINTF("%ss%ss%ss", "And ", "some other", "joined");
}

// ============================================================================
// POINTER FORMAT TESTS - %p
// ============================================================================

void test_p_format(void)
{
	TEST_START("%p - pointer format");
	
	TEST_PRINTF("%p", "");
	TEST_PRINTF("%p", NULL);
	TEST_PRINTF("%p", (void *)-14523);
	TEST_PRINTF("0x%p-", (void *)ULONG_MAX);
	TEST_PRINTF("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	TEST_PRINTF("%p", (void *)0x123456789abcdef);
}

// ============================================================================
// DECIMAL FORMAT TESTS - %d
// ============================================================================

void test_d_format(void)
{
	TEST_START("%d - decimal integer format");
	
	TEST_PRINTF("%d", 0);
	TEST_PRINTF("%d", -10);
	TEST_PRINTF("%d", -200000);
	TEST_PRINTF("%d", -6000023);
	TEST_PRINTF("%d", 10);
	TEST_PRINTF("%d", 10000);
	TEST_PRINTF("%d", 100023);
	TEST_PRINTF("%d", INT_MAX);
	TEST_PRINTF("%d", INT_MIN);
	TEST_PRINTF("dgs%dxx", 10);
	TEST_PRINTF("%d%dd%d", 1, 2, -3);
}

// ============================================================================
// INTEGER FORMAT TESTS - %i
// ============================================================================

void test_i_format(void)
{
	TEST_START("%i - integer format");
	
	TEST_PRINTF("%i", 0);
	TEST_PRINTF("%i", -10);
	TEST_PRINTF("%i", -200000);
	TEST_PRINTF("%i", -6000023);
	TEST_PRINTF("%i", 10);
	TEST_PRINTF("%i", 10000);
	TEST_PRINTF("%i", 100023);
	TEST_PRINTF("%i", INT_MAX);
	TEST_PRINTF("%i", INT_MIN);
	TEST_PRINTF("dgs%ixx", 10);
	TEST_PRINTF("%i%ii%i", 1, 2, -3);
}

// ============================================================================
// UNSIGNED FORMAT TESTS - %u
// ============================================================================

void test_u_format(void)
{
	TEST_START("%u - unsigned integer format");
	
	TEST_PRINTF("%u", 0);
	TEST_PRINTF("%u", 10);
	TEST_PRINTF("%u", 10000);
	TEST_PRINTF("%u", 100023);
	TEST_PRINTF("%u", INT_MAX);
	TEST_PRINTF("%u", INT_MIN);
	TEST_PRINTF("%u", UINT_MAX);
	TEST_PRINTF("dgs%uxx", 10);
	TEST_PRINTF("%u%uu%u", 1, 2, -3);
	TEST_PRINTF("%u", (unsigned int)-10);
	TEST_PRINTF("%u", (unsigned int)-200000);
}

// ============================================================================
// HEXADECIMAL LOWERCASE FORMAT TESTS - %x
// ============================================================================

void test_x_format(void)
{
	TEST_START("%x - hexadecimal lowercase format");
	
	TEST_PRINTF("%x", 0);
	TEST_PRINTF("%x", 10);
	TEST_PRINTF("%x", 10000);
	TEST_PRINTF("%x", 100023);
	TEST_PRINTF("%x", 0xabcdef);
	TEST_PRINTF("%x", 0x7fedcba1);
	TEST_PRINTF("%x", INT_MAX);
	TEST_PRINTF("%x", INT_MIN);
	TEST_PRINTF("%x", UINT_MAX);
	TEST_PRINTF("dgs%xxx", 10);
	TEST_PRINTF("%x%xx%x", 1, 2, -3);
	TEST_PRINTF("%x", (unsigned int)-10);
	TEST_PRINTF("%x", (unsigned int)-200000);
}

// ============================================================================
// HEXADECIMAL UPPERCASE FORMAT TESTS - %X
// ============================================================================

void test_X_format(void)
{
	TEST_START("%X - hexadecimal uppercase format");
	
	TEST_PRINTF("%X", 0);
	TEST_PRINTF("%X", 10);
	TEST_PRINTF("%X", 10000);
	TEST_PRINTF("%X", 100023);
	TEST_PRINTF("%X", 0xabcdef);
	TEST_PRINTF("%X", 0x7fedcba1);
	TEST_PRINTF("%X", INT_MAX);
	TEST_PRINTF("%X", INT_MIN);
	TEST_PRINTF("%X", UINT_MAX);
	TEST_PRINTF("dgs%Xxx", 10);
	TEST_PRINTF("%X%Xx%X", 1, 2, -3);
	TEST_PRINTF("%X", (unsigned int)-10);
	TEST_PRINTF("%X", (unsigned int)-200000);
}

// ============================================================================
// MIXED FORMAT TESTS
// ============================================================================

void test_mixed_formats(void)
{
	TEST_START("Mixed format specifiers");
	
	TEST_PRINTF("%d %s %c", 42, "hello", 'x');
	TEST_PRINTF("%c %s %d %p", 'A', "test", -100, (void *)0x123);
	TEST_PRINTF("%x %X %u %d", 255, 255, 255, 255);
	TEST_PRINTF("%%d = %d, %%s = %s", 100, "string");
	TEST_PRINTF("%s%c%d%i%u%x%X%p%%", "str", 'c', 1, 2, 3, 4, 5, (void *)6);
}

// ============================================================================
// EDGE CASES AND BOUNDARY TESTS
// ============================================================================

void test_edge_cases(void)
{
	TEST_START("Edge cases and boundary conditions");
	
	// Empty and NULL
	TEST_PRINTF("");
	TEST_PRINTF("%s", (char *)NULL);
	TEST_PRINTF("%p", NULL);
	
	// Boundary values
	TEST_PRINTF("%d", INT_MIN);
	TEST_PRINTF("%d", INT_MAX);
	TEST_PRINTF("%u", UINT_MAX);
	TEST_PRINTF("%x", UINT_MAX);
	TEST_PRINTF("%X", UINT_MAX);
	
	// Special characters
	TEST_PRINTF("%c%c%c", 0, 127, 255);
	TEST_PRINTF("%s", "\n\t\r\v\f");
	
	// Multiple nulls
	TEST_PRINTF("%s %s %s", (char *)NULL, (char *)NULL, (char *)NULL);
	TEST_PRINTF("%p %p %p", NULL, NULL, NULL);
}

// ============================================================================
// RETURN VALUE TESTS
// ============================================================================

void test_return_values(void)
{
	TEST_START("Return value correctness");
	
	// Should return number of characters printed
	TEST_PRINTF("hello");
	TEST_PRINTF("%d", 42);
	TEST_PRINTF("%s", "test string");
	TEST_PRINTF("%c%c%c", 'a', 'b', 'c');
	TEST_PRINTF("");
	TEST_PRINTF("%%");
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
