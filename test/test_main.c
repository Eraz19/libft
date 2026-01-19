/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:30:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 19:45:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include <stdio.h>

// Forward declarations from test files
void run_comprehensive_tests(void);
void run_edge_case_tests(void);
void run_buffer_comprehensive_tests(void);
void run_buffer_edge_case_tests(void);
void run_list_comprehensive_tests(void);
void run_list_edge_case_tests(void);
void run_char_comprehensive_tests(void);
void run_math_comprehensive_tests(void);
void run_printf_comprehensive_tests(void);
void run_printf_edge_case_tests(void);

// External test counters from string tests
extern int g_tests_run;
extern int g_tests_passed;
extern int g_tests_failed;

// External test counters from buffer tests
extern int g_buf_tests_run;
extern int g_buf_tests_passed;
extern int g_buf_tests_failed;

// External test counters from list tests
extern int g_list_tests_run;
extern int g_list_tests_passed;
extern int g_list_tests_failed;

// External test counters from char tests
extern int g_char_tests_run;
extern int g_char_tests_passed;
extern int g_char_tests_failed;

// External test counters from math tests
extern int g_math_tests_run;
extern int g_math_tests_passed;
extern int g_math_tests_failed;

// External test counters from printf tests
extern int g_printf_tests_run;
extern int g_printf_tests_passed;
extern int g_printf_tests_failed;

int main(void)
{
	int total_tests = 0;
	int total_passed = 0;
	int total_failed = 0;

	// ========================================================================
	// STRING LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- STRING LIBRARY TEST SUITE -------\n" COLOR_RESET);

	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("      STRING LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_comprehensive_tests();

	printf("\n");
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("      STRING LIBRARY - EDGE CASE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);
	
	run_edge_case_tests();

	// Collect string test results
	int string_tests = g_tests_run;
	int string_passed = g_tests_passed;
	int string_failed = g_tests_failed;

	// ========================================================================
	// BUFFER LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- BUFFER LIBRARY TEST SUITE -------\n" COLOR_RESET);

	// Run comprehensive buffer tests
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("      BUFFER LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_buffer_comprehensive_tests();

	// Run edge case buffer tests
	printf("\n");
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("      BUFFER LIBRARY - EDGE CASE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_buffer_edge_case_tests();

	// Collect buffer test results
	int buffer_tests = g_buf_tests_run;
	int buffer_passed = g_buf_tests_passed;
	int buffer_failed = g_buf_tests_failed;

	// ========================================================================
	// LIST LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- LIST LIBRARY TEST SUITE -------\n" COLOR_RESET);

	// Run comprehensive list tests
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("        LIST LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_list_comprehensive_tests();
	
	// Run edge case list tests
	printf("\n");
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("        LIST LIBRARY - EDGE CASE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	printf("\n");
	run_list_edge_case_tests();

	// Collect list test results
	int list_tests = g_list_tests_run;
	int list_passed = g_list_tests_passed;
	int list_failed = g_list_tests_failed;

	// ========================================================================
	// CHAR LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- CHAR LIBRARY TEST SUITE -------\n" COLOR_RESET);

	// Run comprehensive char tests
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("        CHAR LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_char_comprehensive_tests();

	// Collect char test results
	int char_tests = g_char_tests_run;
	int char_passed = g_char_tests_passed;
	int char_failed = g_char_tests_failed;

	// ========================================================================
	// MATH LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- MATH LIBRARY TEST SUITE -------\n" COLOR_RESET);

	// Run comprehensive math tests
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("        MATH LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_math_comprehensive_tests();

	// Collect math test results
	int math_tests = g_math_tests_run;
	int math_passed = g_math_tests_passed;
	int math_failed = g_math_tests_failed;

	// ========================================================================
	// PRINTF LIBRARY TESTS
	// ========================================================================
	
	printf("\n");
	printf(COLOR_CYAN " ------- PRINTF LIBRARY TEST SUITE -------\n" COLOR_RESET);

	// Run comprehensive printf tests
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("         PRINTF LIBRARY - COMPREHENSIVE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_printf_comprehensive_tests();

	// Run edge case printf tests
	printf("\n");
	printf(COLOR_BLUE "════════════════════════════════════════════════════\n");
	printf("         PRINTF LIBRARY - EDGE CASE TESTS     \n");
	printf("════════════════════════════════════════════════════\n" COLOR_RESET);

	run_printf_edge_case_tests();

	// Collect printf test results
	int printf_tests = g_printf_tests_run;
	int printf_passed = g_printf_tests_passed;
	int printf_failed = g_printf_tests_failed;

	// ========================================================================
	// OVERALL SUMMARY
	// ========================================================================
	
	total_tests = string_tests + buffer_tests + list_tests + char_tests + math_tests + printf_tests;
	total_passed = string_passed + buffer_passed + list_passed + char_passed + math_passed + printf_passed;
	total_failed = string_failed + buffer_failed + list_failed + char_failed + math_failed + printf_failed;

	printf("\n");
	printf(COLOR_MAGENTA "╔════════════════════════════════════════════════════╗\n");
	printf("║              OVERALL TEST SUMMARY                  ║\n");
	printf("╚════════════════════════════════════════════════════╝\n" COLOR_RESET);
	printf("\n");

	printf(COLOR_CYAN "String Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		string_tests, string_passed);
	if (string_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", string_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_CYAN "Buffer Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		buffer_tests, buffer_passed);
	if (buffer_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", buffer_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_CYAN "List Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		list_tests, list_passed);
	if (list_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", list_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_CYAN "Char Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		char_tests, char_passed);
	if (char_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", char_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_CYAN "Math Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		math_tests, math_passed);
	if (math_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", math_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_CYAN "Printf Library Results:\n" COLOR_RESET);
	printf("  Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", 
		printf_tests, printf_passed);
	if (printf_failed > 0)
		printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", printf_failed);
	else
		printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n");

	printf("\n");
	printf(COLOR_BLUE "═══════════════════════════════════════════════════\n" COLOR_RESET);
	printf(COLOR_YELLOW "Combined Total: %d tests\n" COLOR_RESET, total_tests);
	printf(COLOR_GREEN "✓ Passed: %d (%.1f%%)\n" COLOR_RESET, 
		total_passed, (total_tests > 0) ? (100.0 * total_passed / total_tests) : 0);
	if (total_failed > 0)
		printf(COLOR_RED "✗ Failed: %d (%.1f%%)\n" COLOR_RESET, 
			total_failed, (100.0 * total_failed / total_tests));
	else
		printf(COLOR_GREEN "✗ Failed: 0\n" COLOR_RESET);
	printf(COLOR_BLUE "═══════════════════════════════════════════════════\n" COLOR_RESET);
	printf("\n");

	if (total_failed == 0)
		printf(COLOR_GREEN "🎉 All tests passed! 🎉\n" COLOR_RESET);
	else
		printf(COLOR_YELLOW "⚠️  Some tests failed. Please review the output above.\n" COLOR_RESET);

	printf("\n");

	return (total_failed > 0) ? 1 : 0;
}
