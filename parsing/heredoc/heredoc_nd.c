/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_nd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:51:56 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/03 15:01:32 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_counter(char *pipes)
{
	int	i;
	int	heredoc;

	heredoc = 0;
	i = 0;
	while (pipes[i])
	{
		if (pipes[i] && pipes[i] == '<')
		{
			i++;
			if (pipes[i] && pipes[i] == '<')
			{
				heredoc++;
				i++;
			}
		}
		else
			i++;
	}
	return (heredoc);
}

int	heredoc_memory_allocer(char *pipes, t_cmd **cmd)
{
	(*cmd)->nb_del = heredoc_counter(pipes);
	if ((*cmd)->nb_del > 0)
		(*cmd)->delimiter = ft_calloc((*cmd)->nb_del + 1, sizeof (char *));
	if (!(*cmd)->delimiter && (*cmd)->nb_del > 0)
		return (-1);
	end_heredoc(pipes, cmd);
	return (0);
}

char	*heredoc_w_cote(char *src)
{
	char	*dest;
	char	*tmp;
	int		i;
	int		p;

	tmp = NULL;
	dest = NULL;
	p = 0;
	i = 0;
	dest = ft_calloc((ft_strlen(src) - 1), sizeof (char));
	if (!dest)
		return (NULL);
	tmp = ft_strdup(src);
	if (!tmp)
		return (NULL);
	while (tmp[i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
			i++;
		else
			dest[p++] = tmp[i++];
	}
	free(tmp);
	free(src);
	return (dest);
}

void	heredoc_copyer_init(t_cmd **cmd, t_int *var, int i)
{
	(*cmd)->heredoc = true;
	(*var).p = i + 1;
}

int	heredoc_copyer(char *pipes, t_cmd **cmd, int i, int del)
{
	t_int	var;

	init_var(&var);
	heredoc_copyer_init(cmd, &var, i);
	while (pipes[var.p] && pipes[var.p] == ' ')
		var.p++;
	var.start = var.p;
	while (pipes[var.p] && pipes[var.p] != ' ' && pipes[var.p] != '<')
		var.p++;
	(*cmd)->delimiter[del] = ft_substr(pipes, var.start, var.p - var.start);
	while ((*cmd)->delimiter[del][var.x])
	{
		if ((*cmd)->delimiter[del][var.x] == 34 || \
		(*cmd)->delimiter[del][var.x] == 39)
		{
			(*cmd)->delimiter[del] = heredoc_w_cote((*cmd)->delimiter[del]);
			if (!(*cmd)->delimiter[del])
				return (-1);
			(*cmd)->expand_heredoc = 0;
			break ;
		}
		(*cmd)->expand_heredoc = 1;
		var.x++;
	}
	return (var.p);
}
