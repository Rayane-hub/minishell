/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:21 by rasamad           #+#    #+#             */
/*   Updated: 2024/04/05 09:49:24 by rasamad          ###   ########.fr       */
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
	char			*delimiter;//**delimiter
	char			*cmd;
	char			**args;
	char			**redirection;
	struct s_lst	*next;
	
	int				fd_infile;
	int				fd_outfile;
	char			**split_path;
	char			*slash_cmd;
	char			*path_cmd;
	int				i;
	
}	t_lst;

typedef struct s_struct
{
	int	pipe_fd[2];
	int save_pipe;
}	t_struct;

t_lst	*ft_lstnew_minishell(void);
t_lst	*ft_lstlast_minishell(t_lst *lst);
void	ft_lstadd_back_minishell(t_lst **lst, t_lst *new);
int		ft_lstlen(t_lst *elem);
void	ft_redirection(t_lst *elem);
int		ft_check_access(t_lst *elem, char **envp);
int		ft_first_fork(t_lst *elem, t_struct *var, char **envp);
int		ft_middle_fork(t_lst *elem, t_struct *var, char **envp);
int		ft_last_fork(t_lst *elem, t_struct *var, char **envp);
void	display_error_cmd(t_lst *elem);
void	display_no_such(t_lst *elem);
void	ft_free_access(t_lst *elem);
void	ft_free_token(t_lst *elem);
void	ft_free_lst(t_lst *lst);
void	ft_close(t_lst *elem);

#endif