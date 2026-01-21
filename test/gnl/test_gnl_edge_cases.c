/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl_edge_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 13:16:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * GET_NEXT_LINE - EDGE CASE AND ERROR HANDLING TESTS
 * 
 * This file tests:
 * - Binary files and special characters
 * - Very long lines
 * - Mixed line lengths
 * - Memory management edge cases
 * - Reopening files
 * - Stdin handling
 */

#include "libft_test.h"
#include "libft.h"
#include <fcntl.h>

#include <string.h>
#include <unistd.h>

// Override TEST_ASSERT and TEST_SUMMARY
#undef TEST_ASSERT
#define TEST_ASSERT GNL_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY GNL_TEST_SUMMARY

// Test counters (shared from test_gnl_comprehensive.c)
extern int g_gnl_tests_run;
extern int g_gnl_tests_passed;
extern int g_gnl_tests_failed;

// Helper functions
static void create_test_file(const char *filename, const char *content)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		write(fd, content, strlen(content));
		close(fd);
	}
}

static int strings_equal(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	return (strcmp(s1, s2) == 0);
}

// ============================================================================
// SPECIAL CHARACTERS TESTS
// ============================================================================

void test_gnl_special_chars(void)
{
	TEST_START("Special characters in content");
	t_readers readers = {0};
	
	create_test_file("gnl_special.txt", 
		"Line with\ttabs\there\n"
		"Line with\rnull\n"
		"Line with special: !@#$%^&*()\n");
	
	int fd = open("gnl_special.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result;
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Tab line read");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "CR line read");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Special chars line read");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_special.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_binary_content(void)
{
	TEST_START("Binary content with null bytes");
	t_readers readers = {0};
	
	int fd = open("gnl_binary.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		// Write binary data with null bytes
		char binary[] = {'a', 'b', '\0', 'c', 'd', '\n', 'e', 'f', '\n'};
		write(fd, binary, 9);
		close(fd);
	}
	
	fd = open("gnl_binary.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result;
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Binary line 1 read");
		// Note: Behavior with null bytes may vary
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Binary line 2 read");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_binary.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// EXTREME LENGTH TESTS
// ============================================================================

void test_gnl_very_long_line(void)
{
	TEST_START("Very long line (100,000 chars)");
	t_readers readers = {0};
	
	char *giant = malloc(100001);
	if (giant)
	{
		for (int i = 0; i < 100000; i++)
			giant[i] = 'A' + (i % 26);
		giant[100000] = '\0';
		
		create_test_file("gnl_verylong.txt", giant);
		
		int fd = open("gnl_verylong.txt", O_RDONLY);
		if (fd >= 0)
		{
			t_dstr result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s != NULL, "Very long line read");
			TEST_ASSERT(result.len == 100000, "Correct length");
			free_dstr(&result);
			
			close(fd);
		}
		unlink("gnl_verylong.txt");
		free(giant);
	}
	free_lst(&readers, free_reader_content);
}

void test_gnl_mixed_line_lengths(void)
{
	TEST_START("Mixed very short and very long lines");
	t_readers readers = {0};
	
	char *content = malloc(50000);
	if (content)
	{
		int offset = 0;
		
		// Short line
		offset += sprintf(content + offset, "a\n");
		
		// Long line
		for (int i = 0; i < 10000; i++)
			content[offset++] = 'b';
		content[offset++] = '\n';
		
		// Very short
		offset += sprintf(content + offset, "c\n");
		
		// Medium line
		for (int i = 0; i < 500; i++)
			content[offset++] = 'd';
		content[offset++] = '\n';
		
		content[offset] = '\0';
		
		create_test_file("gnl_mixed.txt", content);
		
		int fd = open("gnl_mixed.txt", O_RDONLY);
		if (fd >= 0)
		{
			t_dstr result;
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == 2, "Short line correct");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == 10001, "Long line correct");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == 2, "Short line 2 correct");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == 501, "Medium line correct");
			free_dstr(&result);
			
			close(fd);
		}
		unlink("gnl_mixed.txt");
		free(content);
	}
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// FILE REOPEN TESTS
// ============================================================================

void test_gnl_reopen_file(void)
{
	TEST_START("Reopening and rereading file");
	t_readers readers = {0};
	
	create_test_file("gnl_reopen.txt", "Line 1\nLine 2\nLine 3\n");
	
	// First read session
	int fd = open("gnl_reopen.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 1\n"), "First session line 1");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 2\n"), "First session line 2");
		free_dstr(&result);
		
		close(fd);
	}
	
	free_lst(&readers, free_reader_content);
	readers = (t_readers){0};
	
	// Reopen and read again
	fd = open("gnl_reopen.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 1\n"), "Second session line 1");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 2\n"), "Second session line 2");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 3\n"), "Second session line 3");
		free_dstr(&result);
		
		close(fd);
	}
	
	unlink("gnl_reopen.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// ALTERNATING FD TESTS
// ============================================================================

void test_gnl_alternating_fds(void)
{
	TEST_START("Rapidly alternating between FDs");
	t_readers readers = {0};
	
	create_test_file("gnl_alt1.txt", "A1\nA2\nA3\nA4\nA5\n");
	create_test_file("gnl_alt2.txt", "B1\nB2\nB3\nB4\nB5\n");
	
	int fd1 = open("gnl_alt1.txt", O_RDONLY);
	int fd2 = open("gnl_alt2.txt", O_RDONLY);
	
	if (fd1 >= 0 && fd2 >= 0)
	{
		// Alternate between files
		for (int i = 1; i <= 5; i++)
		{
			t_dstr r1 = get_next_line((t_u32)fd1, &readers);
			char expected1[10];
			sprintf(expected1, "A%d\n", i);
			TEST_ASSERT(strings_equal((char *)r1.s, expected1), "Alternating A line");
			free_dstr(&r1);
			
			t_dstr r2 = get_next_line((t_u32)fd2, &readers);
			char expected2[10];
			sprintf(expected2, "B%d\n", i);
			TEST_ASSERT(strings_equal((char *)r2.s, expected2), "Alternating B line");
			free_dstr(&r2);
		}
		
		close(fd1);
		close(fd2);
	}
	
	unlink("gnl_alt1.txt");
	unlink("gnl_alt2.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// MEMORY STRESS TESTS
// ============================================================================

void test_gnl_many_reads(void)
{
	TEST_START("Many consecutive reads");
	t_readers readers = {0};
	
	// Create file with 100 lines
	int fd = open("gnl_many.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		for (int i = 0; i < 100; i++)
		{
			char line[50];
			sprintf(line, "Line number %d\n", i);
			write(fd, line, strlen(line));
		}
		close(fd);
	}
	
	fd = open("gnl_many.txt", O_RDONLY);
	if (fd >= 0)
	{
		int count = 0;
		t_dstr result;
		
		while (1)
		{
			result = get_next_line((t_u32)fd, &readers);
			if (result.s == NULL)
				break;
			count++;
			free_dstr(&result);
		}
		
		TEST_ASSERT(count == 100, "Read all 100 lines");
		
		close(fd);
	}
	unlink("gnl_many.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_many_fds(void)
{
	TEST_START("Multiple file descriptors simultaneously");
	t_readers readers = {0};
	
	int fds[10];
	char filenames[10][30];
	
	// Create and open 10 files
	for (int i = 0; i < 10; i++)
	{
		sprintf(filenames[i], "gnl_multi_%d.txt", i);
		char content[50];
		sprintf(content, "File %d Line 1\nFile %d Line 2\n", i, i);
		create_test_file(filenames[i], content);
		fds[i] = open(filenames[i], O_RDONLY);
	}
	
	// Read first line from each
	int success = 1;
	for (int i = 0; i < 10; i++)
	{
		if (fds[i] >= 0)
		{
			t_dstr result = get_next_line((t_u32)(fds[i]), &readers);
			if (result.s == NULL)
				success = 0;
			free_dstr(&result);
		}
	}
	TEST_ASSERT(success, "Read from all 10 files");
	
	// Read second line from each
	success = 1;
	for (int i = 0; i < 10; i++)
	{
		if (fds[i] >= 0)
		{
			t_dstr result = get_next_line((t_u32)(fds[i]), &readers);
			if (result.s == NULL)
				success = 0;
			free_dstr(&result);
		}
	}
	TEST_ASSERT(success, "Read second line from all files");
	
	// Clean up
	for (int i = 0; i < 10; i++)
	{
		if (fds[i] >= 0)
			close(fds[i]);
		unlink(filenames[i]);
	}
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// BOUNDARY CONDITION TESTS
// ============================================================================

void test_gnl_exact_buffer_size_lines(void)
{
	TEST_START("Lines exactly at BUFFER_SIZE boundaries");
	t_readers readers = {0};
	
	char *line1 = malloc(BUF_SIZE + 2);
	char *line2 = malloc(BUF_SIZE - 1 + 2);
	char *line3 = malloc(BUF_SIZE + 1 + 2);
	
	if (line1 && line2 && line3)
	{
		// Line exactly BUFFER_SIZE
		for (int i = 0; i < BUF_SIZE; i++)
			line1[i] = 'A';
		line1[BUF_SIZE] = '\n';
		line1[BUF_SIZE + 1] = '\0';
		
		// Line BUFFER_SIZE - 1
		for (int i = 0; i < BUF_SIZE - 1; i++)
			line2[i] = 'B';
		line2[BUF_SIZE - 1] = '\n';
		line2[BUF_SIZE] = '\0';
		
		// Line BUFFER_SIZE + 1
		for (int i = 0; i < BUF_SIZE + 1; i++)
			line3[i] = 'C';
		line3[BUF_SIZE + 1] = '\n';
		line3[BUF_SIZE + 2] = '\0';
		
		int fd = open("gnl_boundary.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			write(fd, line1, strlen(line1));
			write(fd, line2, strlen(line2));
			write(fd, line3, strlen(line3));
			close(fd);
		}
		
		fd = open("gnl_boundary.txt", O_RDONLY);
		if (fd >= 0)
		{
			t_dstr result;
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == BUF_SIZE + 1, "Exact BUFFER_SIZE line");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == BUF_SIZE, "BUFFER_SIZE - 1 line");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.len == BUF_SIZE + 2, "BUFFER_SIZE + 1 line");
			free_dstr(&result);
			
			close(fd);
		}
		unlink("gnl_boundary.txt");
		
		free(line1);
		free(line2);
		free(line3);
	}
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// EDGE CASE TEST RUNNER
// ============================================================================

void run_gnl_edge_case_tests(void)
{
	TEST_WITH_TIMEOUT(test_gnl_special_chars, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_binary_content, TEST_TIMEOUT_SECONDS);
	
	TEST_WITH_TIMEOUT(test_gnl_very_long_line, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_mixed_line_lengths, TEST_TIMEOUT_SECONDS);
	
	TEST_WITH_TIMEOUT(test_gnl_reopen_file, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_alternating_fds, TEST_TIMEOUT_SECONDS);
	
	TEST_WITH_TIMEOUT(test_gnl_many_reads, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_many_fds, TEST_TIMEOUT_SECONDS);
	
	TEST_WITH_TIMEOUT(test_gnl_exact_buffer_size_lines, TEST_TIMEOUT_SECONDS);
	
	GNL_TEST_SUMMARY();
}
