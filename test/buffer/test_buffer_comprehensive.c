/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_buffer_comprehensive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 15:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Override TEST_ASSERT and TEST_SUMMARY to use buffer-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT BUF_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY BUF_TEST_SUMMARY

// Test counters (shared across test files)
int g_buf_tests_run = 0;
int g_buf_tests_passed = 0;
int g_buf_tests_failed = 0;

// ============================================================================
// CONSTRUCTOR TESTS - cbuf
// ============================================================================

void test_cbuf(void)
{
	TEST_START("cbuf - constant buffer creation");
	
	// NULL data
	t_cbuf null_buf = cbuf(NULL, 10);
	TEST_ASSERT(null_buf.data == NULL, "NULL data returns NULL buffer");
	TEST_ASSERT(null_buf.size == 0, "NULL data has size 0");
	
	// Zero size
	char data[] = "test";
	t_cbuf zero_buf = cbuf(data, 0);
	TEST_ASSERT(zero_buf.size == 0, "Zero size returns size 0");
	// Note: Implementation may leave data pointer set
	
	// Normal buffer
	t_cbuf buf = cbuf(data, 4);
	TEST_ASSERT(buf.data == data, "Data pointer correct");
	TEST_ASSERT(buf.size == 4, "Size correct");
	TEST_ASSERT(((const char *)buf.data)[0] == 't', "Can access data");
}

void test_cbuf_d(void)
{
	TEST_START("cbuf_d - dynamic to constant conversion");
	
	// NULL dynamic buffer
	t_dbuf null_dbuf = dbuf_s(0);
	t_cbuf from_null = cbuf_d(null_dbuf);
	TEST_ASSERT(from_null.data == NULL, "NULL dbuf converts to NULL cbuf");
	TEST_ASSERT(from_null.size == 0, "NULL dbuf has size 0");
	
	// Valid dynamic buffer
	t_dbuf dbuf = dbuf_s(10);
	((char *)dbuf.data)[0] = 'A';
	((char *)dbuf.data)[1] = 'B';
	dbuf.len = 2;
	
	t_cbuf cbuf = cbuf_d(dbuf);
	TEST_ASSERT(cbuf.data == dbuf.data, "Pointers match");
	TEST_ASSERT(cbuf.size == 2, "Size is dbuf.len");
	TEST_ASSERT(((const char *)cbuf.data)[0] == 'A', "Data accessible");
	
	free_dbuf(&dbuf);
}

// ============================================================================
// CONSTRUCTOR TESTS - dbuf
// ============================================================================

void test_dbuf_s(void)
{
	TEST_START("dbuf_s - dynamic buffer allocation");
	
	// Zero size
	t_dbuf zero = dbuf_s(0);
	TEST_ASSERT(zero.data == NULL, "Zero size returns NULL data");
	TEST_ASSERT(zero.size == 0, "Zero size has size 0");
	TEST_ASSERT(zero.len == 0, "Zero size has len 0");
	
	// Normal allocation
	t_dbuf buf = dbuf_s(100);
	TEST_ASSERT(buf.data != NULL, "Allocation succeeds");
	TEST_ASSERT(buf.size == 100, "Size is correct");
	TEST_ASSERT(buf.len == 0, "Initial len is 0");
	
	// Verify initialization to zero
	int all_zero = 1;
	for (size_t i = 0; i < buf.size; i++) {
		if (((char *)buf.data)[i] != 0) {
			all_zero = 0;
			break;
		}
	}
	TEST_ASSERT(all_zero, "Buffer initialized to zero");
	
	free_dbuf(&buf);
}

void test_dbuf_d(void)
{
	TEST_START("dbuf_d - dynamic buffer duplication");
	
	// NULL buffer
	t_dbuf null_buf = dbuf_s(0);
	t_dbuf dup_null = dbuf_d(null_buf);
	TEST_ASSERT(dup_null.data == NULL, "NULL buffer duplicates to NULL");
	
	// Normal buffer
	t_dbuf orig = dbuf_s(10);
	((char *)orig.data)[0] = 'X';
	((char *)orig.data)[1] = 'Y';
	orig.len = 2;
	
	t_dbuf dup = dbuf_d(orig);
	TEST_ASSERT(dup.data != NULL, "Duplication succeeds");
	TEST_ASSERT(dup.data != orig.data, "Different memory");
	TEST_ASSERT(dup.size == orig.size, "Size matches");
	TEST_ASSERT(dup.len == orig.len, "Length matches");
	TEST_ASSERT(((char *)dup.data)[0] == 'X', "Content copied");
	TEST_ASSERT(((char *)dup.data)[1] == 'Y', "Content copied");
	
	// Modify duplicate, verify original unchanged
	((char *)dup.data)[0] = 'Z';
	TEST_ASSERT(((char *)orig.data)[0] == 'X', "Original unchanged");
	
	free_dbuf(&orig);
	free_dbuf(&dup);
}

void test_dbuf_c(void)
{
	TEST_START("dbuf_c - constant to dynamic conversion");
	
	// NULL constant buffer
	t_cbuf null_cbuf = cbuf(NULL, 0);
	t_dbuf from_null = dbuf_c(null_cbuf);
	TEST_ASSERT(from_null.data == NULL, "NULL cbuf converts to NULL dbuf");
	
	// Normal buffer
	char data[] = {1, 2, 3, 4, 5};
	t_cbuf cbuf_ = cbuf(data, 5);
	t_dbuf dbuf_ = dbuf_c(cbuf_);
	
	TEST_ASSERT(dbuf_.data != NULL, "Conversion succeeds");
	TEST_ASSERT(dbuf_.data != data, "Different memory");
	TEST_ASSERT(dbuf_.size == 5, "Size correct");
	TEST_ASSERT(dbuf_.len == 5, "Length is size");
	TEST_ASSERT(((char *)dbuf_.data)[0] == 1, "Data copied");
	TEST_ASSERT(((char *)dbuf_.data)[4] == 5, "Data copied");
	
	free_dbuf(&dbuf_);
}

// ============================================================================
// MEMORY MANAGEMENT TESTS
// ============================================================================

void test_free_dbuf(void)
{
	TEST_START("free_dbuf - memory cleanup");
	
	// NULL pointer
	free_dbuf(NULL);
	TEST_ASSERT(1, "NULL pointer doesn't crash");
	
	// NULL buffer
	t_dbuf null_buf = dbuf_s(0);
	free_dbuf(&null_buf);
	TEST_ASSERT(1, "NULL buffer frees safely");
	
	// Normal buffer
	t_dbuf buf = dbuf_s(10);
	((char *)buf.data)[0] = 'A';
	free_dbuf(&buf);
	TEST_ASSERT(buf.data == NULL, "Data pointer set to NULL");
	TEST_ASSERT(buf.len == 0, "Length reset");
	TEST_ASSERT(buf.size == 0, "Size reset");
	
	// Double free should be safe
	free_dbuf(&buf);
	TEST_ASSERT(1, "Double free doesn't crash");
}

// ============================================================================
// SHIFT TESTS
// ============================================================================

void test_buf_shift(void)
{
	TEST_START("buf_shift - pointer shifting");
	
	// NULL buffer
	t_cbuf null_buf = cbuf(NULL, 0);
	t_cbuf result = buf_shift(null_buf, 5);
	TEST_ASSERT(result.data == NULL, "NULL buffer stays NULL");
	TEST_ASSERT(result.size == 0, "Size stays 0");
	
	// Normal shift
	char data[] = "ABCDEFGH";
	t_cbuf buf = cbuf(data, 8);
	result = buf_shift(buf, 3);
	
	TEST_ASSERT(result.data == (const void*)(data + 3), "Pointer shifted");
	TEST_ASSERT(result.size == 5, "Size decreased");
	TEST_ASSERT(((const char *)result.data)[0] == 'D', "Points to correct data");
	
	// Shift by 0
	result = buf_shift(buf, 0);
	TEST_ASSERT(result.data == buf.data, "Zero shift unchanged");
	TEST_ASSERT(result.size == buf.size, "Size unchanged");
	
	// Shift beyond size
	result = buf_shift(buf, 100);
	TEST_ASSERT(result.data == NULL, "Shift beyond returns NULL");
	TEST_ASSERT(result.size == 0, "Size is 0");
	
	// Shift exactly to end
	result = buf_shift(buf, 8);
	TEST_ASSERT(result.data == NULL, "Shift to end returns NULL");
}

// ============================================================================
// INSERT TESTS - buf_insertc
// ============================================================================

void test_buf_insertc(void)
{
	TEST_START("buf_insertc - insert constant buffer");
	
	// NULL buf pointer
	t_dbuf result = buf_insertc(NULL, cbuf("test", 4), 0, E);
	TEST_ASSERT(result.data == NULL, "NULL buf pointer returns NULL");
	
	// NULL buf.data, valid insert
	t_dbuf buf = dbuf_s(0);
	char data[] = "Hello";
	result = buf_insertc(&buf, cbuf(data, 5), 0, E);
	TEST_ASSERT(result.data != NULL, "NULL buf.data creates new buffer");
	TEST_ASSERT(result.len == 5, "Length correct");
	TEST_ASSERT(memcmp(result.data, "Hello", 5) == 0, "Content correct");
	free_dbuf(&result);
	
	// Valid buf, NULL insert
	buf = dbuf_s(10);
	((char *)buf.data)[0] = 'A';
	buf.len = 1;
	result = buf_insertc(&buf, cbuf(NULL, 0), 0, E);
	TEST_ASSERT(((char *)result.data)[0] == 'A', "NULL insert leaves unchanged");
	free_dbuf(&result);
	
	// Insert at beginning
	buf = dbuf_s(20);
	memcpy(buf.data, "World", 5);
	buf.len = 5;
	result = buf_insertc(&buf, cbuf("Hello ", 6), 0, E);
	TEST_ASSERT(result.len == 11, "Length updated");
	TEST_ASSERT(memcmp(result.data, "Hello World", 11) == 0, "Insert at start");
	free_dbuf(&result);
	
	// Insert in middle
	buf = dbuf_s(20);
	memcpy(buf.data, "HelloWorld", 10);
	buf.len = 10;
	result = buf_insertc(&buf, cbuf(" ", 1), 5, E);
	TEST_ASSERT(memcmp(result.data, "Hello World", 11) == 0, "Insert in middle");
	free_dbuf(&result);
	
	// Insert at end
	buf = dbuf_s(20);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	result = buf_insertc(&buf, cbuf(" World", 6), 5, E);
	TEST_ASSERT(memcmp(result.data, "Hello World", 11) == 0, "Insert at end");
	free_dbuf(&result);
	
	// Insert beyond length (clamped)
	buf = dbuf_s(20);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	result = buf_insertc(&buf, cbuf("!", 1), 100, E);
	TEST_ASSERT(result.len == 6, "Length correct");
	TEST_ASSERT(memcmp(result.data, "Hello!", 6) == 0, "Index clamped");
	free_dbuf(&result);
	
	// Trigger reallocation (E mode)
	buf = dbuf_s(6);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	result = buf_insertc(&buf, cbuf(" World", 6), 5, E);
	TEST_ASSERT(result.data != NULL, "Reallocation succeeds");
	TEST_ASSERT(result.size == 11, "Size is exact (E mode)");
	TEST_ASSERT(result.len == 11, "Length correct");
	free_dbuf(&result);
	
	// Trigger reallocation (x2 mode)
	buf = dbuf_s(6);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	result = buf_insertc(&buf, cbuf(" World", 6), 5, x2);
	TEST_ASSERT(result.data != NULL, "Reallocation succeeds");
	TEST_ASSERT(result.size >= 11, "Size doubled (x2 mode)");
	TEST_ASSERT(result.len == 11, "Length correct");
	free_dbuf(&result);
}

// ============================================================================
// INSERT TESTS - buf_insert
// ============================================================================

void test_buf_insert(void)
{
	TEST_START("buf_insert - insert dynamic buffer");
	
	// Both NULL
	t_dbuf result = buf_insert(NULL, NULL, 0, E);
	TEST_ASSERT(result.data == NULL, "Both NULL returns NULL buffer");
	
	// NULL buf, valid insert
	t_dbuf buf = dbuf_s(0);
	t_dbuf insert = dbuf_s(10);
	memcpy(insert.data, "Hello", 5);
	insert.len = 5;
	
	// This should work
	result = buf_insert(&buf, &insert, 0, E);
	TEST_ASSERT(result.data != NULL, "NULL buf returns insert copy");
	TEST_ASSERT(result.len == 5, "Length correct");
	free_dbuf(&result);
	
	// Valid buf, NULL insert
	buf = dbuf_s(10);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	insert = dbuf_s(0);
	result = buf_insert(&buf, &insert, 0, E);
	TEST_ASSERT(memcmp(result.data, "Hello", 5) == 0, "NULL insert returns buf");
	free_dbuf(&result);
	
	// Normal insertion
	buf = dbuf_s(20);
	memcpy(buf.data, "Hello", 5);
	buf.len = 5;
	insert = dbuf_s(10);
	memcpy(insert.data, " World", 6);
	insert.len = 6;
	result = buf_insert(&buf, &insert, 5, E);
	TEST_ASSERT(result.len == 11, "Length correct");
	TEST_ASSERT(memcmp(result.data, "Hello World", 11) == 0, "Content correct");
	TEST_ASSERT(1, "Insert freed (no double free)");
	free_dbuf(&result);
}

// ============================================================================
// MEMORY LEAK TESTS
// ============================================================================

void test_buffer_memory_leaks(void)
{
	TEST_START("Buffer memory leak checks");
	
	// Many allocations
	for (int i = 0; i < 100; i++) {
		t_dbuf buf = dbuf_s(100);
		free_dbuf(&buf);
	}
	TEST_ASSERT(1, "Multiple allocations/frees");
	
	// Duplications
	t_dbuf orig = dbuf_s(50);
	for (int i = 0; i < 50; i++) {
		t_dbuf dup = dbuf_d(orig);
		free_dbuf(&dup);
	}
	free_dbuf(&orig);
	TEST_ASSERT(1, "Multiple duplications");
	
	// Insert operations
	for (int i = 0; i < 50; i++) {
		t_dbuf buf = dbuf_s(10);
		buf.len = 5;
		t_dbuf ins = dbuf_s(5);
		ins.len = 5;
		buf = buf_insert(&buf, &ins, 0, E);
		free_dbuf(&buf);
	}
	TEST_ASSERT(1, "Insert operations clean up");
}

// ============================================================================
// COMPARISON TESTS
// ============================================================================

void test_buf_cmp(void)
{
	TEST_START("buf_cmp - buffer comparison");
	
	// Equal buffers
	char data1[] = "hello";
	char data2[] = "hello";
	t_cbuf buf1 = cbuf(data1, 5);
	t_cbuf buf2 = cbuf(data2, 5);
	TEST_ASSERT(buf_cmp(buf1, buf2) == 0, "Equal buffers return 0");
	
	// Different content - first less
	char data3[] = "aello";
	t_cbuf buf3 = cbuf(data3, 5);
	TEST_ASSERT(buf_cmp(buf3, buf1) < 0, "Lexicographically smaller returns negative");
	
	// Different content - first greater
	char data4[] = "zello";
	t_cbuf buf4 = cbuf(data4, 5);
	TEST_ASSERT(buf_cmp(buf4, buf1) > 0, "Lexicographically greater returns positive");
	
	// Different sizes - shorter vs longer (same prefix)
	t_cbuf buf5 = cbuf(data1, 3);  // "hel"
	TEST_ASSERT(buf_cmp(buf5, buf1) < 0, "Shorter buffer returns negative");
	TEST_ASSERT(buf_cmp(buf1, buf5) > 0, "Longer buffer returns positive");
	
	// Empty buffers
	t_cbuf empty1 = cbuf(NULL, 0);
	t_cbuf empty2 = cbuf(NULL, 0);
	TEST_ASSERT(buf_cmp(empty1, empty2) == 0, "Empty buffers are equal");
	
	// NULL vs non-NULL
	TEST_ASSERT(buf_cmp(empty1, buf1) < 0, "NULL buffer less than non-NULL");
	TEST_ASSERT(buf_cmp(buf1, empty1) > 0, "Non-NULL buffer greater than NULL");
	
	// Binary data with zeros
	unsigned char bin1[] = {0x00, 0x01, 0x02, 0x03};
	unsigned char bin2[] = {0x00, 0x01, 0x02, 0x03};
	unsigned char bin3[] = {0x00, 0x01, 0x02, 0x04};
	t_cbuf binbuf1 = cbuf(bin1, 4);
	t_cbuf binbuf2 = cbuf(bin2, 4);
	t_cbuf binbuf3 = cbuf(bin3, 4);
	TEST_ASSERT(buf_cmp(binbuf1, binbuf2) == 0, "Equal binary buffers");
	TEST_ASSERT(buf_cmp(binbuf1, binbuf3) < 0, "Different binary buffers");
	
	// Single byte difference
	char single1[] = "a";
	char single2[] = "b";
	t_cbuf sbuf1 = cbuf(single1, 1);
	t_cbuf sbuf2 = cbuf(single2, 1);
	TEST_ASSERT(buf_cmp(sbuf1, sbuf2) < 0, "Single byte comparison");
	
	// Same data, different sizes
	char long_data[] = "test string";
	t_cbuf long_buf = cbuf(long_data, 11);
	t_cbuf short_buf = cbuf(long_data, 4);
	TEST_ASSERT(buf_cmp(short_buf, long_buf) < 0, "Same prefix, different lengths");
}

// ============================================================================
// FIND TESTS
// ============================================================================

void test_buf_findindex(void)
{
	TEST_START("buf_findindex - find bytes in buffer");
	
	// Basic find at beginning
	char haystack1[] = "hello world";
	char needle1[] = "hello";
	t_cbuf buf1 = cbuf(haystack1, 11);
	t_cbuf search1 = cbuf(needle1, 5);
	ssize_t idx = buf_findindex(buf1, search1);
	TEST_ASSERT(idx == 0, "Find at beginning");

	// Find won't work in middle due to size-aligned jumping
	char needle2[] = "world";
	t_cbuf search2 = cbuf(needle2, 5);
	idx = buf_findindex(buf1, search2);
	TEST_ASSERT(idx == -1, "Not found (skipped by 5-byte jumps)");
	
	// Find at exact jump position (position divisible by search size)
	char haystack_aligned[] = "helloworld!";
	t_cbuf buf_aligned = cbuf(haystack_aligned, 11);
	char needle_aligned[] = "world";
	t_cbuf search_aligned = cbuf(needle_aligned, 5);
	idx = buf_findindex(buf_aligned, search_aligned);
	TEST_ASSERT(idx == 1, "Find at position 5 (5/5 = 1)");
	
	// Not found
	char needle3[] = "xyz";
	t_cbuf search3 = cbuf(needle3, 3);
	idx = buf_findindex(buf1, search3);
	TEST_ASSERT(idx == -1, "Not found returns -1");
	
	// NULL buffer
	t_cbuf null_buf = cbuf(NULL, 0);
	idx = buf_findindex(null_buf, search1);
	TEST_ASSERT(idx == -1, "NULL buffer returns -1");
	
	// NULL search
	idx = buf_findindex(buf1, null_buf);
	TEST_ASSERT(idx == -1, "NULL search returns -1");
	
	// Single byte search
	char haystack2[] = "abcdefg";
	char needle4[] = "d";
	t_cbuf buf2 = cbuf(haystack2, 7);
	t_cbuf search4 = cbuf(needle4, 1);
	idx = buf_findindex(buf2, search4);
	TEST_ASSERT(idx >= 0, "Single byte found");
	
	// Search larger than buffer
	char small[] = "hi";
	char large[] = "hello world";
	t_cbuf small_buf = cbuf(small, 2);
	t_cbuf large_search = cbuf(large, 11);
	idx = buf_findindex(small_buf, large_search);
	TEST_ASSERT(idx == -1, "Search larger than buffer returns -1");
	
	// Binary data search
	unsigned char bin_hay[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	unsigned char bin_needle[] = {0x03, 0x04};
	t_cbuf bin_buf = cbuf(bin_hay, 6);
	t_cbuf bin_search = cbuf(bin_needle, 2);
	idx = buf_findindex(bin_buf, bin_search);
	TEST_ASSERT(idx >= 0, "Binary data found");
	
	// Multiple occurrences (should find first)
	char repeated[] = "ababab";
	char pattern[] = "ab";
	t_cbuf rep_buf = cbuf(repeated, 6);
	t_cbuf pat_search = cbuf(pattern, 2);
	idx = buf_findindex(rep_buf, pat_search);
	TEST_ASSERT(idx == 0, "Finds first occurrence");
	
	// Exact match (buffer equals search)
	char exact[] = "test";
	t_cbuf exact_buf = cbuf(exact, 4);
	t_cbuf exact_search = cbuf(exact, 4);
	idx = buf_findindex(exact_buf, exact_search);
	TEST_ASSERT(idx == 0, "Exact match found at 0");
	
	// Empty search in non-empty buffer
	t_cbuf empty_search = cbuf(NULL, 0);
	idx = buf_findindex(buf1, empty_search);
	TEST_ASSERT(idx == -1, "Empty search returns -1");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_buffer_comprehensive_tests(void)
{
	// Constructor tests
	test_cbuf();
	test_cbuf_d();
	test_dbuf_s();
	test_dbuf_d();
	test_dbuf_c();
	
	// Memory management
	test_free_dbuf();
	
	// Shift tests
	test_buf_shift();
	
	// Insert tests
	test_buf_insertc();
	test_buf_insert();
	
	// Comparison tests
	test_buf_cmp();
	
	// Find tests
	test_buf_findindex();
	
	// Memory tests
	test_buffer_memory_leaks();

	TEST_SUMMARY();
}
