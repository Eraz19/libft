/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math_comprehensive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 19:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"
#include <stdio.h>
#include <limits.h>

// Override TEST_ASSERT and TEST_SUMMARY to use math-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT MATH_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY MATH_TEST_SUMMARY

// Test counters (shared across test files)
int g_math_tests_run = 0;
int g_math_tests_passed = 0;
int g_math_tests_failed = 0;

// ============================================================================
// ABSOLUTE VALUE TESTS - abs_i
// ============================================================================

void test_abs_i(void)
{
	TEST_START("abs_i - absolute value for 32-bit integers");
	
	// Positive numbers
	TEST_ASSERT(abs_i(0) == 0, "abs(0) returns 0");
	TEST_ASSERT(abs_i(1) == 1, "abs(1) returns 1");
	TEST_ASSERT(abs_i(42) == 42, "abs(42) returns 42");
	TEST_ASSERT(abs_i(12345) == 12345, "abs(12345) returns 12345");
	TEST_ASSERT(abs_i(I32_MAX) == (t_u32)I32_MAX, "abs(INT_MAX) returns INT_MAX");
	
	// Negative numbers
	TEST_ASSERT(abs_i(-1) == 1, "abs(-1) returns 1");
	TEST_ASSERT(abs_i(-42) == 42, "abs(-42) returns 42");
	TEST_ASSERT(abs_i(-12345) == 12345, "abs(-12345) returns 12345");
	TEST_ASSERT(abs_i(-100) == 100, "abs(-100) returns 100");
	
	// Edge case: INT_MIN
	TEST_ASSERT(abs_i(I32_MIN) == (t_u32)I32_MAX + 1, 
		"abs(INT_MIN) returns INT_MAX + 1 (as unsigned)");
	
	// Values near boundaries
	TEST_ASSERT(abs_i(I32_MAX - 1) == (t_u32)(I32_MAX - 1), 
		"abs(INT_MAX - 1) correct");
	TEST_ASSERT(abs_i(I32_MIN + 1) == (t_u32)I32_MAX, 
		"abs(INT_MIN + 1) returns INT_MAX");
}

// ============================================================================
// ABSOLUTE VALUE TESTS - abs_l
// ============================================================================

void test_abs_l(void)
{
	TEST_START("abs_l - absolute value for 64-bit integers");
	
	// Positive numbers
	TEST_ASSERT(abs_l(0L) == 0UL, "abs(0L) returns 0");
	TEST_ASSERT(abs_l(1L) == 1UL, "abs(1L) returns 1");
	TEST_ASSERT(abs_l(42L) == 42UL, "abs(42L) returns 42");
	TEST_ASSERT(abs_l(123456789L) == 123456789UL, "abs(123456789L) returns 123456789");
	TEST_ASSERT(abs_l(I64_MAX) == (t_u64)I64_MAX, "abs(LONG_MAX) returns LONG_MAX");
	
	// Negative numbers
	TEST_ASSERT(abs_l(-1L) == 1UL, "abs(-1L) returns 1");
	TEST_ASSERT(abs_l(-42L) == 42UL, "abs(-42L) returns 42");
	TEST_ASSERT(abs_l(-123456789L) == 123456789UL, "abs(-123456789L) returns 123456789");
	TEST_ASSERT(abs_l(-1000L) == 1000UL, "abs(-1000L) returns 1000");
	
	// Edge case: LONG_MIN
	TEST_ASSERT(abs_l(I64_MIN) == (t_u64)I64_MAX + 1, 
		"abs(LONG_MIN) returns LONG_MAX + 1 (as unsigned)");
	
	// Values near boundaries
	TEST_ASSERT(abs_l(I64_MAX - 1) == (t_u64)(I64_MAX - 1), 
		"abs(LONG_MAX - 1) correct");
	TEST_ASSERT(abs_l(I64_MIN + 1) == (t_u64)I64_MAX, 
		"abs(LONG_MIN + 1) returns LONG_MAX");
	
	// Large values
	TEST_ASSERT(abs_l(1000000000000L) == 1000000000000UL, 
		"abs(1000000000000L) correct");
	TEST_ASSERT(abs_l(-1000000000000L) == 1000000000000UL, 
		"abs(-1000000000000L) correct");
}

// ============================================================================
// CROSS-SIZE COMPARISON TESTS
// ============================================================================

void test_abs_comparison(void)
{
	TEST_START("abs_i and abs_l - consistency checks");
	
	// Same values should produce same results for both functions
	TEST_ASSERT(abs_i(42) == abs_l(42L), "abs_i(42) == abs_l(42L)");
	TEST_ASSERT(abs_i(-42) == abs_l(-42L), "abs_i(-42) == abs_l(-42L)");
	TEST_ASSERT(abs_i(0) == abs_l(0L), "abs_i(0) == abs_l(0L)");
	TEST_ASSERT(abs_i(I32_MAX) == abs_l((t_i64)I32_MAX), 
		"abs_i(INT_MAX) == abs_l(INT_MAX as long)");
	TEST_ASSERT(abs_i(I32_MIN) == abs_l((t_i64)I32_MIN), 
		"abs_i(INT_MIN) == abs_l(INT_MIN as long)");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_math_comprehensive_tests(void)
{	
	test_abs_i();
	test_abs_l();
	test_abs_comparison();
	
	TEST_SUMMARY();
}
