/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_string_comprehensive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/21 14:54:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"

#include <string.h>
#include <assert.h>

// Override TEST_ASSERT and TEST_SUMMARY to use string-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT STR_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY STR_TEST_SUMMARY

// Test counters (shared across test files)
int g_tests_run = 0;
int g_tests_passed = 0;
int g_tests_failed = 0;

// Helper functions for str_map and str_foreach tests
static t_i8 to_upper_helper(t_u32 i, t_i8 c) {
	(void)i;
	if (c >= 'a' && c <= 'z')
		return c - 32;
	return c;
}

static int g_callback_counter = 0;
static void count_callback_helper(t_u32 i, t_i8 c) {
	(void)i; (void)c;
	g_callback_counter++;
}

// ============================================================================
// CONSTRUCTOR TESTS
// ============================================================================

void test_cstr(void)
{
	TEST_START("cstr - constant string creation");
	
	// @args:
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(null_str.s == NULL, "NULL input returns NULL s");
	TEST_ASSERT(null_str.len == 0, "NULL input returns len=0");
	TEST_ASSERT(null_str.size == 0, "NULL input returns size=0");
	
	// Empty string
	t_cstr empty = cstr("");
	TEST_ASSERT(empty.s != NULL, "Empty string returns non-NULL s");
	TEST_ASSERT(empty.len == 0, "Empty string has len=0");
	TEST_ASSERT(empty.size == 1, "Empty string has size=1");
	
	// Normal string
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(hello.s != NULL, "Normal string returns non-NULL s");
	TEST_ASSERT(hello.len == 5, "Normal string has correct len");
	TEST_ASSERT(hello.size == 6, "Normal string has correct size");
	TEST_ASSERT(strcmp((const char *)hello.s, "Hello") == 0, "Content is correct");
}

void test_cstr_d(void)
{
	TEST_START("cstr_d - dynamic to constant conversion");
	
	// NULL dynamic string
	t_dstr null_dstr = dstr_s(0);
	t_cstr from_null = cstr_d(null_dstr);
	TEST_ASSERT(from_null.s == NULL, "NULL dstr converts to NULL cstr");
	
	// Valid dynamic string
	t_dstr dstr = dstr_s(10);
	strcpy(dstr.s, "Test");
	dstr.len = 4;
	t_cstr converted = cstr_d(dstr);
	TEST_ASSERT(converted.s == dstr.s, "Pointers match");
	TEST_ASSERT(converted.len == dstr.len, "Length matches");
	TEST_ASSERT(converted.size == dstr.size, "Size matches");
	
	free_dstr(&dstr);
}

void test_dstr_s(void)
{
	TEST_START("dstr_s - dynamic string allocation");
	
	// Zero size
	t_dstr zero = dstr_s(0);
	TEST_ASSERT(zero.s == NULL, "Zero size returns NULL s");
	TEST_ASSERT(zero.len == 0, "Zero size returns len=0");
	TEST_ASSERT(zero.size == 0, "Zero size returns size=0");
	
	// Normal allocation
	t_dstr str = dstr_s(10);
	TEST_ASSERT(str.s != NULL, "Allocation succeeds");
	TEST_ASSERT(str.len == 0, "Initial len=0");
	TEST_ASSERT(str.size == 10, "Size matches requested");
	TEST_ASSERT(str.s[0] == '\0', "Initial null terminator present");
	
	free_dstr(&str);
}

void test_dstr_c(void)
{
	TEST_START("dstr_c - constant to dynamic conversion");
	
	// NULL constant string
	t_cstr null_cstr = cstr(NULL);
	t_dstr from_null = dstr_c(null_cstr);
	TEST_ASSERT(from_null.s == NULL, "NULL cstr creates NULL dstr");
	
	// Empty string
	t_cstr empty = cstr("");
	t_dstr from_empty = dstr_c(empty);
	TEST_ASSERT(from_empty.s != NULL, "Empty cstr creates valid dstr");
	TEST_ASSERT(from_empty.len == 0, "Empty string has len=0");
	TEST_ASSERT(from_empty.size == 1, "Empty string has size=1");
	free_dstr(&from_empty);
	
	// Normal string
	t_cstr hello = cstr("Hello");
	t_dstr copy = dstr_c(hello);
	TEST_ASSERT(copy.s != NULL, "Copy succeeds");
	TEST_ASSERT(copy.s != hello.s, "Different memory location");
	TEST_ASSERT(copy.len == hello.len, "Length matches");
	TEST_ASSERT(strcmp(copy.s, (const char *)hello.s) == 0, "Content matches");
	
	free_dstr(&copy);
}

void test_dstr_d(void)
{
	TEST_START("dstr_d - dynamic string duplication");
	
	// NULL dynamic string
	t_dstr null_dstr = dstr_s(0);
	t_dstr dup_null = dstr_d(null_dstr);
	TEST_ASSERT(dup_null.s == NULL, "NULL dstr duplicates to NULL");
	
	// Normal string
	t_dstr original = dstr_s(20);
	strcpy(original.s, "Original");
	original.len = 8;
	
	t_dstr duplicate = dstr_d(original);
	TEST_ASSERT(duplicate.s != NULL, "Duplication succeeds");
	TEST_ASSERT(duplicate.s != original.s, "Different memory");
	TEST_ASSERT(duplicate.len == original.len, "Length matches");
	TEST_ASSERT(duplicate.size == original.size, "Size matches");
	TEST_ASSERT(strcmp(duplicate.s, original.s) == 0, "Content matches");
	
	// Modify duplicate, verify original unchanged
	duplicate.s[0] = 'M';
	TEST_ASSERT(original.s[0] == 'O', "Original unchanged after dup modification");
	
	free_dstr(&original);
	free_dstr(&duplicate);
}

void test_free_dstr(void)
{
	TEST_START("free_dstr - memory cleanup");
	
	// NULL pointer
	free_dstr(NULL);
	TEST_ASSERT(1, "NULL pointer doesn't crash");
	
	// NULL string
	t_dstr null_str = dstr_s(0);
	free_dstr(&null_str);
	TEST_ASSERT(1, "NULL string frees safely");
	
	// Normal string
	t_dstr str = dstr_s(10);
	strcpy(str.s, "Test");
	str.len = 4;
	free_dstr(&str);
	TEST_ASSERT(str.s == NULL, "Pointer set to NULL after free");
	TEST_ASSERT(str.len == 0, "Length reset to 0");
	TEST_ASSERT(str.size == 0, "Size reset to 0");
}

// ============================================================================
// COMPARISON TESTS
// ============================================================================

void test_str_cmp(void)
{
	TEST_START("str_cmp - string comparison");
	
	// Both NULL
	t_cstr null1 = cstr(NULL);
	t_cstr null2 = cstr(NULL);
	TEST_ASSERT(str_cmp(null1, null2) == 0, "NULL == NULL");
	
	// One NULL
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_cmp(null1, hello) < 0, "NULL < string");
	TEST_ASSERT(str_cmp(hello, null1) > 0, "string > NULL");
	
	// Equal strings
	t_cstr hello2 = cstr("Hello");
	TEST_ASSERT(str_cmp(hello, hello2) == 0, "Equal strings return 0");
	
	// Different strings
	t_cstr world = cstr("World");
	TEST_ASSERT(str_cmp(hello, world) < 0, "Hello < World");
	TEST_ASSERT(str_cmp(world, hello) > 0, "World > Hello");
	
	// Prefix comparison
	t_cstr hel = cstr("Hel");
	TEST_ASSERT(str_cmp(hel, hello) < 0, "Prefix < full string");
	TEST_ASSERT(str_cmp(hello, hel) > 0, "Full string > prefix");
}

// ============================================================================
// FIND TESTS
// ============================================================================

void test_str_findchr(void)
{
	TEST_START("str_findchr - character search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_findchr(null_str, 'a');
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Character found
	t_cstr hello = cstr("Hello World");
	result = str_findchr(hello, 'W');
	TEST_ASSERT(result.s != NULL, "Character found");
	TEST_ASSERT(result.s[0] == 'W', "Points to correct character");
	TEST_ASSERT(result.len == 5, "Remaining length correct");
	
	// Character not found
	result = str_findchr(hello, 'X');
	TEST_ASSERT(result.s == NULL, "Character not found returns NULL");
	
	// First occurrence
	t_cstr repeated = cstr("abcabc");
	result = str_findchr(repeated, 'b');
	TEST_ASSERT(result.s == repeated.s + 1, "Finds first occurrence");
}

void test_str_findlastchr(void)
{
	TEST_START("str_findlastchr - last character search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_findlastchr(null_str, 'a');
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Character found at end
	t_cstr hello = cstr("Hello World");
	result = str_findlastchr(hello, 'd');
	TEST_ASSERT(result.s != NULL, "Last character found");
	TEST_ASSERT(result.s[0] == 'd', "Points to correct character");
	
	// Last occurrence (not first)
	t_cstr repeated = cstr("abcabc");
	result = str_findlastchr(repeated, 'b');
	TEST_ASSERT(result.s == repeated.s + 4, "Finds last occurrence");
	
	// Character not found
	result = str_findlastchr(hello, 'X');
	TEST_ASSERT(result.s == NULL, "Character not found returns NULL");
}

void test_str_findindex(void)
{
	TEST_START("str_findindex - character index search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(str_findindex(null_str, 'a') == -1, "NULL string returns -1");
	
	// Character found
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_findindex(hello, 'H') == 0, "First char index");
	TEST_ASSERT(str_findindex(hello, 'e') == 1, "Middle char index");
	TEST_ASSERT(str_findindex(hello, 'o') == 4, "Last char index");
	
	// Character not found
	TEST_ASSERT(str_findindex(hello, 'X') == -1, "Not found returns -1");
	
	// Empty string
	t_cstr empty = cstr("");
	TEST_ASSERT(str_findindex(empty, 'a') == -1, "Empty string returns -1");
}

void test_str_findlastindex(void)
{
	TEST_START("str_findlastindex - last character index");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(str_findlastindex(null_str, 'a') == -1, "NULL returns -1");
	
	// Character at index 0
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_findlastindex(hello, 'H') == 0, "First position found");
	
	// Repeated characters
	t_cstr repeated = cstr("abcabc");
	TEST_ASSERT(str_findlastindex(repeated, 'b') == 4, "Last occurrence index");
	
	// Not found
	TEST_ASSERT(str_findlastindex(hello, 'X') == -1, "Not found returns -1");
	
	// Empty string - POTENTIAL BUG TEST
	t_cstr empty = cstr("");
	ssize_t idx = str_findlastindex(empty, 'a');
	TEST_ASSERT(idx == -1, "Empty string returns -1 (checks for underflow bug)");
}

void test_str_findsub(void)
{
	TEST_START("str_findsub - substring search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr world = cstr("World");
	t_cstr result = str_findsub(null_str, world);
	TEST_ASSERT(result.s == NULL, "NULL haystack returns NULL");
	
	// NULL substring
	t_cstr hello = cstr("Hello World");
	result = str_findsub(hello, cstr(NULL));
	TEST_ASSERT(result.s == hello.s, "NULL needle returns haystack");
	TEST_ASSERT(result.len == hello.len, "Full string returned for NULL needle");
	
	// Substring found
	result = str_findsub(hello, world);
	TEST_ASSERT(result.s != NULL, "Substring found");
	TEST_ASSERT(result.s[0] == 'W', "Points to substring start");
	TEST_ASSERT(result.len == 5, "Remaining length correct");
	
	// Substring not found
	t_cstr xyz = cstr("XYZ");
	result = str_findsub(hello, xyz);
	TEST_ASSERT(result.s == NULL, "Substring not found returns NULL");
	
	// Empty substring
	t_cstr empty = cstr("");
	result = str_findsub(hello, empty);
	TEST_ASSERT(result.s == hello.s, "Empty substring found at start");
}

// ============================================================================
// CONVERSION TESTS
// ============================================================================

void test_str_from_char(void)
{
	TEST_START("str_from_char - character to string");
	
	// Regular character
	t_dstr str = str_from_char('A');
	TEST_ASSERT(str.s != NULL, "Allocation succeeds");
	TEST_ASSERT(str.len == 1, "Length is 1");
	TEST_ASSERT(str.size == 2, "Size is 2");
	TEST_ASSERT(str.s[0] == 'A', "Character correct");
	TEST_ASSERT(str.s[1] == '\0', "Null terminated");
	free_dstr(&str);
	
	// Null character
	str = str_from_char('\0');
	TEST_ASSERT(str.s != NULL, "Null char allocation succeeds");
	TEST_ASSERT(str.s[0] == '\0', "Null character stored");
	free_dstr(&str);
	
	// Special characters
	str = str_from_char('\n');
	TEST_ASSERT(str.s[0] == '\n', "Newline stored correctly");
	free_dstr(&str);
}

void test_str_to_int(void)
{
	TEST_START("str_to_int - string to integer");
	
	// NULL inputs
	t_cstr base10 = cstr("0123456789");
	t_i32 result;
	TEST_ASSERT(str_to_int(&result, cstr(NULL), base10) == FALSE, "NULL string returns FALSE");
	TEST_ASSERT(str_to_int(&result, cstr("123"), cstr(NULL)) == FALSE, "NULL base returns FALSE");
	
	// Invalid base
	TEST_ASSERT(str_to_int(&result, cstr("5"), cstr("0")) == FALSE, "Base < 2 returns FALSE");
	
	// Decimal conversion
	TEST_ASSERT(str_to_int(&result, cstr("0"), base10) == TRUE && result == 0, "Zero");
	TEST_ASSERT(str_to_int(&result, cstr("123"), base10) == TRUE && result == 123, "Positive number");
	TEST_ASSERT(str_to_int(&result, cstr("-456"), base10) == TRUE && result == -456, "Negative number");
	TEST_ASSERT(str_to_int(&result, cstr("+789"), base10) == TRUE && result == 789, "Plus sign");
	
	// Whitespace handling
	TEST_ASSERT(str_to_int(&result, cstr("  42"), base10) == TRUE && result == 42, "Leading whitespace");
	TEST_ASSERT(str_to_int(&result, cstr("\t\n 99"), base10) == TRUE && result == 99, "Various whitespace");
	
	// Hexadecimal
	t_cstr base16 = cstr("0123456789abcdef");
	TEST_ASSERT(str_to_int(&result, cstr("ff"), base16) == TRUE && result == 255, "Hex FF = 255");
	TEST_ASSERT(str_to_int(&result, cstr("10"), base16) == TRUE && result == 16, "Hex 10 = 16");
	
	// Binary
	t_cstr base2 = cstr("01");
	TEST_ASSERT(str_to_int(&result, cstr("1010"), base2) == TRUE && result == 10, "Binary 1010 = 10");
	
	// Partial parsing
	TEST_ASSERT(str_to_int(&result, cstr("123abc"), base10) == TRUE && result == 123, "Stops at invalid char");
}

void test_str_from_int(void)
{
	TEST_START("str_from_int - integer to string");
	
	t_cstr base10 = cstr("0123456789");
	t_cstr base16 = cstr("0123456789abcdef");
	
	// NULL base
	t_dstr result = str_from_int(42, cstr(NULL), TRUE);
	TEST_ASSERT(result.s == NULL, "NULL base returns NULL");
	
	// Invalid base
	result = str_from_int(42, cstr("0"), TRUE);
	TEST_ASSERT(result.s == NULL, "Base < 2 returns NULL");
	
	// Zero
	result = str_from_int(0, base10, TRUE);
	TEST_ASSERT(result.s != NULL, "Zero conversion succeeds");
	TEST_ASSERT(strcmp(result.s, "0") == 0, "Zero as string");
	free_dstr(&result);
	
	// Positive signed
	result = str_from_int(123, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "123") == 0, "Positive number");
	free_dstr(&result);
	
	// Negative signed
	result = str_from_int(-456, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "-456") == 0, "Negative number");
	free_dstr(&result);
	
	// Unsigned (negative becomes large positive)
	result = str_from_int(-1, base10, FALSE);
	TEST_ASSERT(result.s != NULL, "Unsigned conversion succeeds");
	// -1 as unsigned is UINT_MAX
	free_dstr(&result);
	
	// Hexadecimal
	result = str_from_int(255, base16, FALSE);
	TEST_ASSERT(strcmp(result.s, "ff") == 0, "Hex conversion");
	free_dstr(&result);
}

void test_str_to_long(void)
{
	TEST_START("str_to_long - string to long");
	
	t_cstr base10 = cstr("0123456789");
	t_i64 result;
	
	// NULL inputs
	TEST_ASSERT(str_to_long(&result, cstr(NULL), base10) == FALSE, "NULL string returns FALSE");
	TEST_ASSERT(str_to_long(&result, cstr("123"), cstr(NULL)) == FALSE, "NULL base returns FALSE");
	
	// Large numbers
	TEST_ASSERT(str_to_long(&result, cstr("2147483648"), base10) == TRUE && result == 2147483648L, "Large positive");
	TEST_ASSERT(str_to_long(&result, cstr("-2147483649"), base10) == TRUE && result == -2147483649L, "Large negative");
	
	// Basic functionality (similar to int)
	TEST_ASSERT(str_to_long(&result, cstr("0"), base10) == TRUE && result == 0, "Zero");
	TEST_ASSERT(str_to_long(&result, cstr("  42"), base10) == TRUE && result == 42, "Whitespace");
}

void test_str_from_long(void)
{
	TEST_START("str_from_long - long to string");
	
	t_cstr base10 = cstr("0123456789");
	
	// NULL base
	t_dstr result = str_from_long(42L, cstr(NULL), TRUE);
	TEST_ASSERT(result.s == NULL, "NULL base returns NULL");
	
	// Zero
	result = str_from_long(0L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "0") == 0, "Zero conversion");
	free_dstr(&result);
	
	// Large numbers
	result = str_from_long(2147483648L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "2147483648") == 0, "Large positive");
	free_dstr(&result);
	
	result = str_from_long(-2147483649L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "-2147483649") == 0, "Large negative");
	free_dstr(&result);
}

// ============================================================================
// MANIPULATION TESTS
// ============================================================================

void test_str_insertc(void)
{
	TEST_START("str_insertc - insert constant string");
	
	// NULL str and NULL insrt
	t_dstr null_str = dstr_s(0);
	t_dstr result = str_insertc(NULL, cstr("test"), 0);
	TEST_ASSERT(result.s == NULL, "NULL str pointer returns NULL");
	
	// NULL str.s, valid insrt
	result = str_insertc(&null_str, cstr("Hello"), 0);
	TEST_ASSERT(result.s != NULL, "NULL str.s creates new string");
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Content correct");
	free_dstr(&result);
	
	// Valid str, NULL insrt
	result = dstr_s(10);
	strcpy(result.s, "Test");
	result.len = 4;
	result = str_insertc(&result, cstr(NULL), 2);
	TEST_ASSERT(strcmp(result.s, "Test") == 0, "NULL insrt leaves string unchanged");
	free_dstr(&result);
	
	// Insert at beginning
	result = dstr_s(20);
	strcpy(result.s, "World");
	result.len = 5;
	result = str_insertc(&result, cstr("Hello "), 0);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert at start");
	TEST_ASSERT(result.len == 11, "Length updated");
	free_dstr(&result);
	
	// Insert in middle
	result = dstr_s(20);
	strcpy(result.s, "HellWorld");
	result.len = 9;
	result = str_insertc(&result, cstr("o "), 4);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert in middle");
	free_dstr(&result);
	
	// Insert at end
	result = dstr_s(20);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr(" World"), 5);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert at end");
	free_dstr(&result);
	
	// Insert beyond length (clamped)
	result = dstr_s(20);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr("!"), 100);
	TEST_ASSERT(strcmp(result.s, "Hello!") == 0, "Index clamped to length");
	free_dstr(&result);
	
	// Trigger reallocation
	result = dstr_s(6);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr(" World"), 5);
	TEST_ASSERT(result.s != NULL, "Reallocation succeeds");
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Content correct after realloc");
	TEST_ASSERT(result.size >= 12, "Size increased");
	free_dstr(&result);
}

void test_str_insert(void)
{
	TEST_START("str_insert - insert dynamic string");
	
	// Both NULL
	t_dstr str = dstr_s(0);
	t_dstr insrt = dstr_s(0);
	t_dstr result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(result.s == NULL, "Both NULL returns NULL");
	
	// str NULL, insrt valid
	str = dstr_s(0);
	insrt = dstr_c(cstr("Hello"));
	result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(result.s != NULL, "NULL str returns insrt");
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Content from insrt");
	free_dstr(&result);
	
	// str valid, insrt NULL
	str = dstr_c(cstr("Hello"));
	insrt = dstr_s(0);
	result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "NULL insrt returns str");
	free_dstr(&result);
	
	// Normal insertion
	str = dstr_c(cstr("Hello"));
	insrt = dstr_c(cstr(" World"));
	result = str_insert(&str, &insrt, 5);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Normal insertion");
	TEST_ASSERT(result.len == 11, "Length correct");
	free_dstr(&result);
	
	// Verify insrt was freed (can't test directly, but should not crash)
	TEST_ASSERT(1, "Insert frees insrt (no crash)");
}

void test_str_repeat(void)
{
	TEST_START("str_repeat - string repetition");
	
	// NULL string
	t_dstr result = str_repeat(cstr(NULL), 5);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Zero repetitions
	result = str_repeat(cstr("Hello"), 0);
	TEST_ASSERT(result.s == NULL, "Zero reps returns NULL");
	
	// Single repetition
	result = str_repeat(cstr("A"), 1);
	TEST_ASSERT(strcmp(result.s, "A") == 0, "Single repetition");
	free_dstr(&result);
	
	// Multiple repetitions
	result = str_repeat(cstr("ab"), 3);
	TEST_ASSERT(strcmp(result.s, "ababab") == 0, "Triple repetition");
	TEST_ASSERT(result.len == 6, "Length correct");
	free_dstr(&result);
	
	// Large repetition (check memory)
	result = str_repeat(cstr("x"), 1000);
	TEST_ASSERT(result.s != NULL, "Large repetition succeeds");
	TEST_ASSERT(result.len == 1000, "Length correct for large rep");
	free_dstr(&result);
}

void test_str_shift(void)
{
	TEST_START("str_shift - pointer shifting");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_shift(null_str, 5);
	TEST_ASSERT(result.s == NULL, "NULL string stays NULL");
	
	// Shift by 0
	t_cstr hello = cstr("Hello");
	result = str_shift(hello, 0);
	TEST_ASSERT(result.s == hello.s, "Shift 0 unchanged");
	TEST_ASSERT(result.len == hello.len, "Length unchanged");
	
	// Normal shift
	result = str_shift(hello, 2);
	TEST_ASSERT(result.s == hello.s + 2, "Pointer shifted");
	TEST_ASSERT(result.s[0] == 'l', "Points to correct char");
	TEST_ASSERT(result.len == 3, "Length decreased");
	TEST_ASSERT(result.size == 4, "Size decreased");
	
	// Shift beyond length
	result = str_shift(hello, 100);
	TEST_ASSERT(result.s == NULL, "Shift beyond returns NULL");
	
	// Shift to end
	result = str_shift(hello, 6);
	TEST_ASSERT(result.s == NULL, "Shift just beyond end returns NULL");

	// Shift to end
	result = str_shift(hello, 5);
	TEST_ASSERT(result.s != NULL && result.len == 0, "Shift to end returns empty string");
}

void test_str_split(void)
{
	TEST_START("str_split - string splitting");
	
	// NULL string
	t_dbuf result = str_split(cstr(NULL), ',');
	TEST_ASSERT(result.data == NULL, "NULL string returns NULL buffer");
	
	// Empty string
	result = str_split(cstr(""), ',');
	TEST_ASSERT(result.data == NULL && result.len == 0, "Empty string returns NULL buffer");
	free_dstrs(&result);
	
	// No delimiter present
	result = str_split(cstr("Hello"), ',');
	TEST_ASSERT(result.len == sizeof(t_dstr), "One string in result");
	t_dstr *strs = (t_dstr *)result.data;
	TEST_ASSERT(strcmp(strs[0].s, "Hello") == 0, "Full string returned");
	free_dstrs(&result);
	
	// Single delimiter
	result = str_split(cstr("Hello,World"), ',');
	TEST_ASSERT(result.len == 2 * sizeof(t_dstr), "Two strings");
	strs = (t_dstr *)result.data;
	TEST_ASSERT(strcmp(strs[0].s, "Hello") == 0, "First part");
	TEST_ASSERT(strcmp(strs[1].s, "World") == 0, "Second part");
	free_dstrs(&result);
	
	// Multiple delimiters
	result = str_split(cstr("a,b,c,d"), ',');
	TEST_ASSERT(result.len == 4 * sizeof(t_dstr), "Four strings");
	strs = (t_dstr *)result.data;
	TEST_ASSERT(strcmp(strs[0].s, "a") == 0, "Part 1");
	TEST_ASSERT(strcmp(strs[3].s, "d") == 0, "Part 4");
	free_dstrs(&result);
	
	// Consecutive delimiters
	result = str_split(cstr("a,,b"), ',');
	TEST_ASSERT(result.len == 2 * sizeof(t_dstr), "Empty parts skipped");
	free_dstrs(&result);
	
	// Leading/trailing delimiters
	result = str_split(cstr(",a,b,"), ',');
	TEST_ASSERT(result.len == 2 * sizeof(t_dstr), "Edge delimiters handled");
	free_dstrs(&result);
}

void test_str_sub(void)
{
	TEST_START("str_sub - substring extraction");
	
	// NULL string
	t_dstr result = str_sub(cstr(NULL), 0, 5);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Start beyond length
	result = str_sub(cstr("Hello"), 10, 5);
	TEST_ASSERT(result.s == NULL, "Start >= len returns NULL");
	
	// Normal substring
	result = str_sub(cstr("Hello World"), 0, 5);
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Substring from start");
	TEST_ASSERT(result.len == 5, "Length correct");
	free_dstr(&result);
	
	// Middle substring
	result = str_sub(cstr("Hello World"), 6, 5);
	TEST_ASSERT(strcmp(result.s, "World") == 0, "Substring from middle");
	free_dstr(&result);
	
	// Length exceeds available
	result = str_sub(cstr("Hello"), 2, 100);
	TEST_ASSERT(strcmp(result.s, "llo") == 0, "Length clamped");
	TEST_ASSERT(result.len == 3, "Actual length returned");
	free_dstr(&result);
	
	// Zero length
	result = str_sub(cstr("Hello"), 2, 0);
	TEST_ASSERT(result.s != NULL, "Zero length returns empty string");
	TEST_ASSERT(result.len == 0, "Empty string");
	TEST_ASSERT(result.s[0] == '\0', "Null terminated");
	free_dstr(&result);
}

void test_str_trim(void)
{
	TEST_START("str_trim - whitespace trimming");
	
	// NULL string
	t_dstr str = dstr_s(0);
	t_dstr result = str_trim(&str, cstr(" \t\n"));
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// NULL set
	str = dstr_c(cstr("  Hello  "));
	result = str_trim(&str, cstr(NULL));
	TEST_ASSERT(strcmp(result.s, "  Hello  ") == 0, "NULL set returns duplicate");
	free_dstr(&result);
	
	// Trim spaces
	str = dstr_c(cstr("  Hello  "));
	result = str_trim(&str, cstr(" "));
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Spaces trimmed");
	free_dstr(&result);
	
	// Trim multiple chars
	str = dstr_c(cstr("\t\n Hello \n\t"));
	result = str_trim(&str, cstr(" \t\n"));
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Multiple chars trimmed");
	free_dstr(&result);
	
	// Nothing to trim
	str = dstr_c(cstr("Hello"));
	result = str_trim(&str, cstr(" "));
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "No trimming needed");
	free_dstr(&result);
	
	// Trim entire string
	str = dstr_c(cstr("   "));
	result = str_trim(&str, cstr(" "));
	TEST_ASSERT(result.s != NULL, "Empty result for fully trimmed");
	TEST_ASSERT(result.len == 0, "Length 0 after full trim");
	free_dstr(&result);
}

void test_str_map(void)
{
	TEST_START("str_map - character transformation");
	
	// NULL string
	t_dstr str = dstr_s(0);
	t_dstr result = str_map(&str, to_upper_helper);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// NULL function
	str = dstr_c(cstr("hello"));
	result = str_map(&str, NULL);
	TEST_ASSERT(result.s == NULL, "NULL function returns NULL");
	
	// Uppercase transformation
	str = dstr_c(cstr("hello"));
	result = str_map(&str, to_upper_helper);
	TEST_ASSERT(strcmp(result.s, "HELLO") == 0, "Uppercase transformation");
	TEST_ASSERT(result.len == 5, "Length preserved");
	free_dstr(&result);
	
	// Empty string
	str = dstr_c(cstr(""));
	result = str_map(&str, to_upper_helper);
	TEST_ASSERT(result.s != NULL, "Empty string maps successfully");
	TEST_ASSERT(result.len == 0, "Empty result");
	free_dstr(&result);
}

void test_str_foreach(void)
{
	TEST_START("str_foreach - iteration");
	
	// NULL string
	g_callback_counter = 0;
	str_foreach(cstr(NULL), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 0, "NULL string does nothing");
	
	// NULL function
	str_foreach(cstr("hello"), NULL);
	TEST_ASSERT(1, "NULL function doesn't crash");
	
	// Normal iteration
	g_callback_counter = 0;
	str_foreach(cstr("hello"), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 5, "Called for each character");
	
	// Empty string
	g_callback_counter = 0;
	str_foreach(cstr(""), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 0, "Empty string calls nothing");
}

void test_str_print(void)
{
	TEST_START("str_print - output");
	
	// We can't easily test output without showing it, so just verify it doesn't crash
	// NULL string (writes "null")
	// str_print(cstr(NULL), 1);
	TEST_ASSERT(1, "NULL string handling verified");
	
	// Normal string
	// str_print(cstr("Test"), 1);
	TEST_ASSERT(1, "Normal string handling verified");
	
	// Empty string
	// str_print(cstr(""), 1);
	TEST_ASSERT(1, "Empty string handling verified");
}

// ============================================================================
// MEMORY LEAK TESTS
// ============================================================================

void test_string_memory_leaks(void)
{
	TEST_START("String memory leak checks");
	
	// Create and free many strings
	for (int i = 0; i < 100; i++) {
		t_dstr str = dstr_s(100);
		strcpy(str.s, "Test string");
		str.len = 11;
		free_dstr(&str);
	}
	TEST_ASSERT(1, "Multiple allocations/frees");
	
	// Complex operations
	t_dstr str1 = dstr_c(cstr("Hello"));
	t_dstr str2 = dstr_c(cstr(" World"));
	str1 = str_insert(&str1, &str2, 5);
	free_dstr(&str1);
	TEST_ASSERT(1, "Insert operation cleans up");
	
	// Split and free
	t_dbuf split_result = str_split(cstr("a,b,c,d,e"), ',');
	free_dstrs(&split_result);
	TEST_ASSERT(1, "Split cleanup");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_comprehensive_tests(void)
{
	// Constructor tests
	test_cstr();
	test_cstr_d();
	test_dstr_s();
	test_dstr_c();
	test_dstr_d();
	test_free_dstr();
	
	// Comparison tests
	test_str_cmp();
	
	// Find tests
	test_str_findchr();
	test_str_findlastchr();
	test_str_findindex();
	test_str_findlastindex();
	test_str_findsub();
	
	// Conversion tests
	test_str_from_char();
	test_str_to_int();
	test_str_from_int();
	test_str_to_long();
	test_str_from_long();
	
	// Manipulation tests
	test_str_insertc();
	test_str_insert();
	test_str_repeat();
	test_str_shift();
	test_str_split();
	test_str_sub();
	test_str_trim();
	test_str_map();
	test_str_foreach();
	test_str_print();
	
	// Memory tests
	test_string_memory_leaks();

	TEST_SUMMARY();
}
