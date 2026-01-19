/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:31:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 19:10:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_rule_content(void *content)
{
	((t_rule_ctnt *)content)->type = _default;
	((t_rule_ctnt *)content)->prec = -1;
	((t_rule_ctnt *)content)->width = 0;
	((t_rule_ctnt *)content)->pad = pad_std;
	((t_rule_ctnt *)content)->out = out_std;
	((t_rule_ctnt *)content)->sign = sign_std;
	((t_rule_ctnt *)content)->len = 0;
	free(content);
}

t_rule	*rule(void)
{
	t_rule		*rule;
	t_rule_ctnt	*content;

	content = malloc(sizeof(t_rule_ctnt));
	if (content == NULL)
		return (NULL);
	content->type = _default;
	content->prec = -1;
	content->width = 0;
	content->pad = pad_std;
	content->out = out_std;
	content->sign = sign_std;
	content->len = 0;
	rule = (t_rule *)node(content);
	if (rule == NULL)
		return (ft_free_rule_content(&content), NULL);
	return (rule);
}
