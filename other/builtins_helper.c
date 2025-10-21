/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:47:52 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/12 14:24:01 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	failed_unset(t_data **data, int i)
{
	exit_status_n_free((*data), 1, "unset: not a valid identifier: ");
	write(2, (*data)->cmd->args[i], ft_strlen((*data)->cmd->args[i]));
	write(2, "\n", 1);
}

void	unset_swap(t_env **swap, t_env **tmp)
{
	(*swap) = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	free((*swap)->name);
	free((*swap)->value);
	free((*swap));
}

void	ft_unset(t_data **data)
{
	t_env	*tmp;
	t_env	*swap;
	int		i;

	i = 1;
	tmp = (*data)->mini_env;
	while ((*data)->cmd->args[i])
	{
		if (spec_export((*data)->cmd->args[i]) == 0)
		{
			while (tmp->next && \
			ft_strcmp(tmp->next->name, (*data)->cmd->args[i]) != 0)
				tmp = tmp->next;
			if (tmp && tmp->next && \
			ft_strcmp(tmp->next->name, (*data)->cmd->args[i]) == 0)
			{
				unset_swap(&swap, &tmp);
				tmp = (*data)->mini_env;
			}
		}
		else
			failed_unset(data, i);
		i++;
	}
}

int	ft_cd_helper(t_data *data, int i, char *old_pwd, int choice)
{
	if (choice == 1)
	{
		while (data->var.mini_env[i] && \
		ft_strncmp(data->var.mini_env[i], "OLDPWD=", 7) != 0)
			i++;
		if (!data->var.mini_env[i])
			return (free(old_pwd), display_error_cmd(data->cmd), -1);
		if (chdir(ft_strchr(data->var.mini_env[i], '/')) == -1)
			return (perror("chdir OLDPWD failed "), free(old_pwd), -1);
	}
	if (choice == 2)
	{
		while (data->var.mini_env[i] && \
		ft_strncmp(data->var.mini_env[i], "HOME=", 5) != 0)
			i++;
		if (!data->var.mini_env[i])
			return (display_error_cmd(data->cmd), -1);
		if (chdir(ft_strchr(data->var.mini_env[i], '/')) == -1)
			return (perror("chdir home failed "), free(old_pwd), -1);
	}
	return (0);
}

int	ft_cd(t_data *data)
{
	char	*old_pwd;
	char	*pwd;
	int		i;

	i = 0;
	old_pwd = getcwd(NULL, 0);
	if (data->cmd->args[1] && ft_strcmp(data->cmd->args[1], "-") == 0)
		ft_cd_helper(data, i, old_pwd, 1);
	else if (!data->cmd->args[1])
		ft_cd_helper(data, i, old_pwd, 2);
	else if (chdir(data->cmd->args[1]) == -1)
	{
		perror("chdir failed ");
		return (free(old_pwd), -1);
	}
	check_variable(&data->mini_env, "OLDPWD", old_pwd);
	pwd = getcwd(NULL, 0);
	check_variable(&data->mini_env, "PWD", pwd);
	return (free(old_pwd), free(pwd), 0);
}
