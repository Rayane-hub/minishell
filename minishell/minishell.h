/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:21 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/28 15:42:19 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_lst
{
	char			*line;//
	int				heredoc;
	char			*delimiter;//**
	char			*cmd;
	char			*args;//**
	char			**redirection;//**
	struct s_lst	*next;
	
	int				fd_infile;
	int				fd_outfile;
	char			**split_path;
	char			*slash_cmd;
	char			*path_cmd;
	int				i;
	int				pipe_fd[2];
	
}	t_lst;

t_lst	*ft_lstnew_minishell(void);
t_lst	*ft_lstlast_minishell(t_lst *lst);
void	ft_lstadd_back_minishell(t_lst **lst, t_lst *new);
void	ft_redirection(t_lst *var);
int		ft_check_access(t_lst *var, char **envp);
void	display_error_cmd(t_lst *var);
void	display_no_such(t_lst *var);
void	ft_free(t_lst *var);
void	ft_free_lst(t_lst *lst);

#endif