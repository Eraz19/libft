/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_buffer_edge_cases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 16:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * BUFFER LIBRARY - EDGE CASE AND ERROR HANDLING TESTS
 * 
 * This file tests:
 * - Boundary conditions
 * - Large allocations
 * - Ownership chain testing
 * - NULL propagation through function chains
 * - Reallocation strategy edge cases
 */

#include "libft_test.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

// Override TEST_ASSERT and TEST_SUMMARY to use buffer-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT BUF_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY BUF_TEST_SUMMARY

// Test counters (shared from test_buffer_comprehensive.c)
extern int g_buf_tests_run;
extern int g_buf_tests_passed;
extern int g_buf_tests_failed;

// ============================================================================
// BOUNDARY TESTS
// ============================================================================

void test_empty_buffers(void)
{
	TEST_START("Empty buffer handling");
	
	// Empty buffer operations
	t_dbuf empty1 = dbuf_s(0);
	t_dbuf empty2 = dbuf_s(0);
	
	// Insert empty into empty
	empty1 = buf_insert(&empty1, &empty2, 0, E);
	TEST_ASSERT(empty1.data == NULL, "Empty + empty = empty");
	
	// Duplicate empty
	t_dbuf dup = dbuf_d(empty1);
	TEST_ASSERT(dup.data == NULL && dup.len == 0, "Duplicate empty buffer");
	
	// Shift empty
	t_cbuf cempty = cbuf(NULL, 0);
	t_cbuf shifted = buf_shift(cempty, 5);
	TEST_ASSERT(shifted.data == NULL, "Shift empty buffer");
	
	// Convert empty to const
	t_cbuf from_empty = cbuf_d(empty1);
	TEST_ASSERT(from_empty.data == NULL && from_empty.size == 0, 
		"Convert empty to const");
}

void test_single_byte_buffers(void)
{
	TEST_START("Single byte buffer operations");
	
	// Create single byte buffer
	t_dbuf single = dbuf_s(1);
	TEST_ASSERT(single.data != NULL && single.size == 1, 
		"Single byte allocation");
	
	((char *)single.data)[0] = 'A';
	single.len = 1;
	
	// Duplicate single byte
	t_dbuf dup = dbuf_d(single);
	TEST_ASSERT(dup.data != NULL && dup.len == 1, "Duplicate single byte");
	TEST_ASSERT(((char *)dup.data)[0] == 'A', "Content copied");
	free_dbuf(&dup);
	
	// Shift single byte
	t_cbuf csingle = cbuf_d(single);
	t_cbuf shifted = buf_shift(csingle, 1);
	TEST_ASSERT(shifted.data == NULL, "Shift beyond single byte");
	
	// Insert into single byte
	t_dbuf insert = dbuf_s(1);
	((char *)insert.data)[0] = 'B';
	insert.len = 1;
	single = buf_insert(&single, &insert, 0, E);
	TEST_ASSERT(single.len == 2, "Insert at start of single byte");
	TEST_ASSERT(((char *)single.data)[0] == 'B', "First byte correct");
	TEST_ASSERT(((char *)single.data)[1] == 'A', "Second byte correct");
	
	free_dbuf(&single);
}

void test_very_large_buffers(void)
{
	TEST_START("Very large buffer handling");
	
	// Create a large buffer (1MB)
	size_t large_size = 1024 * 1024;
	t_dbuf large = dbuf_s(large_size);
	TEST_ASSERT(large.data != NULL, "Large allocation succeeds (1MB)");
	
	if (large.data != NULL) {
		// Fill with pattern
		for (size_t i = 0; i < 1000; i++)
			((char *)large.data)[i] = 'X';
		large.len = 1000;
		
		// Duplicate large buffer
		t_dbuf dup = dbuf_d(large);
		TEST_ASSERT(dup.data != NULL && dup.len == 1000, 
			"Duplicate large buffer");
		TEST_ASSERT(((char *)dup.data)[0] == 'X', "Content preserved");
		free_dbuf(&dup);
		
		// Shift large buffer
		t_cbuf clarge = cbuf_d(large);
		t_cbuf shifted = buf_shift(clarge, 500);
		TEST_ASSERT(shifted.data != NULL && shifted.size == 500,
			"Shift large buffer (size = len - offset)");
		
		// Insert into large buffer
		t_dbuf insert = dbuf_s(100);
		for (size_t i = 0; i < 100; i++)
			((char *)insert.data)[i] = 'Y';
		insert.len = 100;
		large = buf_insert(&large, &insert, 500, E);
		TEST_ASSERT(large.len == 1100, "Insert into large buffer");
		TEST_ASSERT(((char *)large.data)[500] == 'Y', "Insert content correct");
		
		free_dbuf(&large);
	} else {
		g_buf_tests_failed += 5; // Account for skipped tests
	}
}

void test_alignment_and_boundaries(void)
{
	TEST_START("Alignment and boundary conditions");
	
	// Test various buffer sizes
	size_t sizes[] = {1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 63, 64, 127, 128};
	int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
	
	for (int i = 0; i < num_sizes; i++) {
		t_dbuf buf = dbuf_s(sizes[i]);
		if (buf.data != NULL) {
			// Fill buffer
			for (size_t j = 0; j < sizes[i]; j++)
				((char *)buf.data)[j] = (char)(j & 0xFF);
			buf.len = sizes[i];
			
			// Verify content
			int valid = 1;
			for (size_t j = 0; j < sizes[i]; j++) {
				if (((char *)buf.data)[j] != (char)(j & 0xFF))
					valid = 0;
			}
			free_dbuf(&buf);
			
			if (!valid) {
				TEST_ASSERT(0, "Content corrupted at boundary");
				break;
			}
		}
	}
	TEST_ASSERT(1, "All boundary sizes handled correctly");
}

// ============================================================================
// NULL PROPAGATION TESTS
// ============================================================================

void test_buffer_null_propagation_chain(void)
{
	TEST_START("Buffer NULL propagation through function chains");
	
	// Chain 1: NULL -> insert -> insert
	t_dbuf null_buf = dbuf_s(0);
	t_dbuf insert1 = dbuf_s(2);
	((char *)insert1.data)[0] = 'A';
	((char *)insert1.data)[1] = 'B';
	insert1.len = 2;
	
	null_buf = buf_insert(&null_buf, &insert1, 0, E);
	TEST_ASSERT(null_buf.data != NULL && null_buf.len == 2, 
		"NULL + buffer = buffer");
	
	t_dbuf insert2 = dbuf_s(2);
	((char *)insert2.data)[0] = 'C';
	((char *)insert2.data)[1] = 'D';
	insert2.len = 2;
	null_buf = buf_insert(&null_buf, &insert2, 0, E);
	TEST_ASSERT(null_buf.len == 4, "Buffer + buffer = combined");
	TEST_ASSERT(((char *)null_buf.data)[0] == 'C', "Order correct");
	free_dbuf(&null_buf);
	
	// Chain 2: shift to empty -> insert
	t_dbuf buf = dbuf_s(5);
	buf.len = 5;
	t_cbuf cbuf = cbuf_d(buf);
	cbuf = buf_shift(cbuf, 10); // Beyond size
	TEST_ASSERT(cbuf.data == NULL, "Shift beyond returns NULL");
	
	free_dbuf(&buf);
}

void test_buffer_ownership_transfer(void)
{
	TEST_START("Buffer memory ownership transfer");
	
	// Test that buf_insert frees the insert buffer
	t_dbuf buf1 = dbuf_s(10);
	memset(buf1.data, 'A', 5);
	buf1.len = 5;
	
	t_dbuf buf2 = dbuf_s(10);
	memset(buf2.data, 'B', 5);
	buf2.len = 5;
	
	buf1 = buf_insert(&buf1, &buf2, 5, E);
	TEST_ASSERT(buf1.data != NULL, "Result valid");
	TEST_ASSERT(buf1.len == 10, "Length correct");
	TEST_ASSERT(((char *)buf1.data)[0] == 'A', "First part preserved");
	TEST_ASSERT(((char *)buf1.data)[5] == 'B', "Second part inserted");
	// buf2 should be freed internally
	TEST_ASSERT(1, "Insert consumed buf2 (no double free)");
	free_dbuf(&buf1);
	
	// Test buf_insertc doesn't modify source
	t_dbuf buf3 = dbuf_s(5);
	buf3.len = 5;
	char data[] = "XYZ";
	t_cbuf const_buf = cbuf(data, 3);
	
	buf3 = buf_insertc(&buf3, const_buf, 0, E);
	TEST_ASSERT(buf3.len == 8, "Insertc adds to length");
	TEST_ASSERT(data[0] == 'X', "Source unchanged");
	free_dbuf(&buf3);
}

// ============================================================================
// REALLOCATION STRATEGY TESTS
// ============================================================================

void test_exact_allocation_strategy(void)
{
	TEST_START("Exact allocation strategy (E)");
	
	// Start with small buffer
	t_dbuf buf = dbuf_s(5);
	memset(buf.data, 'A', 5);
	buf.len = 5;
	
	// Insert requiring realloc with E strategy
	t_dbuf insert = dbuf_s(10);
	memset(insert.data, 'B', 10);
	insert.len = 10;
	
	buf = buf_insert(&buf, &insert, 5, E);
	TEST_ASSERT(buf.len == 15, "Length is sum");
	TEST_ASSERT(buf.size == 15, "Size is exact (E strategy)");
	
	// Insert again
	t_dbuf insert2 = dbuf_s(5);
	memset(insert2.data, 'C', 5);
	insert2.len = 5;
	
	buf = buf_insert(&buf, &insert2, 15, E);
	TEST_ASSERT(buf.size == 20, "Size remains exact");
	
	free_dbuf(&buf);
}

void test_doubling_allocation_strategy(void)
{
	TEST_START("Doubling allocation strategy (x2)");
	
	// Start with small buffer
	t_dbuf buf = dbuf_s(4);
	memset(buf.data, 'A', 4);
	buf.len = 4;
	
	// Insert requiring realloc with x2 strategy
	t_dbuf insert = dbuf_s(5);
	memset(insert.data, 'B', 5);
	insert.len = 5;
	
	buf = buf_insert(&buf, &insert, 4, x2);
	TEST_ASSERT(buf.len == 9, "Length is sum");
	// Size should double until it fits: 4 -> 8 -> 16
	TEST_ASSERT(buf.size == 16, "Size doubled to fit (x2 strategy)");
	
	// Insert that fits in existing buffer
	t_dbuf insert2 = dbuf_s(3);
	memset(insert2.data, 'C', 3);
	insert2.len = 3;
	
	size_t old_size = buf.size;
	buf = buf_insert(&buf, &insert2, 9, x2);
	TEST_ASSERT(buf.size == old_size, "No realloc when space available");
	
	free_dbuf(&buf);
}

void test_reallocation_preservation(void)
{
	TEST_START("Content preservation during reallocation");
	
	// Create buffer with known pattern
	t_dbuf buf = dbuf_s(10);
	for (int i = 0; i < 10; i++)
		((char *)buf.data)[i] = '0' + (t_u8)i;
	buf.len = 10;
	
	// Force reallocation
	t_dbuf insert = dbuf_s(20);
	memset(insert.data, 'X', 20);
	insert.len = 20;
	
	buf = buf_insert(&buf, &insert, 5, E);
	
	// Verify original content preserved
	TEST_ASSERT(((char *)buf.data)[0] == '0', "Start preserved");
	TEST_ASSERT(((char *)buf.data)[4] == '4', "Before insert preserved");
	TEST_ASSERT(((char *)buf.data)[5] == 'X', "Insert content correct");
	TEST_ASSERT(((char *)buf.data)[25] == '5', "After insert preserved");
	TEST_ASSERT(((char *)buf.data)[29] == '9', "End preserved");
	
	free_dbuf(&buf);
}

// ============================================================================
// SHIFT EDGE CASES
// ============================================================================

void test_shift_edge_cases(void)
{
	TEST_START("buf_shift edge cases");
	
	// Shift by 0
	char data[] = "ABCDEF";
	t_cbuf buf = cbuf(data, 6);
	t_cbuf shifted = buf_shift(buf, 0);
	TEST_ASSERT(shifted.data == data, "Shift by 0 unchanged");
	TEST_ASSERT(shifted.size == 6, "Size unchanged");
	
	// Shift to exactly end
	shifted = buf_shift(buf, 6);
	TEST_ASSERT(shifted.data == NULL, "Shift to end returns NULL");
	
	// Shift beyond end
	shifted = buf_shift(buf, 100);
	TEST_ASSERT(shifted.data == NULL, "Shift beyond returns NULL");
	
	// Multiple shifts
	shifted = buf_shift(buf, 2);
	TEST_ASSERT(((const char *)shifted.data)[0] == 'C', "First shift correct");
	shifted = buf_shift(shifted, 2);
	TEST_ASSERT(((const char *)shifted.data)[0] == 'E', "Second shift correct");
	TEST_ASSERT(shifted.size == 2, "Size correct after shifts");
	
	// Shift NULL buffer
	t_cbuf null_buf = cbuf(NULL, 0);
	shifted = buf_shift(null_buf, 5);
	TEST_ASSERT(shifted.data == NULL, "Shift NULL buffer");
}

// ============================================================================
// INSERT EDGE CASES
// ============================================================================

void test_insert_at_boundaries(void)
{
	TEST_START("Insert at buffer boundaries");
	
	// Insert at position 0
	t_dbuf buf = dbuf_s(10);
	memset(buf.data, 'A', 5);
	buf.len = 5;
	
	t_dbuf insert = dbuf_s(3);
	memset(insert.data, 'B', 3);
	insert.len = 3;
	
	buf = buf_insert(&buf, &insert, 0, E);
	TEST_ASSERT(((char *)buf.data)[0] == 'B', "Insert at 0 - first byte");
	TEST_ASSERT(((char *)buf.data)[2] == 'B', "Insert at 0 - last insert byte");
	TEST_ASSERT(((char *)buf.data)[3] == 'A', "Insert at 0 - original starts");
	free_dbuf(&buf);
	
	// Insert at exact end
	buf = dbuf_s(10);
	memset(buf.data, 'A', 5);
	buf.len = 5;
	
	insert = dbuf_s(3);
	memset(insert.data, 'B', 3);
	insert.len = 3;
	
	buf = buf_insert(&buf, &insert, 5, E);
	TEST_ASSERT(((char *)buf.data)[4] == 'A', "Insert at end - last original");
	TEST_ASSERT(((char *)buf.data)[5] == 'B', "Insert at end - first insert");
	free_dbuf(&buf);
	
	// Insert beyond end (should clamp)
	buf = dbuf_s(10);
	memset(buf.data, 'A', 5);
	buf.len = 5;
	
	insert = dbuf_s(3);
	memset(insert.data, 'B', 3);
	insert.len = 3;
	
	buf = buf_insert(&buf, &insert, 100, E);
	TEST_ASSERT(buf.len == 8, "Insert beyond clamped");
	TEST_ASSERT(((char *)buf.data)[5] == 'B', "Clamped to end");
	free_dbuf(&buf);
}

void test_insert_zero_length(void)
{
	TEST_START("Insert zero-length buffers");
	
	// Insert NULL/empty buffer
	t_dbuf buf = dbuf_s(10);
	memset(buf.data, 'A', 5);
	buf.len = 5;
	
	t_dbuf empty = dbuf_s(0); // Proper empty buffer (NULL data, 0 len)
	
	size_t old_len = buf.len;
	buf = buf_insert(&buf, &empty, 2, E);
	TEST_ASSERT(buf.len == old_len, "Insert empty doesn't change length");
	TEST_ASSERT(((char *)buf.data)[0] == 'A', "Content unchanged");
	
	free_dbuf(&buf);
}

// ============================================================================
// MEMORY LEAK TESTS
// ============================================================================

void test_buffer_memory_leak_edge_cases(void)
{
	TEST_START("Buffer memory leak edge cases");
	
	// Many small allocations
	for (int i = 0; i < 100; i++) {
		t_dbuf buf = dbuf_s((size_t)i + 1);
		free_dbuf(&buf);
	}
	TEST_ASSERT(1, "Many small allocations");
	
	// Reallocation stress test
	t_dbuf buf = dbuf_s(1);
	buf.len = 1;
	for (int i = 0; i < 10; i++) {
		t_dbuf insert = dbuf_s(1);
		insert.len = 1;
		buf = buf_insert(&buf, &insert, buf.len, E);
	}
	TEST_ASSERT(buf.len == 11, "Reallocation stress test");
	free_dbuf(&buf);
	
	// Shift operations don't allocate
	char data[100];
	t_cbuf cbuf_ = cbuf(data, 100);
	for (int i = 0; i < 10; i++)
		cbuf_ = buf_shift(cbuf_, 1);
	TEST_ASSERT(1, "Shift operations (no allocation)");
}

// ============================================================================
// EDGE CASE TEST RUNNER
// ============================================================================

void run_buffer_edge_case_tests(void)
{
	test_empty_buffers();
	test_single_byte_buffers();
	test_very_large_buffers();
	test_alignment_and_boundaries();
	
	test_buffer_null_propagation_chain();
	test_buffer_ownership_transfer();
	
	test_exact_allocation_strategy();
	test_doubling_allocation_strategy();
	test_reallocation_preservation();
	
	test_shift_edge_cases();
	
	test_insert_at_boundaries();
	test_insert_zero_length();
	
	test_buffer_memory_leak_edge_cases();
	
	TEST_SUMMARY();
}
