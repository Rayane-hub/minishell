/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:12:43 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/29 17:41:43 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(t_lst *var, char **envp)
{
	if (var)
		if (envp)
			;

	pid_t pid;
	pid = fork();
	if (pid < 0){
		perror("");	
		exit(1);
	}
	
	if (pid == 0){
		//if (fd_infile > 0) ---> dup2(fd_infile, stdin)
		//if (fd_outfile > 0) ---> dup2(fd_outfile, stdout)
		//if (pipe_fd) ---> dup2(pipd_fd[1], stdout)
		//puis check ou lexecute read et write
		execve(var->path_cmd, var->args, envp);
		perror("execve : failed ");
		exit(0);
	}
	else if (pid > 0){
		int	status;
		wait(&status);
		ft_printf("je suis dans le processus du parent, le pid de l'enfant est %d\n", pid);
	}
	return (0);
}
