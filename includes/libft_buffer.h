/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:41:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 14:30:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BUFFER_H
# define LIBFT_BUFFER_H

# include "libft_types.h"

typedef struct t_dbuffer
{
	void	*data;
	size_t	size;
	size_t	len;
}	t_dbuf;
typedef struct t_cbuffer
{
	const void	*data;
	size_t		size;
}	t_cbuf;
typedef enum e_buf_strategy
{
	E,
	x2,
}	t_buf_strat;

t_cbuf	cbuf_d(t_dbuf buf);
t_cbuf	cbuf(const void *data, size_t size);

t_dbuf	dbuf_d(t_dbuf buf);
t_dbuf	dbuf_c(t_cbuf buf);
t_dbuf	dbuf_s(size_t size);

void	free_dbuf(t_dbuf *buf);

t_dbuf	buf_insert(t_dbuf *buf, t_dbuf *insrt, size_t i, t_buf_strat mode);
t_dbuf	buf_insertc(t_dbuf *buf, t_cbuf insrt, size_t i, t_buf_strat mode);

t_cbuf	buf_shift(t_cbuf buf, size_t offset);

t_i32	buf_cmp(t_cbuf buf1, t_cbuf buf2);

ssize_t	buf_findindex(t_cbuf buf, t_cbuf bytes);

#endif
