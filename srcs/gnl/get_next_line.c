/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:26:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:30:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * on_failure - Handles cleanup on read failure
 *
 * @param readers The list of current readers
 * @param reader The reader that encountered the failure
 * @param buf The buffer containing data from previous reads to free
 * @return A NULL t_dstr indicating failure
 */
t_dstr	on_failure(t_readers *readers, t_reader *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader_content);
	free_dbuf(buf);
	return (dstr_s(0));
}

/**
 * on_file_end - Handles cleanup on end-of-file
 *
 * @param readers The list of current readers
 * @param reader The reader that reached EOF
 * @param buf The buffer containing data from previous reads to convert
 * @return A t_dstr containing any remaining data before EOF
 */
t_dstr	on_file_end(t_readers *readers, t_reader *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader_content);
	return (str_from_buf(buf));
}

/**
 * merge_buffer - Merges data from the reader's buffer into the output buffer
 *
 * @param reader_content Pointer to the reader content
 * @param buf Pointer to the output buffer to merge into
 * @return The updated output buffer
 */
t_dbuf	merge_buffer(t_reader_content *reader_content, t_dbuf *buf)
{
	t_cbuf	buf_;
	ssize_t	buf_size;

	buf_size = reader_content->read_count - (ssize_t)reader_content->start;
	buf_ = cbuf(reader_content->buf + reader_content->start, (size_t)buf_size);
	buf_size = buf_findindex(buf_, cbuf("\n", 1));
	if (buf_size == -1)
		buf_size = (ssize_t)buf_.size;
	else
		buf_size += 1;
	buf_.size = (size_t)buf_size;
	*buf = buf_insertc(buf, buf_, buf->size, x2);
	reader_content->start = reader_content->start + (size_t)buf_size;
	return (*buf);
}

/**
 * need_to_read - Determines if more data needs to be read from the file
 *
 * @param reader_content Pointer to the reader content
 * @return TRUE if more data needs to be read, FALSE otherwise
 */
t_bool	need_to_read(t_reader_content *reader_content)
{
	t_bool	is_first_read;
	t_bool	merged_all;

	is_first_read = (reader_content->start == 0);
	merged_all = reader_content->start >= (size_t)reader_content->read_count;
	return (is_first_read || merged_all);
}

/**

 * get_next_line - Reads the next line from the given file descriptor
 *
 * @param fd The file descriptor to read from
 * @param readers The list of current readers
 * @return A t_dstr containing the next line
 *
 * @error: On reading failure, returns a NULL t_dstr (errno EBADF/EIO/EAGAIN).
 *         On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	get_next_line(t_u32 fd, t_readers *readers)
{
	t_dbuf				buf;
	t_reader			*reader;
	t_reader_content	*reader_content;

	1 && (buf = dbuf_s(0), reader = select_reader(readers, fd));
	if (reader->content == NULL)
		return (free_lst(readers, free_reader_content), dstr_s(0));
	reader_content = reader->content;
	while (TRUE)
	{
		if (need_to_read(reader_content))
		{
			read_file(reader_content, fd);
			if (reader_content->read_count == 0)
				return (on_file_end(readers, reader, &buf));
			else if (reader_content->read_count == -1 && errno != EINTR)
				return (on_failure(readers, reader, &buf));
		}
		buf = merge_buffer(reader_content, &buf);
		if (buf.data == NULL)
			return (on_failure(readers, reader, &buf));
		else if (buf_findindex(cbuf(buf.data, buf.len), cbuf("\n", 1)) != -1)
			return (str_from_buf(&buf));
	}
}
