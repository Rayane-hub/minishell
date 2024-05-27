/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:02:31 by jgavairo          #+#    #+#             */
/*   Updated: 2024/05/27 18:35:38 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
			while (tmp->next && ft_strcmp(tmp->next->name, (*data)->cmd->args[i]) != 0)
				tmp = tmp->next;
			if (tmp && tmp->next && ft_strcmp(tmp->next->name, (*data)->cmd->args[i]) == 0)
			{
				swap = tmp->next;
				tmp->next = tmp->next->next;
				free(swap->name);
				free(swap->value);
				free(swap);
			}
		}
		else
		{
			exit_status_n_free((*data), 1, "unset: not a valid identifier: ");
			write(2, (*data)->cmd->args[i], ft_strlen((*data)->cmd->args[i]));
			write(2,"\n", 1);
		}
		i++;
	}
}

int	ft_cd(t_data *data)
{
	char	*old_pwd;
	int		i;

	i = 0;
	old_pwd = getcwd(NULL, 0);
	if (data->cmd->args[1] && ft_strcmp(data->cmd->args[1], "-") == 0)
	{
		while (data->var.mini_env[i] && ft_strncmp(data->var.mini_env[i], "OLDPWD=", 7) != 0)
			i++;
		if (!data->var.mini_env[i])
			return (display_error_cmd(data->cmd), -1);
		if (chdir(ft_strchr(data->var.mini_env[i], '/')) == -1)
		{
			perror("chdir OLDPWD failed ");
			return (-1);
		}
	}
	else if (!data->cmd->args[1])
	{
		while (data->var.mini_env[i] && ft_strncmp(data->var.mini_env[i], "HOME=", 5) != 0)
			i++;
		if (!data->var.mini_env[i])
			return (display_error_cmd(data->cmd), -1);
		if (chdir(ft_strchr(data->var.mini_env[i], '/')) == -1)
		{
			perror("chdir home failed ");
			return (-1);
		}
	}
	else if (chdir(data->cmd->args[1]) == -1)
	{
		perror("chdir failed ");
		return (-1);
	}
	check_variable(&data->mini_env, "OLDPWD", old_pwd);
	return (0);
}

int	ft_is_builtins_no_access(t_data *data)
{
	if (ft_strcmp(data->cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(data->cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(data->cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(data->cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

int	ft_builtins_env(t_data *data, int i)
{
	if (ft_strcmp(data->cmd->args[0], "export") == 0 && i == 1 && !data->cmd->next)
	{
		ft_export(data, &data->mini_env, data->cmd);
			return (1);
	}
	else if (ft_strcmp(data->cmd->args[0], "unset") == 0  && i == 1 && !data->cmd->next)
	{
		ft_unset(&data);
		return (1);
	}
	else if (ft_strcmp(data->cmd->args[0], "env") == 0 && i == 1 && !data->cmd->next)
	{
		env_cmd(data->mini_env);
		return (1);
	}
	else if (ft_strcmp(data->cmd->args[0], "cd") == 0 && i == 1 && !data->cmd->next)
	{
		ft_cd(data);
		return (1);
	}
	return (0);
}

void	ft_exit_prog(t_data *data)
{
	int exit_status = 0;
	if (data->cmd->args[1])
		exit_status = ft_atoi(data->cmd->args[1]); // Convert argument to exit status
	//ft_free_data(data); // Free any allocated memory
	exit(exit_status); // Exit the shell with the given status
}

void	ft_stat_check(int check_access, t_data *data)
{
	struct stat statbuf;
	if (check_access == 0){
		stat(data->cmd->path_cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			exit_status(data, 126, "");
			display_is_dir(data->cmd);
		}
	}
}

int	launch_exec(t_data *data)
{
	int		i;
	t_data	*begin;

	// Check if the command is "exit" and handle it before anything else
	if (data->cmd->args[0] && data->cmd->next == NULL && ft_strcmp(data->cmd->args[0], "exit") == 0)
		ft_exit_prog(data);
	begin = data;
	data->var.mini_env = ft_list_to_tab(data->mini_env);
	if (!data->var.mini_env)
		return (-1);
	data->save_pipe = 0;
	i = 0;
	int len_lst = ft_lstlen(data->cmd);
	if (ft_heredoc(data) == -1)
		return (ft_free_all_heredoc(begin), -1);
	//ft_display_heredoc(data->cmd);
	while (data->cmd)
	{
		data->exit_code = 0;
		i++;
		if (data->cmd->redirecter)	//2. redirecter check
			ft_redirecter(data);
		if (data->cmd->next != NULL)		//3. Pipe check ne peut etre fait si 3 ou plus de cmd car il va refaire un pipe et erase lancien alors aue pour 2 cmd il fait qun pipe
			if (pipe(data->pipe_fd) == -1)
				exit_status(data, 1, "pipe failed\n");
		if (data->cmd->args[0])
		{
			int check_access = ft_is_builtins_no_access(data);
			if (ft_builtins_env(data, i) == 0)
				if (check_access == 0)
					ft_stat_check(ft_check_access(data), data);
			if (i == 1)
			{	//5. exec (cmd_first) | cmd_middle... | cmd_last
				//printf("go exec first\n");
				ft_first_fork(data);
				if (data->pipe_fd[1] > 3)
					close(data->pipe_fd[1]);// je close lecriture pour pas que la lecture attende indefinement.
				data->save_pipe = data->pipe_fd[0]; //je save la lecture pour le next car je vais re pipe pour avoir un nouveau canal 
			}
			else if (i < len_lst)
			{	//6. exec cmd_first | (cmd_middle...) | cmd_last
				//printf("go exec mid\n");
				ft_middle_fork(data);
				close(data->pipe_fd[1]);
				data->save_pipe = data->pipe_fd[0];
			}
			else if (i == len_lst)
			{	//7. exec  exec cmd_first | cmd_middle... | (cmd_last)
				//printf("go exec last\n");
				ft_last_fork(data);
				close(data->pipe_fd[0]);
			}
		}
		ft_close(data->cmd);
		data->cmd = data->cmd->next;
	}
	ft_free_all_heredoc(begin);
	if (data->exit_code != 0)
		return (-1);
	return (0);
}

void handle_sigint(int sig) 
{
	(void)sig;              // Pour éviter les avertissements de variable non utilisée
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0); // Effacer la ligne actuelle
	rl_on_new_line();       // Repositionner le curseur sur une nouvelle ligne
	rl_redisplay();         // Redisplay le prompt
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	i = 0;
	data.exit_code = 0;
	if (minishell_starter(envp, &data) == -1)
		return (printf("Malloc error\n"), -1);
	while (1)
	{
		if (prompt_customer(&data) == 0)
		{
			if (data.var.rl[0] != '\0' && syntaxe_error(&data, data.var.rl) == 0)
			{
				if (parser(&data) == 0)
					if (final_parse(&data) == -1)
					{
						ft_lstclear(&data.cmd);
						free_pipes(data.var.pipes);
						free(data.var.pwd);
					}
			}
		}
		else
			break;
	}
	rl_clear_history();
	return(0);
}

//launch_exec | bultins

//faire < (syntaxe err) puis ls
