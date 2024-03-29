/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:26 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/29 17:34:58 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_lst(t_lst *lst);
static void	ft_init_list(t_lst **lst, char **av);

int	main(int ac, char **av, char **envp)
{
	t_lst	*lst;

	int i = 0;
	lst = NULL;
	if (ac)
		if(av[1] == NULL)
			return (0);
	ft_init_list(&lst, av);
	while (lst)
	{
		i++;
		ft_printf("%d\n", i);
		display_lst(lst);
		if (lst->heredoc < 0)//1. Heredoc check
			printf("ft_heredoc() a faire\n");
		if (lst->redirection)//2. Redirection check
			ft_redirection(lst);
		if (lst->next != NULL)//3. pipe check
			pipe(lst->pipe_fd);
		if (ft_check_access(lst, envp) == 0) //4. cmd check
			ft_fork(lst, envp);
		else
			ft_printf("cmd wrong, que faire ?\n\n\n");
		lst = lst->next;
	}
	ft_free_lst(lst);
	return (0);
}

static void	display_lst(t_lst *elem)
{
	ft_printf(">\t\t|%s|\n", elem->line);
	ft_printf("heredoc =\t%d\ndelimiter =\t|%s|\n", elem->heredoc, elem->delimiter);
	ft_printf("cmd =\t\t|%s|\n", elem->cmd);
	for (size_t i = 0; elem->args[i] ; i++)
		ft_printf("args[%d] =\t|%s|\n", i, elem->args[i]);
	for (size_t i = 0; elem->redirection[i] ; i++)
		ft_printf("redi[%d] =\t|%s|\n", i, elem->redirection[i]);
	ft_printf("next =\t\t|%p|\n\n", elem->next);
}

static void	ft_init_list(t_lst **lst, char **av)//test de ligne de commande (sortie du parsing)
{
	t_lst	*first_elem;
	//t_lst	*second_elem;
	//t_lst	*third_elem;

	first_elem = ft_lstnew_minishell();
	ft_lstadd_back_minishell(lst, first_elem);

	first_elem->line = "ls -l > f4";
	first_elem->heredoc = 0;
	first_elem->cmd = av[1];
	
	first_elem->args = malloc(3 * sizeof(char *));
	if (!first_elem->args){
		ft_printf("malloc args failed\n");
		exit(EXIT_FAILURE);
	}
	//first_elem->args[0] = first_elem->cmd;
	//first_elem->args[0] = "ls";
	first_elem->args[0] = "-l";
	first_elem->args[1] = "-a";
	first_elem->args[2] = NULL;
	
	first_elem->redirection = malloc(2 * sizeof(char *));
	if (!first_elem->redirection){
		ft_printf("malloc redi failed\n");
		exit(EXIT_FAILURE);
	}
	first_elem->redirection[0] = "> f4";
	first_elem->redirection[1] = NULL;
	//first_elem->redirection[2] = ">>                            f3";
	//first_elem->redirection[3] = NULL;
	first_elem->next = NULL;
	
	
	/*second_elem = ft_lstnew_minishell();
	ft_lstadd_back_minishell(lst, second_elem);

	second_elem->line = "<< EOF cmd -l > f2 -a";
	second_elem->heredoc = 1;
	second_elem->delimiter = "EOF";
	second_elem->cmd = av[2];
	second_elem->args = "-l -a";
	second_elem->redirection = malloc(2 * sizeof(char *));
	if (!second_elem->redirection)
	{
		ft_printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	second_elem->redirection[0] = "> f2";
	second_elem->redirection[1] = NULL;
	second_elem->next = NULL;


	third_elem = ft_lstnew_minishell();
	ft_lstadd_back_minishell(lst, third_elem);

	third_elem->line = "<f3 cmd -eA";
	third_elem->heredoc = 0;
	third_elem->cmd = av[3];
	third_elem->args = "-eA";
	third_elem->redirection = malloc(2 * sizeof(char *));
	if (!third_elem->redirection)
	{
		ft_printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	third_elem->redirection[0] = "<f3";
	third_elem->redirection[1] = NULL;
	third_elem->next = NULL;*/
}
