/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:53:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:04:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GNL_H
# define LIBFT_GNL_H

# include "libft_list.h"
# include "libft_string.h"

typedef struct t_reader_content
{
	t_i32			fd;
	t_u8			buf[BUF_SIZE];
	ssize_t			read_count;
	size_t			start;
}	t_reader_content;
typedef struct t_reader
{
	t_reader_content	*content;
	struct t_reader		*next;
}	t_reader;
typedef t_lst	t_readers;

t_dstr	get_next_line(t_u32 fd, t_readers *readers);

void	free_reader_content(void *content);

#endif