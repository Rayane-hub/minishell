/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper_nd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:23:25 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/12 14:24:23 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtins_no_access(t_cmd *lst)
{
	if (!lst->args[0])
		return (1);
	if (ft_strcmp(lst->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(lst->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(lst->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(lst->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(lst->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(lst->args[0], "pwd") == 0)
		return (1);
	return (0);
}

int	ft_builtins(t_cmd *lst)
{
	if (ft_strcmp(lst->args[0], "pwd") == 0)
	{
		if (ft_pwd() == -1)
		{
			perror("getcwd");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	else if (ft_strcmp(lst->args[0], "echo") == 0)
		return (ft_echo(lst), 1);
	return (0);
}
