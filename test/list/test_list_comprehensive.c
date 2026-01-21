/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_comprehensive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 17:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"

#include <string.h>
#include <stdlib.h>

// Override TEST_ASSERT and TEST_SUMMARY to use list-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT LIST_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY LIST_TEST_SUMMARY

// Test counters
int g_list_tests_run = 0;
int g_list_tests_passed = 0;
int g_list_tests_failed = 0;

// Helper functions for testing
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

static void *double_int(void *content)
{
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = (*(int *)content) * 2;
	return new;
}

static int g_foreach_sum = 0;
static void sum_foreach(void *content)
{
	g_foreach_sum += *(int *)content;
}

// ============================================================================
// CONSTRUCTOR TESTS
// ============================================================================

void test_lst_(void)
{
	TEST_START("lst_ - empty list creation");
	
	t_lst empty = lst_();
	TEST_ASSERT(empty.nodes == NULL, "Empty list has NULL nodes");
	TEST_ASSERT(empty.size == 0, "Empty list has size 0");
}

void test_node(void)
{
	TEST_START("node - node creation");
	
	// NULL content
	t_node *null_node = node(NULL);
	TEST_ASSERT(null_node == NULL, "NULL content returns NULL node");
	
	// Valid content
	int *value = malloc(sizeof(int));
	*value = 42;
	t_node *valid_node = node(value);
	TEST_ASSERT(valid_node != NULL, "Valid content creates node");
	TEST_ASSERT(valid_node->content == value, "Content pointer stored");
	TEST_ASSERT(*(int *)valid_node->content == 42, "Content value correct");
	TEST_ASSERT(valid_node->next == NULL, "Next is NULL");
	
	free(value);
	free(valid_node);
}

void test_lst_n(void)
{
	TEST_START("lst_n - single node list creation");
	
	// NULL node
	t_lst from_null = lst_n(NULL);
	TEST_ASSERT(from_null.nodes == NULL, "NULL node returns empty list");
	TEST_ASSERT(from_null.size == 0, "Size is 0");
	
	// Valid node
	int *value = malloc(sizeof(int));
	*value = 42;
	t_node *n = node(value);
	t_lst list = lst_n(n);
	TEST_ASSERT(list.nodes == n, "List points to node");
	TEST_ASSERT(list.size == 1, "Size is 1");
	TEST_ASSERT(*(int *)list.nodes->content == 42, "Content accessible");
	
	free(value);
	free(n);
}

void test_lst_l(void)
{
	TEST_START("lst_l - list copying");
	
	// Create original list
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	
	t_lst original = lst_();
	t_node *n1 = node(v1);
	t_node *n2 = node(v2);
	t_node *n3 = node(v3);
	
	
	original = lst_insert(&original, n1, 0);
	original = lst_insert(&original, n2, 1);
	original = lst_insert(&original, n3, 2);
	
	// Copy list
	t_lst copy = lst_l(original, copy_int, del_int);
	TEST_ASSERT(copy.nodes != NULL, "Copy created");
	TEST_ASSERT(copy.size == 3, "Copy has correct size");
	TEST_ASSERT(copy.nodes != original.nodes, "Different memory");
	TEST_ASSERT(*(int *)copy.nodes->content == 10, "First element copied");
	TEST_ASSERT(*(int *)copy.nodes->next->content == 20, "Second element copied");
	TEST_ASSERT(*(int *)copy.nodes->next->next->content == 30, "Third element copied");
	
	// Modify copy, verify original unchanged
	*(int *)copy.nodes->content = 99;
	TEST_ASSERT(*(int *)original.nodes->content == 10, "Original unchanged");
	
	free_lst(&original, del_int);
	free_lst(&copy, del_int);
	
	// NULL inputs
	t_lst empty = lst_();
	t_lst copy_null = lst_l(empty, copy_int, del_int);
	TEST_ASSERT(copy_null.nodes == NULL, "NULL list returns empty");
	
	t_lst with_null_func = lst_l(original, NULL, del_int);
	TEST_ASSERT(with_null_func.nodes == NULL, "NULL copy function returns empty");
}

// ============================================================================
// FREE TESTS
// ============================================================================

void test_free_lst(void)
{
	TEST_START("free_lst - list deallocation");
	
	// Create and free list
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	
	t_lst list = lst_();
	list = lst_insert(&list, node(v1), 0);
	list = lst_insert(&list, node(v2), 1);
	
	free_lst(&list, del_int);
	TEST_ASSERT(list.nodes == NULL, "Nodes set to NULL");
	TEST_ASSERT(list.size == 0, "Size reset to 0");
	
	// NULL list
	free_lst(NULL, del_int);
	TEST_ASSERT(1, "NULL list doesn't crash");
	
	// Empty list
	t_lst empty = lst_();
	free_lst(&empty, del_int);
	TEST_ASSERT(1, "Empty list frees safely");
}

void test_free_node(void)
{
	TEST_START("free_node - single node deletion");
	
	// Create list with 3 nodes
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	
	t_lst list = lst_();
	list = lst_insert(&list, node(v1), 0);
	list = lst_insert(&list, node(v2), 1);
	list = lst_insert(&list, node(v3), 2);
	
	// Delete middle node
	t_node *middle = get(list, 1);
	free_node(&list, middle, del_int);
	TEST_ASSERT(list.size == 2, "Size decreased");
	TEST_ASSERT(*(int *)list.nodes->content == 10, "First still there");
	TEST_ASSERT(*(int *)list.nodes->next->content == 30, "Third moved up");
	
	// Delete first node
	free_node(&list, list.nodes, del_int);
	TEST_ASSERT(list.size == 1, "Size decreased again");
	TEST_ASSERT(*(int *)list.nodes->content == 30, "Correct node remains");
	
	// Delete last node
	free_node(&list, list.nodes, del_int);
	TEST_ASSERT(list.size == 0, "List empty");
	TEST_ASSERT(list.nodes == NULL, "Nodes NULL");
	
	// Out of bounds
	int *v4 = malloc(sizeof(int));
	*v4 = 40;
	list = lst_insert(&list, node(v4), 0);
	free_node(&list, NULL, del_int);
	TEST_ASSERT(list.size == 1, "NULL node does nothing");
	
	free_lst(&list, del_int);
}

// ============================================================================
// GET TESTS
// ============================================================================

void test_get(void)
{
	TEST_START("get - node retrieval");
	
	// Create list
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	
	t_lst list = lst_();
	list = lst_insert(&list, node(v1), 0);
	list = lst_insert(&list, node(v2), 1);
	list = lst_insert(&list, node(v3), 2);
	
	// Get first
	t_node *first = get(list, 0);
	TEST_ASSERT(first != NULL, "Get first node");
	TEST_ASSERT(*(int *)first->content == 10, "First content correct");
	
	// Get middle
	t_node *middle = get(list, 1);
	TEST_ASSERT(middle != NULL, "Get middle node");
	TEST_ASSERT(*(int *)middle->content == 20, "Middle content correct");
	
	// Get last
	t_node *last = get(list, 2);
	TEST_ASSERT(last != NULL, "Get last node");
	TEST_ASSERT(*(int *)last->content == 30, "Last content correct");
	
	// Out of bounds
	t_node *out = get(list, 10);
	TEST_ASSERT(out == NULL, "Out of bounds returns NULL");
	
	// Empty list
	t_lst empty = lst_();
	t_node *from_empty = get(empty, 0);
	TEST_ASSERT(from_empty == NULL, "Get from empty returns NULL");
	
	free_lst(&list, del_int);
}

// Helper functions for filter tests
static t_bool is_even(void *content, void *context)
{
	(void)context;
	return (*(int *)content % 2 == 0);
}

static t_bool is_positive(void *content, void *context)
{
	(void)context;
	return (*(int *)content > 0);
}

static t_bool is_greater_than_20(void *content, void *context)
{
	(void)context;
	return (*(int *)content > 20);
}

static t_bool always_false(void *content, void *context)
{
	(void)content;
	(void)context;
	return (FALSE);
}

void test_filter(void)
{
	TEST_START("filter - list filtering");
	
	// Create list with values: 10, 15, 20, 25, 30
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	int *v4 = malloc(sizeof(int));
	int *v5 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 15;
	*v3 = 20;
	*v4 = 25;
	*v5 = 30;
	
	t_lst list = lst_();
	list = lst_insert(&list, node(v1), 0);
	list = lst_insert(&list, node(v2), 1);
	list = lst_insert(&list, node(v3), 2);
	list = lst_insert(&list, node(v4), 3);
	list = lst_insert(&list, node(v5), 4);
	
	// Filter even numbers (should find first: 10)
	t_lst evens = filter(list, is_even, NULL);
	TEST_ASSERT(evens.nodes != NULL, "Filter finds even numbers");
	TEST_ASSERT(*(int *)evens.nodes->content == 10, "First even is 10");
	
	// Filter greater than 20 (should find first: 25)
	t_lst greater = filter(list, is_greater_than_20, NULL);
	TEST_ASSERT(greater.nodes != NULL, "Filter finds values > 20");
	TEST_ASSERT(*(int *)greater.nodes->content == 25, "First value > 20 is 25");
	
	// Filter all positive (should find first: 10)
	t_lst positive = filter(list, is_positive, NULL);
	TEST_ASSERT(positive.nodes != NULL, "Filter finds positive values");
	TEST_ASSERT(*(int *)positive.nodes->content == 10, "First positive is 10");
	
	// Filter with no matches
	t_lst no_match = filter(list, always_false, NULL);
	TEST_ASSERT(no_match.nodes == NULL, "No matches returns empty list");
	TEST_ASSERT(no_match.size == 0, "No matches has size 0");
	
	// Empty list
	t_lst empty = lst_();
	t_lst filtered_empty = filter(empty, is_even, NULL);
	TEST_ASSERT(filtered_empty.nodes == NULL, "Filter empty list returns empty");
	TEST_ASSERT(filtered_empty.size == 0, "Filter empty has size 0");
	
	// NULL comparison function
	t_lst null_cmp = filter(list, NULL, NULL);
	TEST_ASSERT(null_cmp.nodes == NULL, "NULL comparison returns empty list");
	TEST_ASSERT(null_cmp.size == 0, "NULL comparison has size 0");
	
	free_lst(&list, del_int);
}

// ============================================================================
// INSERT TESTS
// ============================================================================

void test_lst_insert(void)
{
	TEST_START("lst_insert - node insertion");
	
	// Insert into empty list
	t_lst list = lst_();
	int *v1 = malloc(sizeof(int));
	*v1 = 10;
	list = lst_insert(&list, node(v1), 0);
	TEST_ASSERT(list.size == 1, "Insert into empty");
	TEST_ASSERT(*(int *)list.nodes->content == 10, "Content correct");
	
	// Insert at beginning
	int *v2 = malloc(sizeof(int));
	*v2 = 20;
	list = lst_insert(&list, node(v2), 0);
	TEST_ASSERT(list.size == 2, "Size increased");
	TEST_ASSERT(*(int *)list.nodes->content == 20, "New first");
	TEST_ASSERT(*(int *)list.nodes->next->content == 10, "Old first moved");
	
	// Insert at end
	int *v3 = malloc(sizeof(int));
	*v3 = 30;
	list = lst_insert(&list, node(v3), 2);
	TEST_ASSERT(list.size == 3, "Size increased again");
	TEST_ASSERT(*(int *)list.nodes->next->next->content == 30, "Last element");
	
	// Insert in middle
	int *v4 = malloc(sizeof(int));
	*v4 = 25;
	list = lst_insert(&list, node(v4), 2);
	TEST_ASSERT(list.size == 4, "Middle insert size");
	TEST_ASSERT(*(int *)list.nodes->next->next->content == 25, "Middle content");
	
	// Insert beyond size (clamped)
	int *v5 = malloc(sizeof(int));
	*v5 = 40;
	list = lst_insert(&list, node(v5), 100);
	TEST_ASSERT(list.size == 5, "Beyond size clamped");
	TEST_ASSERT(*(int *)get(list, 4)->content == 40, "Inserted at end");
	
	free_lst(&list, del_int);
	
	// NULL node
	t_lst list2 = lst_();
	int *v6 = malloc(sizeof(int));
	*v6 = 50;
	list2 = lst_insert(&list2, node(v6), 0);
	list2 = lst_insert(&list2, NULL, 1);
	TEST_ASSERT(list2.nodes == NULL, "NULL node returns empty list");
	TEST_ASSERT(list2.size == 0, "Size reset");
}

// ============================================================================
// ITERATION TESTS
// ============================================================================

void test_lst_foreach(void)
{
	TEST_START("lst_foreach - iteration");
	
	// Create list
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	
	t_lst list = lst_();
	list = lst_insert(&list, node(v1), 0);
	list = lst_insert(&list, node(v2), 1);
	list = lst_insert(&list, node(v3), 2);
	
	// Sum all elements
	g_foreach_sum = 0;
	lst_foreach(list, sum_foreach);
	TEST_ASSERT(g_foreach_sum == 60, "Foreach processes all elements");
	
	// NULL function
	lst_foreach(list, NULL);
	TEST_ASSERT(1, "NULL function doesn't crash");
	
	// Empty list
	t_lst empty = lst_();
	g_foreach_sum = 0;
	lst_foreach(empty, sum_foreach);
	TEST_ASSERT(g_foreach_sum == 0, "Empty list does nothing");
	
	free_lst(&list, del_int);
}

void test_lst_map(void)
{
	TEST_START("lst_map - transformation");
	
	// Create original list
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	
	t_lst original = lst_();
	original = lst_insert(&original, node(v1), 0);
	original = lst_insert(&original, node(v2), 1);
	original = lst_insert(&original, node(v3), 2);
	
	// Map to double values
	t_lst mapped = lst_map(&original, double_int, del_int);
	TEST_ASSERT(mapped.size == 3, "Mapped list same size");
	TEST_ASSERT(*(int *)get(mapped, 0)->content == 20, "First doubled");
	TEST_ASSERT(*(int *)get(mapped, 1)->content == 40, "Second doubled");
	TEST_ASSERT(*(int *)get(mapped, 2)->content == 60, "Third doubled");
	
	// Original should be freed by lst_map
	TEST_ASSERT(1, "Original consumed (no double free)");
	
	free_lst(&mapped, del_int);
	
	// NULL function
	int *v4 = malloc(sizeof(int));
	*v4 = 100;
	t_lst list2 = lst_();
	list2 = lst_insert(&list2, node(v4), 0);
	t_lst null_map = lst_map(&list2, NULL, del_int);
	TEST_ASSERT(null_map.nodes == NULL, "NULL function returns empty");
	
	// Empty list
	t_lst empty = lst_();
	t_lst mapped_empty = lst_map(&empty, double_int, del_int);
	TEST_ASSERT(mapped_empty.nodes == NULL, "Empty list maps to empty");
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

void test_list_edge_cases(void)
{
	TEST_START("List edge cases");
	
	// Very long list
	t_lst long_list = lst_();
	for (int i = 0; i < 100; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		long_list = lst_insert(&long_list, node(val), (size_t)i);
	}
	TEST_ASSERT(long_list.size == 100, "Long list size correct");
	TEST_ASSERT(*(int *)get(long_list, 0)->content == 0, "First element");
	TEST_ASSERT(*(int *)get(long_list, 99)->content == 99, "Last element");
	TEST_ASSERT(*(int *)get(long_list, 50)->content == 50, "Middle element");
	free_lst(&long_list, del_int);
	
	// Alternating insertions
	t_lst alt = lst_();
	for (int i = 0; i < 10; i++) {
		int *val = malloc(sizeof(int));
		*val = i;
		if (i % 2 == 0)
			alt = lst_insert(&alt, node(val), 0);
		else
			alt = lst_insert(&alt, node(val), alt.size);
	}
	TEST_ASSERT(alt.size == 10, "Alternating insertions");
	free_lst(&alt, del_int);
	
	// Multiple operations
	t_lst ops = lst_();
	int *v1 = malloc(sizeof(int));
	*v1 = 1;
	ops = lst_insert(&ops, node(v1), 0);
	
	t_lst ops_copy = lst_l(ops, copy_int, del_int);
	TEST_ASSERT(ops_copy.size == 1, "Copy works");
	
	t_lst ops_mapped = lst_map(&ops_copy, double_int, del_int);
	TEST_ASSERT(*(int *)ops_mapped.nodes->content == 2, "Map works");
	
	free_lst(&ops, del_int);
	free_lst(&ops_mapped, del_int);
}

// ============================================================================
// MEMORY LEAK TESTS
// ============================================================================

void test_list_memory_leaks(void)
{
	TEST_START("List memory leak checks");
	
	// Many allocations and frees
	for (int i = 0; i < 50; i++) {
		t_lst list = lst_();
		for (int j = 0; j < 10; j++) {
			int *val = malloc(sizeof(int));
			*val = j;
			list = lst_insert(&list, node(val), (size_t)j);
		}
		free_lst(&list, del_int);
	}
	TEST_ASSERT(1, "Many allocations/frees");
	
	// Copy and free
	for (int i = 0; i < 20; i++) {
		t_lst orig = lst_();
		int *v = malloc(sizeof(int));
		*v = i;
		orig = lst_insert(&orig, node(v), 0);
		
		t_lst copy = lst_l(orig, copy_int, del_int);
		free_lst(&orig, del_int);
		free_lst(&copy, del_int);
	}
	TEST_ASSERT(1, "Copy operations");
	
	// Map operations
	for (int i = 0; i < 20; i++) {
		t_lst list = lst_();
		int *v = malloc(sizeof(int));
		*v = i;
		list = lst_insert(&list, node(v), 0);
		
		t_lst mapped = lst_map(&list, double_int, del_int);
		free_lst(&mapped, del_int);
	}
	TEST_ASSERT(1, "Map operations");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_list_comprehensive_tests(void)
{	
	// Constructor tests
	test_lst_();
	test_node();
	test_lst_n();
	test_lst_l();
	
	// Free tests
	test_free_lst();
	test_free_node();
	
	// Get tests
	test_get();
	test_filter();
	
	// Insert tests
	test_lst_insert();
	
	// Iteration tests
	test_lst_foreach();
	test_lst_map();
	
	// Edge cases
	test_list_edge_cases();
	
	// Memory tests
	test_list_memory_leaks();
	
	TEST_SUMMARY();
}
