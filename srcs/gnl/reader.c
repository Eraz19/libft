/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:45:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:17:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * is_fd_reader - Predicate to check if a reader matches the given fd
 *
 * @param content The reader content to check
 * @param fd Pointer to the fd to match against
 * @return TRUE if matches, FALSE otherwise
 */
static t_bool	is_fd_reader(void *content, void *fd)
{
	t_i32	fd_;

	fd_ = *(t_i32 *)fd;
	return (((t_reader_content *)content)->fd == fd_);
}

/**
 * select_reader - Selects or creates a reader for the given fd
 *
 * @param readers The list of current readers
 * @param fd The file descriptor to select
 * @return Pointer to the selected or newly created reader
 *
 * @error: On allocation failure, returns NULL (errno ENOMEM).
 */
t_reader	*select_reader(t_readers *readers, t_u32 fd)
{
	size_t		i;
	t_readers	matching_readers;
	t_reader	*new_reader;

	matching_readers = filter(*readers, is_fd_reader, &fd);
	if (matching_readers.nodes != NULL)
		return ((t_reader *)matching_readers.nodes);
	new_reader = malloc(sizeof(t_reader));
	if (new_reader == NULL)
		return (NULL);
	new_reader->content = malloc(sizeof(t_reader_content));
	if (new_reader->content == NULL)
		return (free(new_reader), NULL);
	new_reader->content->fd = (t_i32)fd;
	new_reader->content->read_count = 0;
	new_reader->content->start = 0;
	i = 0;
	while (i < BUF_SIZE)
		new_reader->content->buf[i++] = 0;
	lst_insert(readers, (t_node *)new_reader, 0);
	return (new_reader);
}

/**
 * free_reader_content - Frees the content of a reader
 *
 * @param content Pointer to the reader content to free
 */
void	free_reader_content(void *content)
{
	size_t	i;

	((t_reader_content *)content)->fd = -1;
	((t_reader_content *)content)->read_count = 0;
	((t_reader_content *)content)->start = 0;
	i = 0;
	while (i < BUF_SIZE)
		((t_reader_content *)content)->buf[i++] = 0;
}

/**
 * read_file - Reads data from the file descriptor into the reader's buffer
 *
 * @param reader_content Pointer to the reader content
 * @param fd The file descriptor to read from
 */
void	read_file(t_reader_content *reader_content, t_u32 fd)
{
	reader_content->read_count = read((t_i32)fd, reader_content->buf, BUF_SIZE);
	reader_content->start = 0;
}
