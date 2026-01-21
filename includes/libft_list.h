/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/20 19:30:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include "libft_types.h"

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;
typedef struct s_list
{
	t_node	*nodes;
	size_t	size;
}	t_lst;

t_lst	lst_(void);
t_lst	lst_n(t_node *node);
t_lst	lst_l(t_lst list, void *(*copy)(void *), void (*del)(void *));

t_node	*node(void *content);

void	free_lst(t_lst *lst, void (*del)(void*));
void	free_node(t_lst *lst, t_node *node, void (*del)(void*));

t_node	*get(t_lst lst, size_t index);
t_lst	filter(t_lst lst, t_bool (*cmp)(void *, void *), void *context);

t_lst	lst_insert(t_lst *lst, t_node *node, size_t index);

void	lst_foreach(t_lst lst, void (*f)(void *));
t_lst	lst_map(t_lst *lst, void *(*f)(void *), void (*del)(void *));

#endif
