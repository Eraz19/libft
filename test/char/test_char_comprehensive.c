/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_char_comprehensive.c                          :+:      :+:    :+:   */
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

// Override TEST_ASSERT and TEST_SUMMARY to use char-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT CHAR_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY CHAR_TEST_SUMMARY

// Test counters (shared across test files)
int g_char_tests_run = 0;
int g_char_tests_passed = 0;
int g_char_tests_failed = 0;

// ============================================================================
// CHARACTER CLASSIFICATION TESTS
// ============================================================================

void test_c_isalpha(void)
{
	TEST_START("c_isalpha - alphabetic character check");
	
	// Lowercase letters
	TEST_ASSERT(c_isalpha('a') == TRUE, "Lowercase 'a' is alpha");
	TEST_ASSERT(c_isalpha('z') == TRUE, "Lowercase 'z' is alpha");
	TEST_ASSERT(c_isalpha('m') == TRUE, "Lowercase 'm' is alpha");
	
	// Uppercase letters
	TEST_ASSERT(c_isalpha('A') == TRUE, "Uppercase 'A' is alpha");
	TEST_ASSERT(c_isalpha('Z') == TRUE, "Uppercase 'Z' is alpha");
	TEST_ASSERT(c_isalpha('M') == TRUE, "Uppercase 'M' is alpha");
	
	// Non-alphabetic
	TEST_ASSERT(c_isalpha('0') == FALSE, "Digit '0' is not alpha");
	TEST_ASSERT(c_isalpha('9') == FALSE, "Digit '9' is not alpha");
	TEST_ASSERT(c_isalpha(' ') == FALSE, "Space is not alpha");
	TEST_ASSERT(c_isalpha('!') == FALSE, "Punctuation '!' is not alpha");
	TEST_ASSERT(c_isalpha('\n') == FALSE, "Newline is not alpha");
	TEST_ASSERT(c_isalpha('\0') == FALSE, "Null byte is not alpha");
	
	// Edge cases
	TEST_ASSERT(c_isalpha('@') == FALSE, "Character before 'A' is not alpha");
	TEST_ASSERT(c_isalpha('[') == FALSE, "Character after 'Z' is not alpha");
	TEST_ASSERT(c_isalpha('`') == FALSE, "Character before 'a' is not alpha");
	TEST_ASSERT(c_isalpha('{') == FALSE, "Character after 'z' is not alpha");
}

void test_c_isdigit(void)
{
	TEST_START("c_isdigit - digit character check");
	
	// Digits
	TEST_ASSERT(c_isdigit('0') == TRUE, "Character '0' is digit");
	TEST_ASSERT(c_isdigit('1') == TRUE, "Character '1' is digit");
	TEST_ASSERT(c_isdigit('5') == TRUE, "Character '5' is digit");
	TEST_ASSERT(c_isdigit('9') == TRUE, "Character '9' is digit");
	
	// Non-digits
	TEST_ASSERT(c_isdigit('a') == FALSE, "Lowercase letter is not digit");
	TEST_ASSERT(c_isdigit('Z') == FALSE, "Uppercase letter is not digit");
	TEST_ASSERT(c_isdigit(' ') == FALSE, "Space is not digit");
	TEST_ASSERT(c_isdigit('\n') == FALSE, "Newline is not digit");
	TEST_ASSERT(c_isdigit('\0') == FALSE, "Null byte is not digit");
	
	// Edge cases
	TEST_ASSERT(c_isdigit('/') == FALSE, "Character before '0' is not digit");
	TEST_ASSERT(c_isdigit(':') == FALSE, "Character after '9' is not digit");
}

void test_c_isalnum(void)
{
	TEST_START("c_isalnum - alphanumeric character check");
	
	// Alphanumeric
	TEST_ASSERT(c_isalnum('a') == TRUE, "Lowercase letter is alnum");
	TEST_ASSERT(c_isalnum('Z') == TRUE, "Uppercase letter is alnum");
	TEST_ASSERT(c_isalnum('0') == TRUE, "Digit '0' is alnum");
	TEST_ASSERT(c_isalnum('9') == TRUE, "Digit '9' is alnum");
	TEST_ASSERT(c_isalnum('m') == TRUE, "Lowercase 'm' is alnum");
	TEST_ASSERT(c_isalnum('5') == TRUE, "Digit '5' is alnum");
	
	// Non-alphanumeric
	TEST_ASSERT(c_isalnum(' ') == FALSE, "Space is not alnum");
	TEST_ASSERT(c_isalnum('!') == FALSE, "Punctuation is not alnum");
	TEST_ASSERT(c_isalnum('\n') == FALSE, "Newline is not alnum");
	TEST_ASSERT(c_isalnum('\t') == FALSE, "Tab is not alnum");
	TEST_ASSERT(c_isalnum('@') == FALSE, "Symbol '@' is not alnum");
	TEST_ASSERT(c_isalnum('#') == FALSE, "Symbol '#' is not alnum");
}

void test_c_isascii(void)
{
	TEST_START("c_isascii - ASCII character check");
	
	// Valid ASCII (0-127)
	TEST_ASSERT(c_isascii(0) == TRUE, "Null byte is ASCII");
	TEST_ASSERT(c_isascii(1) == TRUE, "Character 1 is ASCII");
	TEST_ASSERT(c_isascii(32) == TRUE, "Space (32) is ASCII");
	TEST_ASSERT(c_isascii('A') == TRUE, "Letter 'A' is ASCII");
	TEST_ASSERT(c_isascii('z') == TRUE, "Letter 'z' is ASCII");
	TEST_ASSERT(c_isascii('0') == TRUE, "Digit '0' is ASCII");
	TEST_ASSERT(c_isascii(127) == TRUE, "DEL (127) is ASCII");
	
	// Invalid ASCII (outside 0-127)
	TEST_ASSERT(c_isascii(128) == FALSE, "Character 128 is not ASCII");
	TEST_ASSERT(c_isascii(255) == FALSE, "Character 255 is not ASCII");
	TEST_ASSERT(c_isascii(-1) == FALSE, "Negative value is not ASCII");
	TEST_ASSERT(c_isascii(200) == FALSE, "Character 200 is not ASCII");
}

void test_c_isprint(void)
{
	TEST_START("c_isprint - printable character check");
	
	// Printable characters (32-126)
	TEST_ASSERT(c_isprint(' ') == TRUE, "Space is printable");
	TEST_ASSERT(c_isprint('!') == TRUE, "Character '!' is printable");
	TEST_ASSERT(c_isprint('A') == TRUE, "Letter 'A' is printable");
	TEST_ASSERT(c_isprint('z') == TRUE, "Letter 'z' is printable");
	TEST_ASSERT(c_isprint('0') == TRUE, "Digit '0' is printable");
	TEST_ASSERT(c_isprint('~') == TRUE, "Character '~' is printable");
	
	// Non-printable characters
	TEST_ASSERT(c_isprint('\0') == FALSE, "Null byte is not printable");
	TEST_ASSERT(c_isprint('\n') == FALSE, "Newline is not printable");
	TEST_ASSERT(c_isprint('\t') == FALSE, "Tab is not printable");
	TEST_ASSERT(c_isprint(31) == FALSE, "Character 31 is not printable");
	TEST_ASSERT(c_isprint(127) == FALSE, "DEL (127) is not printable");
	TEST_ASSERT(c_isprint(128) == FALSE, "Character 128 is not printable");
}

void test_c_isspace(void)
{
	TEST_START("c_isspace - whitespace character check");
	
	// Whitespace characters
	TEST_ASSERT(c_isspace(' ') == TRUE, "Space is whitespace");
	TEST_ASSERT(c_isspace('\t') == TRUE, "Tab is whitespace");
	TEST_ASSERT(c_isspace('\n') == TRUE, "Newline is whitespace");
	TEST_ASSERT(c_isspace('\v') == TRUE, "Vertical tab is whitespace");
	TEST_ASSERT(c_isspace('\f') == TRUE, "Form feed is whitespace");
	TEST_ASSERT(c_isspace('\r') == TRUE, "Carriage return is whitespace");
	
	// Non-whitespace characters
	TEST_ASSERT(c_isspace('a') == FALSE, "Letter 'a' is not whitespace");
	TEST_ASSERT(c_isspace('0') == FALSE, "Digit '0' is not whitespace");
	TEST_ASSERT(c_isspace('\0') == FALSE, "Null byte is not whitespace");
	TEST_ASSERT(c_isspace('!') == FALSE, "Punctuation is not whitespace");
}

// ============================================================================
// CHARACTER CONVERSION TESTS
// ============================================================================

void test_c_toupper(void)
{
	TEST_START("c_toupper - uppercase conversion");
	
	// Lowercase to uppercase
	TEST_ASSERT(c_toupper('a') == 'A', "Lowercase 'a' converts to 'A'");
	TEST_ASSERT(c_toupper('z') == 'Z', "Lowercase 'z' converts to 'Z'");
	TEST_ASSERT(c_toupper('m') == 'M', "Lowercase 'm' converts to 'M'");
	
	// Already uppercase (no change)
	TEST_ASSERT(c_toupper('A') == 'A', "Uppercase 'A' stays 'A'");
	TEST_ASSERT(c_toupper('Z') == 'Z', "Uppercase 'Z' stays 'Z'");
	
	// Non-alphabetic (no change)
	TEST_ASSERT(c_toupper('0') == '0', "Digit '0' unchanged");
	TEST_ASSERT(c_toupper('9') == '9', "Digit '9' unchanged");
	TEST_ASSERT(c_toupper(' ') == ' ', "Space unchanged");
	TEST_ASSERT(c_toupper('!') == '!', "Punctuation unchanged");
	TEST_ASSERT(c_toupper('\n') == '\n', "Newline unchanged");
	TEST_ASSERT(c_toupper('@') == '@', "Symbol '@' unchanged");
}

void test_c_tolower(void)
{
	TEST_START("c_tolower - lowercase conversion");
	
	// Uppercase to lowercase
	TEST_ASSERT(c_tolower('A') == 'a', "Uppercase 'A' converts to 'a'");
	TEST_ASSERT(c_tolower('Z') == 'z', "Uppercase 'Z' converts to 'z'");
	TEST_ASSERT(c_tolower('M') == 'm', "Uppercase 'M' converts to 'm'");
	
	// Already lowercase (no change)
	TEST_ASSERT(c_tolower('a') == 'a', "Lowercase 'a' stays 'a'");
	TEST_ASSERT(c_tolower('z') == 'z', "Lowercase 'z' stays 'z'");
	
	// Non-alphabetic (no change)
	TEST_ASSERT(c_tolower('0') == '0', "Digit '0' unchanged");
	TEST_ASSERT(c_tolower('9') == '9', "Digit '9' unchanged");
	TEST_ASSERT(c_tolower(' ') == ' ', "Space unchanged");
	TEST_ASSERT(c_tolower('!') == '!', "Punctuation unchanged");
	TEST_ASSERT(c_tolower('\n') == '\n', "Newline unchanged");
	TEST_ASSERT(c_tolower('[') == '[', "Symbol '[' unchanged");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_char_comprehensive_tests(void)
{	
	test_c_isalpha();
	test_c_isdigit();
	test_c_isalnum();
	test_c_isascii();
	test_c_isprint();
	test_c_isspace();
	test_c_toupper();
	test_c_tolower();
	
	TEST_SUMMARY();
}
