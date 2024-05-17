/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavairon <gavairon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:31:40 by gavairon          #+#    #+#             */
/*   Updated: 2024/05/16 01:50:10 by gavairon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell_starter(char **env, t_data *data)
{
	data_initializer(data);
	printf_title();
	if (env_copyer(env, &data->mini_env) == -1)
		return (exit_status(data, 1, "\033[31mMalloc error from [env_copyer]\n\033[0m"), -1);
	return (0);
}

int	prompt_customer(t_data *data)
{
	data->var.pwd = getcwd(NULL, 0);
	if (data->var.pwd == NULL)
		return (exit_status(data, 1, "\033[31mError from [getcwd]\n\033[0m"), -1);
	printf ("\033[90m%s\033[0m", data->var.pwd);
	data->var.rl = readline("\e[33m$> \e[37m");
	if (data->var.rl == NULL)
		return (exit_status(data, 1, "\033[31mError from [readline]\n\033[0m"), -1);
	if (data->var.rl[0])
		add_history(data->var.rl);
	return (0);
}

int	parser(t_data *data)
{
	negative_checker(data->var.rl);
	data->var.rl = dolls_expander(data->var.rl, data->mini_env, data);
	if (!data->var.rl)
		return (exit_status(data, 1, "\033[31mMalloc error from [dolls_expander]\n\033[0m"), -1);
	data->var.pipes = ft_split(data->var.rl, '|');
	if (!data->var.pipes)
		return (exit_status(data, 1, "\033[31mMalloc error from [ft_split]\n\033[0m"), -1);
	free(data->var.rl);
	return (0);
}

int	node_precreator(t_data *data, int i)
{
	data->tmp = ft_lstnew_minishell();
	if (!data->tmp)
		return (exit_status(data, 1, "\033[31mMalloc error from [lst_new_minishell]\n\033[0m"), -1);
	if (heredoc_checker(data->var.pipes[i], &data->tmp) == -1)
		return (exit_status(data, 1, "\033[31mMalloc error from [heredoc_checker]\n\033[0m"), -1);
	if (redirecter(data->var.pipes[i], &data->tmp) == -1)
		return (exit_status(data, 1, "\033[31mMalloc error from [redirecter]\n\033[0m"), -1);
	data->var.pipes[i] = redirect_deleter(data->var.pipes[i]);
	if (!data->var.pipes[i])
		return (exit_status(data, 1, "\033[31mMalloc error from [redirect_deleter]\n\033[0m"), -1);
	data->var.input = ft_split(data->var.pipes[i], ' ');
	if (data->var.input == NULL)
			return (exit_status(data, 1, "\033[31mMalloc error from [ft_split]\n\033[0m"), -1);
	data->var.input_copy = input_copyer(data->var.input, data->var.input_copy);
	if (data->var.input_copy == NULL)
		return (exit_status(data, 1, "\033[31mMalloc error from [input_copyer]\n\033[0m"), -1);
	return (0);
}

int	node_creator(t_data *data)
{
	int	i;

	i = 0;
	while (data->var.pipes[i])
	{
		if (node_precreator(data, i) == 0)
		{
			if (stock_input(data->var.input_copy, &data->tmp) == 0)
			{
				i++;
				ft_lstadd_back_minishell(&data->cmd, data->tmp);
			}
			else
				return (-1);
			free(data->var.input_copy);
		}
		else
			return (-1);
	}
	return (0);
}
