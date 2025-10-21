/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:39:42 by rasamad           #+#    #+#             */
/*   Updated: 2024/06/12 14:53:10 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_heredoc(t_cmd *lst)
{
	while (lst)
	{
		if (lst->heredoc_content)
		{
			free(lst->heredoc_content);
			lst->heredoc_content = NULL;
		}
		lst = lst->next;
	}
}

void	ft_free_heredoc(t_cmd *lst)
{
	int	i;

	i = 0;
	if (lst->heredoc_content)
	{
		free(lst->heredoc_content);
		lst->heredoc_content = NULL;
	}
}

void	del_first(char *line, t_cmd *lst)
{
	free(line);
	lst->heredoc_content = malloc(1 * sizeof(char));
	lst->heredoc_content[0] = '\n';
	lst->del_one = 1;
}

void	ft_close_pipe(t_data *data)
{
	if (data->pipe_fd[0] != -1)
	{
		close(data->pipe_fd[0]);
		data->pipe_fd[0] = -1;
	}
	if (data->pipe_fd[1] != -1)
	{
		close(data->pipe_fd[1]);
		data->pipe_fd[1] = -1;
	}
}

int	ft_check_num(t_data *data)
{
	int	i;

	if (data->cmd->args[1][0] != '+' && data->cmd->args[1][0] != '-' && \
	(!(data->cmd->args[1][0] >= '0' && data->cmd->args[1][0] <= '9')))
		return (-1);
	if (data->cmd->args[1][0] == '+' \
	&& (!(data->cmd->args[1][1] >= '0' && data->cmd->args[1][1] <= '9')))
		return (-1);
	else if (data->cmd->args[1][0] == '-' && \
	(!(data->cmd->args[1][1] >= '0' && data->cmd->args[1][1] <= '9')))
		return (-1);
	i = 1;
	while (data->cmd->args[1][i])
	{
		if ((!(data->cmd->args[1][i] >= '0' && data->cmd->args[1][i] <= '9')))
			return (-1);
		i++;
	}
	return (0);
}
