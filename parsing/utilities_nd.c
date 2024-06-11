/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_nd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:46:02 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/10 16:54:21 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone_nd(t_cmd *lst)
{
	if (lst->redirecter)
	{
		free_pipes(lst->redirecter);
		lst->redirecter = NULL;
	}
	if (lst->split_path)
	{
		free_pipes(lst->split_path);
		lst->split_path = NULL;
	}
	if (lst->slash_cmd)
	{
		free(lst->slash_cmd);
		lst->slash_cmd = NULL;
	}
	if (lst->path_cmd)
	{
		free(lst->path_cmd);
		lst->path_cmd = NULL;
	}
}

void	ft_lstdelone(t_cmd *lst)
{
	if (lst)
	{
		if (lst->args)
		{
			free_pipes(lst->args);
			lst->args = NULL;
		}
		if (lst->delimiter)
		{
			free_pipes(lst->delimiter);
			lst->delimiter = NULL;
		}
		ft_lstdelone_nd(lst);
		free(lst);
	}
}

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = tmp;
	}
}

int	ft_lstlen(t_cmd *elem)
{
	int	i;

	i = 0;
	while (elem)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}
