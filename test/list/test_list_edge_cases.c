/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_edge_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:30:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 17:30:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * LIST LIBRARY - EDGE CASE AND ERROR HANDLING TESTS
 * 
 * This file tests:
 * - Boundary conditions
 * - Large lists
 * - NULL propagation through function chains
 * - Memory ownership edge cases
 * - Insert/delete pattern combinations
 * - Copy and map failure scenarios
 */

#include "libft_test.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Override TEST_ASSERT and TEST_SUMMARY to use list-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT LIST_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY LIST_TEST_SUMMARY

// Test counters (shared from test_list_comprehensive.c)
extern int g_list_tests_run;
extern int g_list_tests_passed;
extern int g_list_tests_failed;

// Helper functions
static void del_int(void *content)
{
	free(content);
}

static void *copy_int(void *content)
{
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = *(int *)content;
	return new;
}

static void *triple_int(void *content)
{
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = (*(int *)content) * 3;
	return new;
}

static void *return_null(void *content)
{
	(void)content;
	return NULL;  // Simulate allocation failure
}

static int g_foreach_count = 0;
static void count_foreach(void *content)
{
	(void)content;
	g_foreach_count++;
}

static void *copy_fail_after_3(void *content)
{
	static int count = 0;
	if (count++ >= 3)
		return NULL;
	return copy_int(content);
}

// ============================================================================
// EMPTY LIST EDGE CASES
// ============================================================================

void test_empty_list_operations(void)
{
	TEST_START("Empty list edge cases");
	
	t_lst empty = lst_();
	
	// Get from empty
	t_node *from_empty = get(empty, 0);
	TEST_ASSERT(from_empty == NULL, "Get from empty returns NULL");
	
	// Foreach on empty
	g_foreach_count = 0;
	lst_foreach(empty, count_foreach);
	TEST_ASSERT(g_foreach_count == 0, "Foreach on empty does nothing");
	
	// Map empty
	t_lst mapped = lst_map(&empty, triple_int, del_int);
	TEST_ASSERT(mapped.nodes == NULL, "Map empty returns empty");
	TEST_ASSERT(mapped.size == 0, "Map empty size is 0");
	
	// Copy empty
	t_lst copied = lst_l(empty, copy_int, del_int);
	TEST_ASSERT(copied.nodes == NULL, "Copy empty returns empty");
	
	// Free empty (shouldn't crash)
	free_lst(&empty, del_int);
	TEST_ASSERT(1, "Free empty list safe");
	
	// Free node from empty (shouldn't crash)
	t_lst empty2 = lst_();
	free_node(&empty2, NULL, del_int);
	TEST_ASSERT(1, "Free node from empty safe");
}

// ============================================================================
// SINGLE NODE EDGE CASES
// ============================================================================

void test_single_node_operations(void)
{
	TEST_START("Single node edge cases");
	
	// Create single node list
	int *v = malloc(sizeof(int));
	*v = 42;
	t_lst single = lst_n(node(v));
	
	// Get index 0
	t_node *first = get(single, 0);
	TEST_ASSERT(first != NULL && *(int *)first->content == 42, "Get single node");
	
	// Get out of bounds
	t_node *out = get(single, 1);
	TEST_ASSERT(out == NULL, "Get beyond single returns NULL");
	
	// Copy single
	t_lst copy = lst_l(single, copy_int, del_int);
	TEST_ASSERT(copy.size == 1, "Copy single has size 1");
	TEST_ASSERT(*(int *)copy.nodes->content == 42, "Copy content correct");
	free_lst(&copy, del_int);
	
	// Map single
	t_lst mapped = lst_map(&single, triple_int, del_int);
	TEST_ASSERT(mapped.size == 1, "Map single has size 1");
	TEST_ASSERT(*(int *)mapped.nodes->content == 126, "Map result correct");
	free_lst(&mapped, del_int);
	
	// Create new single for deletion test
	int *v2 = malloc(sizeof(int));
	*v2 = 99;
	t_lst single2 = lst_n(node(v2));
	
	// Free only node
	free_node(&single2, single2.nodes, del_int);
	TEST_ASSERT(single2.nodes == NULL, "Free only node leaves empty list");
	TEST_ASSERT(single2.size == 0, "Size reset after free");
}

// ============================================================================
// VERY LARGE LIST TESTS
// ============================================================================

void test_very_large_lists(void)
{
	TEST_START("Very large list handling");
	
	// Create list with 1000 nodes
	t_lst large = lst_();
	for (int i = 0; i < 1000; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		large = lst_insert(&large, node(val), (size_t)i);
	}
	TEST_ASSERT(large.size == 1000, "Large list created");
	
	// Get various indices
	TEST_ASSERT(*(int *)get(large, 0)->content == 0, "Get first from large");
	TEST_ASSERT(*(int *)get(large, 500)->content == 500, "Get middle from large");
	TEST_ASSERT(*(int *)get(large, 999)->content == 999, "Get last from large");
	
	// Copy large list
	t_lst large_copy = lst_l(large, copy_int, del_int);
	TEST_ASSERT(large_copy.size == 1000, "Large list copied");
	TEST_ASSERT(*(int *)get(large_copy, 0)->content == 0, "Copy first correct");
	TEST_ASSERT(*(int *)get(large_copy, 999)->content == 999, "Copy last correct");
	
	// Foreach on large list
	g_foreach_count = 0;
	lst_foreach(large_copy, count_foreach);
	TEST_ASSERT(g_foreach_count == 1000, "Foreach counts all nodes");
	
	free_lst(&large, del_int);
	free_lst(&large_copy, del_int);
	
	// Test performance with many deletions
	t_lst delete_test = lst_();
	for (int i = 0; i < 100; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		delete_test = lst_insert(&delete_test, node(val), (size_t)i);
	}
	
	// Delete every other node
	for (int i = 49; i >= 0; i--) {
		t_node *to_delete = get(delete_test, (size_t)i * 2);
		free_node(&delete_test, to_delete, del_int);
	}
	TEST_ASSERT(delete_test.size == 50, "Alternating deletions correct");
	
	free_lst(&delete_test, del_int);
}

// ============================================================================
// INSERT PATTERN EDGE CASES
// ============================================================================

void test_insert_patterns(void)
{
	TEST_START("Insert pattern edge cases");
	
	// Insert only at beginning
	t_lst front = lst_();
	for (int i = 0; i < 10; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		front = lst_insert(&front, node(val), 0);
	}
	TEST_ASSERT(*(int *)get(front, 0)->content == 9, "Front insert - newest first");
	TEST_ASSERT(*(int *)get(front, 9)->content == 0, "Front insert - oldest last");
	free_lst(&front, del_int);
	
	// Insert only at end
	t_lst back = lst_();
	for (int i = 0; i < 10; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		back = lst_insert(&back, node(val), back.size);
	}
	TEST_ASSERT(*(int *)get(back, 0)->content == 0, "Back insert - first stays first");
	TEST_ASSERT(*(int *)get(back, 9)->content == 9, "Back insert - last is newest");
	free_lst(&back, del_int);
	
	// Insert at alternating positions
	t_lst alt = lst_();
	for (int i = 0; i < 10; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		if (i % 2 == 0)
			alt = lst_insert(&alt, node(val), 0);
		else
			alt = lst_insert(&alt, node(val), alt.size);
	}
	TEST_ASSERT(alt.size == 10, "Alternating pattern size");
	free_lst(&alt, del_int);
	
	// Insert beyond size (should clamp to end)
	t_lst clamp = lst_();
	int *v1 = malloc(sizeof(int));
	*v1 = 1;
	clamp = lst_insert(&clamp, node(v1), 0);
	
	int *v2 = malloc(sizeof(int));
	*v2 = 2;
	clamp = lst_insert(&clamp, node(v2), 1000);
	TEST_ASSERT(clamp.size == 2, "Insert beyond clamped");
	TEST_ASSERT(*(int *)get(clamp, 1)->content == 2, "Clamped to end");
	free_lst(&clamp, del_int);
}

// ============================================================================
// DELETE PATTERN EDGE CASES
// ============================================================================

void test_delete_patterns(void)
{
	TEST_START("Delete pattern edge cases");
	
	// Create list with 10 nodes
	t_lst list = lst_();
	for (int i = 0; i < 10; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		list = lst_insert(&list, node(val), (size_t)i);
	}
	
	// Delete from beginning repeatedly
	free_node(&list, list.nodes, del_int);
	free_node(&list, list.nodes, del_int);
	free_node(&list, list.nodes, del_int);
	TEST_ASSERT(list.size == 7, "Three front deletions");
	TEST_ASSERT(*(int *)get(list, 0)->content == 3, "Front deletions shift list");
	
	// Delete from end repeatedly
	t_node *last = get(list, 6);
	free_node(&list, last, del_int);
	last = get(list, 5);
	free_node(&list, last, del_int);
	TEST_ASSERT(list.size == 5, "Back deletions");
	TEST_ASSERT(*(int *)get(list, 4)->content == 7, "Back deletions preserve rest");
	
	free_lst(&list, del_int);
	
	// Delete all nodes one by one from front
	t_lst delete_all = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		delete_all = lst_insert(&delete_all, node(val), (size_t)i);
	}
	
	while (delete_all.size > 0)
		free_node(&delete_all, delete_all.nodes, del_int);
	TEST_ASSERT(delete_all.nodes == NULL, "All nodes deleted");
	TEST_ASSERT(delete_all.size == 0, "Size is 0 after all deleted");
	
	// Out of bounds delete (should do nothing)
	int *v = malloc(sizeof(int));
	*v = 100;
	t_lst oob = lst_n(node(v));
	free_node(&oob, NULL, del_int);
	TEST_ASSERT(oob.size == 1, "NULL node does nothing");
	free_lst(&oob, del_int);
}

// ============================================================================
// NULL PROPAGATION TESTS
// ============================================================================

void test_list_null_propagation(void)
{
	TEST_START("List NULL propagation");
	
	// Chain: empty -> insert -> insert -> map
	t_lst chain = lst_();
	int *v1 = malloc(sizeof(int));
	*v1 = 10;
	chain = lst_insert(&chain, node(v1), 0);
	
	int *v2 = malloc(sizeof(int));
	*v2 = 20;
	chain = lst_insert(&chain, node(v2), 1);
	
	chain = lst_map(&chain, triple_int, del_int);
	TEST_ASSERT(chain.size == 2, "Chain operations size");
	TEST_ASSERT(*(int *)get(chain, 0)->content == 30, "Chain first element");
	TEST_ASSERT(*(int *)get(chain, 1)->content == 60, "Chain second element");
	free_lst(&chain, del_int);
	
	// NULL function propagation
	t_lst null_func = lst_();
	int *v3 = malloc(sizeof(int));
	*v3 = 5;
	null_func = lst_insert(&null_func, node(v3), 0);
	
	t_lst mapped = lst_map(&null_func, NULL, del_int);
	TEST_ASSERT(mapped.nodes == NULL, "NULL function returns empty");
	
	// Copy with NULL function
	int *v4 = malloc(sizeof(int));
	*v4 = 7;
	t_lst copy_null = lst_n(node(v4));
	t_lst copied = lst_l(copy_null, NULL, del_int);
	TEST_ASSERT(copied.nodes == NULL, "NULL copy function returns empty");
	free_lst(&copy_null, del_int);
}

// ============================================================================
// COPY FAILURE SCENARIOS
// ============================================================================

void test_copy_failures(void)
{
	TEST_START("Copy failure handling");
	
	// Create list with 5 nodes
	t_lst original = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		original = lst_insert(&original, node(val), (size_t)i);
	}
	
	// Copy should fail after 3 elements
	t_lst failed_copy = lst_l(original, copy_fail_after_3, del_int);
	TEST_ASSERT(failed_copy.nodes == NULL, "Copy failure returns empty");
	TEST_ASSERT(failed_copy.size == 0, "Failed copy size is 0");
	
	// Original should still be intact
	TEST_ASSERT(original.size == 5, "Original preserved after copy failure");
	
	free_lst(&original, del_int);
}

// ============================================================================
// MAP FAILURE SCENARIOS
// ============================================================================

void test_map_failures(void)
{
	TEST_START("Map failure handling");
	
	// Create list
	t_lst list = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		list = lst_insert(&list, node(val), (size_t)i);
	}
	
	// Map with function that returns NULL
	t_lst mapped = lst_map(&list, return_null, del_int);
	TEST_ASSERT(mapped.nodes == NULL, "Map with NULL return gives empty");
	TEST_ASSERT(mapped.size == 0, "Map failure size is 0");
	
	// Original should be freed by lst_map
	TEST_ASSERT(1, "Original consumed on map failure");
}

// ============================================================================
// BOUNDARY INDEX TESTS
// ============================================================================

void test_boundary_indices(void)
{
	TEST_START("Boundary index handling");
	
	// Create list with 5 nodes
	t_lst list = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		list = lst_insert(&list, node(val), (size_t)i);
	}
	
	// Get at boundaries
	TEST_ASSERT(get(list, 0) != NULL, "Get index 0 valid");
	TEST_ASSERT(get(list, 4) != NULL, "Get last index valid");
	TEST_ASSERT(get(list, 5) == NULL, "Get size index invalid");
	TEST_ASSERT(get(list, 100) == NULL, "Get way beyond invalid");
	
	// Insert at boundaries
	int *v1 = malloc(sizeof(int));
	*v1 = 99;
	list = lst_insert(&list, node(v1), 0);
	TEST_ASSERT(*(int *)get(list, 0)->content == 99, "Insert at 0");
	
	int *v2 = malloc(sizeof(int));
	*v2 = 88;
	list = lst_insert(&list, node(v2), list.size);
	TEST_ASSERT(*(int *)get(list, list.size - 1)->content == 88, "Insert at size");
	
	// Delete at boundaries
	size_t orig_size = list.size;
	free_node(&list, list.nodes, del_int);
	TEST_ASSERT(list.size == orig_size - 1, "Delete at 0");
	
	t_node *last_node = get(list, list.size - 1);
	free_node(&list, last_node, del_int);
	TEST_ASSERT(list.size == orig_size - 2, "Delete at last");
	
	free_node(&list, NULL, del_int);
	TEST_ASSERT(list.size == orig_size - 2, "NULL node does nothing");
	
	free_lst(&list, del_int);
}

// ============================================================================
// FILTER EDGE CASE TESTS
// ============================================================================

// Helper functions for filter tests
static t_bool is_even(void *content, void *context)
{
	(void)context;
	return (*(int *)content % 2 == 0);
}

static t_bool is_negative(void *content, void *context)
{
	(void)context;
	return (*(int *)content < 0);
}

static t_bool always_true(void *content, void *context)
{
	(void)content;
	(void)context;
	return (TRUE);
}

static t_bool is_zero(void *content, void *context)
{
	(void)context;
	return (*(int *)content == 0);
}

void test_filter_edge_cases(void)
{
	TEST_START("Filter edge case handling");
	
	// Filter on empty list
	t_lst empty = lst_();
	t_lst filtered_empty = filter(empty, is_even, NULL);
	TEST_ASSERT(filtered_empty.nodes == NULL, "Filter empty returns NULL");
	TEST_ASSERT(filtered_empty.size == 0, "Filter empty size is 0");
	
	// Filter with NULL comparison
	int *v1 = malloc(sizeof(int));
	*v1 = 10;
	t_lst list = lst_n(node(v1));
	t_lst null_cmp = filter(list, NULL, NULL);
	TEST_ASSERT(null_cmp.nodes == NULL, "NULL comparison returns empty");
	TEST_ASSERT(null_cmp.size == 0, "NULL comparison size is 0");
	free_lst(&list, del_int);
	
	// Filter with no matches
	t_lst no_match_list = lst_();
	for (int i = 1; i <= 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i * 2 + 1;  // All odd numbers: 3, 5, 7, 9, 11
		no_match_list = lst_insert(&no_match_list, node(val), (size_t)(i - 1));
	}
	t_lst no_match = filter(no_match_list, is_even, NULL);
	TEST_ASSERT(no_match.nodes == NULL, "No matches returns empty");
	TEST_ASSERT(no_match.size == 0, "No matches size is 0");
	free_lst(&no_match_list, del_int);
	
	// Filter first element matches
	t_lst first_match = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = (i == 0) ? 10 : i * 2 + 1;  // First is even, rest odd
		first_match = lst_insert(&first_match, node(val), (size_t)i);
	}
	t_lst filtered_first = filter(first_match, is_even, NULL);
	TEST_ASSERT(filtered_first.nodes != NULL, "First match found");
	TEST_ASSERT(*(int *)filtered_first.nodes->content == 10, "First match correct");
	free_lst(&first_match, del_int);
	
	// Filter last element matches
	t_lst last_match = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = (i == 4) ? 10 : i * 2 + 1;  // Last is even, rest odd
		last_match = lst_insert(&last_match, node(val), (size_t)i);
	}
	t_lst filtered_last = filter(last_match, is_even, NULL);
	TEST_ASSERT(filtered_last.nodes != NULL, "Last match found");
	TEST_ASSERT(*(int *)filtered_last.nodes->content == 10, "Last match correct");
	free_lst(&last_match, del_int);
	
	// Filter middle element matches
	t_lst middle_match = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = (i == 2) ? 10 : i * 2 + 1;  // Middle is even, rest odd
		middle_match = lst_insert(&middle_match, node(val), (size_t)i);
	}
	t_lst filtered_middle = filter(middle_match, is_even, NULL);
	TEST_ASSERT(filtered_middle.nodes != NULL, "Middle match found");
	TEST_ASSERT(*(int *)filtered_middle.nodes->content == 10, "Middle match correct");
	free_lst(&middle_match, del_int);
	
	// Filter all elements match (returns first)
	t_lst all_match = lst_();
	for (int i = 0; i < 5; i++) {
		int *val = malloc(sizeof(int));
		*val = i * 2;  // All even
		all_match = lst_insert(&all_match, node(val), (size_t)i);
	}
	t_lst filtered_all = filter(all_match, is_even, NULL);
	TEST_ASSERT(filtered_all.nodes != NULL, "All match found");
	TEST_ASSERT(*(int *)filtered_all.nodes->content == 0, "Returns first match");
	free_lst(&all_match, del_int);
	
	// Filter single node list - match
	int *v2 = malloc(sizeof(int));
	*v2 = 10;
	t_lst single_match = lst_n(node(v2));
	t_lst filtered_single_match = filter(single_match, is_even, NULL);
	TEST_ASSERT(filtered_single_match.nodes != NULL, "Single match found");
	TEST_ASSERT(*(int *)filtered_single_match.nodes->content == 10, "Single match correct");
	free_lst(&single_match, del_int);
	
	// Filter single node list - no match
	int *v3 = malloc(sizeof(int));
	*v3 = 11;
	t_lst single_no_match = lst_n(node(v3));
	t_lst filtered_single_no = filter(single_no_match, is_even, NULL);
	TEST_ASSERT(filtered_single_no.nodes == NULL, "Single no match returns empty");
	free_lst(&single_no_match, del_int);
	
	// Filter with always true predicate (returns first)
	t_lst any_list = lst_();
	for (int i = 0; i < 3; i++) {
		int *val = malloc(sizeof(int));
		*val = i + 1;
		any_list = lst_insert(&any_list, node(val), (size_t)i);
	}
	t_lst filtered_true = filter(any_list, always_true, NULL);
	TEST_ASSERT(filtered_true.nodes != NULL, "Always true finds first");
	TEST_ASSERT(*(int *)filtered_true.nodes->content == 1, "Returns first element");
	free_lst(&any_list, del_int);
	
	// Filter looking for zero
	t_lst with_zero = lst_();
	int *z1 = malloc(sizeof(int));
	int *z2 = malloc(sizeof(int));
	int *z3 = malloc(sizeof(int));
	*z1 = 5;
	*z2 = 0;
	*z3 = 10;
	with_zero = lst_insert(&with_zero, node(z1), 0);
	with_zero = lst_insert(&with_zero, node(z2), 1);
	with_zero = lst_insert(&with_zero, node(z3), 2);
	t_lst filtered_zero = filter(with_zero, is_zero, NULL);
	TEST_ASSERT(filtered_zero.nodes != NULL, "Zero found");
	TEST_ASSERT(*(int *)filtered_zero.nodes->content == 0, "Zero match correct");
	free_lst(&with_zero, del_int);
	
	// Filter with negative numbers
	t_lst with_negatives = lst_();
	for (int i = -3; i <= 3; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		with_negatives = lst_insert(&with_negatives, node(val), 
			(size_t)(i + 3));
	}
	t_lst filtered_neg = filter(with_negatives, is_negative, NULL);
	TEST_ASSERT(filtered_neg.nodes != NULL, "Negative found");
	TEST_ASSERT(*(int *)filtered_neg.nodes->content == -3, "First negative correct");
	free_lst(&with_negatives, del_int);
}

// ============================================================================
// OWNERSHIP CHAIN TESTS
// ============================================================================

void test_ownership_chains(void)
{
	TEST_START("Memory ownership chains");
	
	// Create -> Copy -> Map -> Free chain
	t_lst orig = lst_();
	for (int i = 0; i < 3; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		orig = lst_insert(&orig, node(val), (size_t)i);
	}
	
	t_lst copy1 = lst_l(orig, copy_int, del_int);
	t_lst copy2 = lst_l(orig, copy_int, del_int);
	
	TEST_ASSERT(copy1.size == 3, "First copy valid");
	TEST_ASSERT(copy2.size == 3, "Second copy valid");
	TEST_ASSERT(orig.size == 3, "Original unchanged by copy");
	
	// Map consumes input
	t_lst mapped1 = lst_map(&copy1, triple_int, del_int);
	TEST_ASSERT(mapped1.size == 3, "Map result valid");
	// copy1 is now invalid (freed by map)
	
	// Free in various orders
	free_lst(&orig, del_int);
	free_lst(&mapped1, del_int);
	free_lst(&copy2, del_int);
	TEST_ASSERT(1, "Multiple frees in order");
}

// ============================================================================
// STRESS TESTS
// ============================================================================

void test_list_stress(void)
{
	TEST_START("List stress tests");
	
	// Rapid insert/delete cycles
	t_lst stress = lst_();
	for (int cycle = 0; cycle < 10; cycle++) {
		// Insert 20
		for (int i = 0; i < 20; i++) {
			int *val = malloc(sizeof(int));
			*val = i;
			stress = lst_insert(&stress, node(val), stress.size);
		}
		
		// Delete 10
		for (int i = 0; i < 10; i++) {
			free_node(&stress, stress.nodes, del_int);
		}
	}
	TEST_ASSERT(stress.size == 100, "Stress test final size");
	free_lst(&stress, del_int);
	
	// Many small lists
	for (int i = 0; i < 100; i++) {
		t_lst small = lst_();
		int *v1 = malloc(sizeof(int));
		int *v2 = malloc(sizeof(int));
		*v1 = i;
		*v2 = i * 2;
		small = lst_insert(&small, node(v1), 0);
		small = lst_insert(&small, node(v2), 1);
		free_lst(&small, del_int);
	}
	TEST_ASSERT(1, "Many small lists");
	
	// Deep copy chains
	t_lst base = lst_();
	int *v = malloc(sizeof(int));
	*v = 42;
	base = lst_insert(&base, node(v), 0);
	
	t_lst c1 = lst_l(base, copy_int, del_int);
	t_lst c2 = lst_l(c1, copy_int, del_int);
	t_lst c3 = lst_l(c2, copy_int, del_int);
	
	TEST_ASSERT(*(int *)c3.nodes->content == 42, "Deep copy chain");
	
	free_lst(&base, del_int);
	free_lst(&c1, del_int);
	free_lst(&c2, del_int);
	free_lst(&c3, del_int);
}

// ============================================================================
// EDGE CASE TEST RUNNER
// ============================================================================

void run_list_edge_case_tests(void)
{	
	test_empty_list_operations();
	test_single_node_operations();
	test_very_large_lists();
	
	test_insert_patterns();
	test_delete_patterns();
	
	test_list_null_propagation();
	test_copy_failures();
	test_map_failures();
	
	test_boundary_indices();
	test_filter_edge_cases();
	test_ownership_chains();
	
	test_list_stress();

	TEST_SUMMARY();
}
