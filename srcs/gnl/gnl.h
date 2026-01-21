/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:01:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:30:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "libft_gnl.h"

t_reader	*select_reader(t_readers *readers, t_u32 fd);

void		read_file(t_reader_content *reader_content, t_u32 fd);

#endif