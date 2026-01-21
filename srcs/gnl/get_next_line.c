/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:26:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 10:40:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gnl.h"
#include "libft_buffer.h"
#include "libft_string.h"
#include <stdio.h>

t_dstr	on_failure(t_readers *readers, t_reader *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader_content);
	free_dbuf(buf);
	return (dstr_s(0));
}

t_dstr	on_file_end(t_readers *readers, t_reader *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader_content);
	return (str_from_buf(buf));
}

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

t_bool	need_to_read(t_reader_content *reader_content)
{
	t_bool	is_first_read;
	t_bool	merged_all;

	is_first_read = (reader_content->start == 0);
	merged_all = reader_content->start >= (size_t)reader_content->read_count;
	return (is_first_read || merged_all);
}

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
