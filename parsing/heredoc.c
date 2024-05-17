/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:38:50 by jgavairo          #+#    #+#             */
/*   Updated: 2024/05/10 18:33:17 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		(*cmd)->delimiter = malloc(sizeof (char *) * (*cmd)->nb_del);
	if (!(*cmd)->delimiter && (*cmd)->nb_del > 0)
		return (-1);
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

int	heredoc_copyer(char *pipes, t_cmd **cmd, int i, int del)
{
	int	start;
	int	p;

	p = i;
	start = 0;
	if (pipes[p] && pipes[p] == '<')
	{
		(*cmd)->heredoc = true;
		p++;
		while (pipes[p] && pipes[p] == ' ')
			p++;
		start = p;
		while (pipes[p] && pipes[p] != ' ' && pipes[p] != '<')
			p++;
		(*cmd)->delimiter[del] = ft_substr(pipes, start, p - start);
		if ((*cmd)->delimiter[del][0] == 34 || (*cmd)->delimiter[del][0] == 39)
		{
			(*cmd)->delimiter[del] = heredoc_w_cote((*cmd)->delimiter[del]);
			if (!(*cmd)->delimiter[del])
				return (-1);
			(*cmd)->expand_heredoc = 0;
		}
		else
			(*cmd)->expand_heredoc = 1;
	}
	return (p);
}

void	end_heredoc(char *pipes, t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while (pipes[i])
	{
		if (pipes[i] == '<')
		{
			i++;
			if (pipes[i] == '<')
				(*cmd)->end_heredoc = 1;
			else
				(*cmd)->end_heredoc = 0;
		}
		i++;
	}
}

int	heredoc_checker(char *pipes, t_cmd **cmd)
{
	int	i;
	int	del;

	del = 0;
	i = 0;
	if (heredoc_memory_allocer(pipes, cmd) == -1)
		return (-1);
	end_heredoc(pipes, cmd);
	while (pipes[i])
	{
		if (pipes[i] && pipes[i] == '<')
		{
			i++;
			if (pipes[i] && pipes[i] == '<')
			{
				i = heredoc_copyer(pipes, cmd, i, del);
				if (i == -1)
					return (-1);
				if (del < (*cmd)->nb_del)
					del++;
			}
		}
		else
			i++;
	}
	return (0);
}
