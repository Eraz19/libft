/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl_comprehensive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 13:16:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"
#include <fcntl.h>

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Override TEST_ASSERT and TEST_SUMMARY to use gnl-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT GNL_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY GNL_TEST_SUMMARY

// Test counters
int g_gnl_tests_run = 0;
int g_gnl_tests_passed = 0;
int g_gnl_tests_failed = 0;

// Helper function to create test files
static void create_test_file(const char *filename, const char *content)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		write(fd, content, strlen(content));
		close(fd);
	}
}

// Helper function to compare strings (handles NULL)
static int strings_equal(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	return (strcmp(s1, s2) == 0);
}

// ============================================================================
// BASIC FUNCTIONALITY TESTS
// ============================================================================

void test_gnl_invalid_fd(void)
{
	TEST_START("Invalid file descriptors");
	t_readers readers = {0};
	
	// Very large fd (likely invalid)
	t_dstr result = get_next_line(9999, &readers);
	TEST_ASSERT(result.s == NULL, "Invalid large fd returns NULL");
	free_dstr(&result);
	
	// Closed fd
	int fd = open("test_temp.txt", O_RDONLY | O_CREAT, 0644);
	if (fd >= 0)
	{
		close(fd);
		free_lst(&readers, free_reader_content);
		readers = (t_readers){0};
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "Closed fd returns NULL");
		free_dstr(&result);
		unlink("test_temp.txt");
	}
	free_lst(&readers, free_reader_content);
}

void test_gnl_empty_file(void)
{
	TEST_START("Empty file");
	t_readers readers = {0};
	
	create_test_file("gnl_empty.txt", "");
	
	int fd = open("gnl_empty.txt", O_RDONLY);
	TEST_ASSERT(fd >= 0, "File opened successfully");
	
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "Empty file returns NULL");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "Second read also returns NULL");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_empty.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_single_char(void)
{
	TEST_START("Single character without newline");
	t_readers readers = {0};
	
	create_test_file("gnl_1char.txt", "a");
	
	int fd = open("gnl_1char.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Single char read successfully");
		TEST_ASSERT(strings_equal((char *)result.s, "a"), "Content is 'a'");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "Second read returns NULL");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_1char.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_one_line_no_nl(void)
{
	TEST_START("One line without newline");
	t_readers readers = {0};
	
	create_test_file("gnl_one_line.txt", "abcdefghijklmnopqrstuvwxyz");
	
	int fd = open("gnl_one_line.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Line read successfully");
		TEST_ASSERT(strings_equal((char *)result.s, "abcdefghijklmnopqrstuvwxyz"),
			"Full alphabet read");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "EOF reached");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_one_line.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_only_newline(void)
{
	TEST_START("File with only newline");
	t_readers readers = {0};
	
	create_test_file("gnl_only_nl.txt", "\n");
	
	int fd = open("gnl_only_nl.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s != NULL, "Newline read");
		TEST_ASSERT(strings_equal((char *)result.s, "\n"), "Content is newline");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "EOF after newline");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_only_nl.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_multiple_newlines(void)
{
	TEST_START("Multiple consecutive newlines");
	t_readers readers = {0};
	
	create_test_file("gnl_multi_nl.txt", "\n\n\n\n\n");
	
	int fd = open("gnl_multi_nl.txt", O_RDONLY);
	if (fd >= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			t_dstr result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s != NULL, "Newline read");
			TEST_ASSERT(strings_equal((char *)result.s, "\n"), 
				"Each line is a newline");
			free_dstr(&result);
		}
		
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "EOF after all newlines");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_multi_nl.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// MULTIPLE LINES TESTS
// ============================================================================

void test_gnl_simple_lines(void)
{
	TEST_START("Simple multiple lines");
	t_readers readers = {0};
	
	create_test_file("gnl_lines.txt", "Line 1\nLine 2\nLine 3\n");
	
	int fd = open("gnl_lines.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 1\n"), "First line");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 2\n"), "Second line");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "Line 3\n"), "Third line");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "EOF reached");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_lines.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_variable_newlines(void)
{
	TEST_START("Variable content with newlines");
	t_readers readers = {0};
	
	const char *content = "\n"
		"0123456789012345678901234567890123456789x2\n"
		"0123456789012345678901234567890123456789x3\n"
		"\n"
		"0123456789012345678901234567890123456789x5\n"
		"\n"
		"\n"
		"0123456789012345678901234567890123456789x8\n"
		"\n"
		"\n"
		"\n"
		"0123456789012345678901234567890123456789x12";
	
	create_test_file("gnl_variable.txt", content);
	
	int fd = open("gnl_variable.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result;
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "\n"), "Line 1: empty");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, 
			"0123456789012345678901234567890123456789x2\n"), "Line 2");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, 
			"0123456789012345678901234567890123456789x3\n"), "Line 3");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "\n"), "Line 4: empty");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, 
			"0123456789012345678901234567890123456789x5\n"), "Line 5");
		free_dstr(&result);
		
		// Skip empty lines
		for (int i = 0; i < 2; i++)
		{
			result = get_next_line((t_u32)fd, &readers);
			free_dstr(&result);
		}
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, 
			"0123456789012345678901234567890123456789x8\n"), "Line 8");
		free_dstr(&result);
		
		// Skip remaining empty lines
		for (int i = 0; i < 3; i++)
		{
			result = get_next_line((t_u32)fd, &readers);
			free_dstr(&result);
		}
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, 
			"0123456789012345678901234567890123456789x12"), "Last line no nl");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_variable.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// BUFFER SIZE BOUNDARY TESTS
// ============================================================================

void test_gnl_lines_around_buffer(void)
{
	TEST_START("Lines around BUFFER_SIZE");
	t_readers readers = {0};
	
	create_test_file("gnl_around_buf.txt", 
		"0123456789\n"
		"012345678\n"
		"90123456789\n"
		"0123456789\n"
		"xxxx\n");
	
	int fd = open("gnl_around_buf.txt", O_RDONLY);
	if (fd >= 0)
	{
		t_dstr result;
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "0123456789\n"), "Line 1");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "012345678\n"), "Line 2");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "90123456789\n"), "Line 3");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "0123456789\n"), "Line 4");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(strings_equal((char *)result.s, "xxxx\n"), "Line 5");
		free_dstr(&result);
		
		result = get_next_line((t_u32)fd, &readers);
		TEST_ASSERT(result.s == NULL, "EOF");
		free_dstr(&result);
		
		close(fd);
	}
	unlink("gnl_around_buf.txt");
	free_lst(&readers, free_reader_content);
}

void test_gnl_giant_line(void)
{
	TEST_START("Giant line (10000 chars)");
	t_readers readers = {0};
	
	char *giant = malloc(10001);
	if (giant)
	{
		for (int i = 0; i < 10000; i++)
			giant[i] = '0' + (i % 10);
		giant[10000] = '\0';
		
		create_test_file("gnl_giant.txt", giant);
		
		int fd = open("gnl_giant.txt", O_RDONLY);
		if (fd >= 0)
		{
			t_dstr result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s != NULL, "Giant line read");
			TEST_ASSERT(result.len == 10000, "Correct length");
			TEST_ASSERT(strings_equal((char *)result.s, giant), "Content matches");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s == NULL, "EOF after giant line");
			free_dstr(&result);
			
			close(fd);
		}
		unlink("gnl_giant.txt");
		free(giant);
	}
	free_lst(&readers, free_reader_content);
}

void test_gnl_giant_line_with_nl(void)
{
	TEST_START("Giant line with newline");
	t_readers readers = {0};
	
	char *giant = malloc(10002);
	if (giant)
	{
		for (int i = 0; i < 10000; i++)
			giant[i] = '0' + (i % 10);
		giant[10000] = '\n';
		giant[10001] = '\0';
		
		char second_line[] = "another line!!!";
		
		int fd = open("gnl_giant_nl.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			write(fd, giant, 10001);
			write(fd, second_line, strlen(second_line));
			close(fd);
		}
		
		fd = open("gnl_giant_nl.txt", O_RDONLY);
		if (fd >= 0)
		{
			t_dstr result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s != NULL, "First line read");
			TEST_ASSERT(result.len == 10001, "Correct length with nl");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(strings_equal((char *)result.s, second_line), "Second line");
			free_dstr(&result);
			
			result = get_next_line((t_u32)fd, &readers);
			TEST_ASSERT(result.s == NULL, "EOF");
			free_dstr(&result);
			
			close(fd);
		}
		unlink("gnl_giant_nl.txt");
		free(giant);
	}
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// MULTIPLE FILE DESCRIPTORS TEST
// ============================================================================

void test_gnl_multiple_fds(void)
{
	TEST_START("Multiple file descriptors");
	t_readers readers = {0};
	
	create_test_file("gnl_fd1.txt", "File1 Line1\nFile1 Line2\nFile1 Line3\n");
	create_test_file("gnl_fd2.txt", "File2 Line1\nFile2 Line2\n");
	create_test_file("gnl_fd3.txt", "File3 Line1\n");
	
	int fd1 = open("gnl_fd1.txt", O_RDONLY);
	int fd2 = open("gnl_fd2.txt", O_RDONLY);
	int fd3 = open("gnl_fd3.txt", O_RDONLY);
	
	if (fd1 >= 0 && fd2 >= 0 && fd3 >= 0)
	{
		t_dstr r1, r2, r3;
		
		// Read from fd1
		r1 = get_next_line((t_u32)fd1, &readers);
		TEST_ASSERT(strings_equal((char *)r1.s, "File1 Line1\n"), "FD1 Line1");
		free_dstr(&r1);
		
		// Read from fd2
		r2 = get_next_line((t_u32)fd2, &readers);
		TEST_ASSERT(strings_equal((char *)r2.s, "File2 Line1\n"), "FD2 Line1");
		free_dstr(&r2);
		
		// Read from fd3
		r3 = get_next_line((t_u32)fd3, &readers);
		TEST_ASSERT(strings_equal((char *)r3.s, "File3 Line1\n"), "FD3 Line1");
		free_dstr(&r3);
		
		// Back to fd1
		r1 = get_next_line((t_u32)fd1, &readers);
		TEST_ASSERT(strings_equal((char *)r1.s, "File1 Line2\n"), "FD1 Line2");
		free_dstr(&r1);
		
		// Back to fd2
		r2 = get_next_line((t_u32)fd2, &readers);
		TEST_ASSERT(strings_equal((char *)r2.s, "File2 Line2\n"), "FD2 Line2");
		free_dstr(&r2);
		
		// FD3 should be at EOF
		r3 = get_next_line((t_u32)fd3, &readers);
		TEST_ASSERT(r3.s == NULL, "FD3 EOF");
		free_dstr(&r3);
		
		// Continue with fd1
		r1 = get_next_line((t_u32)fd1, &readers);
		TEST_ASSERT(strings_equal((char *)r1.s, "File1 Line3\n"), "FD1 Line3");
		free_dstr(&r1);
		
		close(fd1);
		close(fd2);
		close(fd3);
	}
	
	unlink("gnl_fd1.txt");
	unlink("gnl_fd2.txt");
	unlink("gnl_fd3.txt");
	free_lst(&readers, free_reader_content);
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_gnl_comprehensive_tests(void)
{
	// Basic tests
	TEST_WITH_TIMEOUT(test_gnl_invalid_fd, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_empty_file, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_single_char, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_one_line_no_nl, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_only_newline, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_multiple_newlines, TEST_TIMEOUT_SECONDS);
	
	// Multiple lines
	TEST_WITH_TIMEOUT(test_gnl_simple_lines, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_variable_newlines, TEST_TIMEOUT_SECONDS);
	
	// Buffer boundary tests
	TEST_WITH_TIMEOUT(test_gnl_lines_around_buffer, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_giant_line, TEST_TIMEOUT_SECONDS);
	TEST_WITH_TIMEOUT(test_gnl_giant_line_with_nl, TEST_TIMEOUT_SECONDS);
	
	// Multiple FDs
	TEST_WITH_TIMEOUT(test_gnl_multiple_fds, TEST_TIMEOUT_SECONDS);
	
	GNL_TEST_SUMMARY();
}
