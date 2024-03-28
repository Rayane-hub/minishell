/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:26 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/28 18:43:55 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_lst(t_lst *lst);
static void	ft_init_list(t_lst **lst, char **av);

int	main(int ac, char **av, char **envp)
{
	t_lst	*lst;
	char buff[100];

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
		if (lst->heredoc < 0)
			printf("ft_heredoc() a faire\n");
		if (lst->redirection)
			ft_redirection(lst);
		if (lst->fd_infile > 0){
			read(lst->fd_infile, buff, 7);
			ft_printf("\t\tbuff = %s\n\n", buff);
		}
		if (lst->fd_outfile > 0)
			write(lst->fd_outfile, av[i], ft_strlen(av[i])); // ft_printf("\t\tout = %d\n", lst->fd_outfile);
		if (lst->next != NULL)
			printf("pipe a faire\n");
		if (ft_check_access(lst, envp) == 0)
			ft_printf("go exec la cmd ?\n\n\n");
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
	ft_printf("cmd =\t\t|%s|\nargs =\t\t|%s|\n", elem->cmd, elem->args, elem->next);
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

	first_elem->heredoc = 0;
	first_elem->cmd = av[1];
	first_elem->args = "bonjour";
	first_elem->redirection = malloc(4 * sizeof(char *));
	if (!first_elem->redirection)
	{
		ft_printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	first_elem->redirection[0] = "<   f42";
	first_elem->redirection[1] = ">f2";
	first_elem->redirection[2] = ">>                             f3";
	first_elem->redirection[3] = NULL;
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
