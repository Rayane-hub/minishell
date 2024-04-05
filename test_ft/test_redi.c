#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

static void	ft_init_list(t_lst **lst, char **av)//test de ligne de commande (sortie du parsing)
{
	t_lst	*first_elem;
	//t_lst	*second_elem;
	//t_lst	*third_elem;

	
	first_elem = ft_lstnew_minishell();
	ft_lstadd_back_minishell(lst, first_elem);
	
	first_elem->line = "cmd bonjour >   f1 >> f2 >f3";
	first_elem->heredoc = 0;
	first_elem->cmd = av[1];
	first_elem->args = "bonjour";
	first_elem->redirection = malloc(4 * sizeof(char *));
	if (!first_elem->redirection)
	{
		ft_printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	first_elem->redirection[0] = ">   f1";
	first_elem->redirection[1] = ">> f2 ";
	first_elem->redirection[2] = ">f3";
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

static void	display_lst(t_lst *elem)
{
	ft_printf(">\t\t|%s|\n", elem->line);
	ft_printf("heredoc =\t%d\ndelimiter =\t|%s|\n", elem->heredoc, elem->delimiter);
	ft_printf("cmd =\t\t|%s|\nargs =\t\t|%s|\n", elem->cmd, elem->args, elem->next);
	for (size_t i = 0; elem->redirection[i] ; i++)
		ft_printf("redi[%d] =\t|%s|\n", i, elem->redirection[i]);
	ft_printf("next =\t\t|%p|\n\n", elem->next);
}

void	ft_redirection(t_lst *var)
{
	int	i;
	int	j;
	
	i = 0;
	while (var->redirection[i])
	{
		j = 0;
		while (var->redirection[i][j])
		{
			if (var->redirection[i][j] == '>' && var->redirection[i][j + 1] == '>') // >> 
			{
				j += 2;
				while (var->redirection[i][j] == ' ')//skip space
					j++;
				var->fd_outfile = open(var->redirection[i] + j, O_CREAT, O_RDWR, O_APPEND, 0644);
				j += ft_strlen(var->redirection[i] + j);
				break;
			}
			else if (var->redirection[i][j] == '>')// > 
			{
				j++;
				while (var->redirection[i][j] == ' ')
					j++;
				var->fd_outfile = open(var->redirection[i] + j, O_CREAT, O_RDWR, O_TRUNC, 0644);
				j += ft_strlen(var->redirection[i] + j);
				break;
			}
			else if (var->redirection[i][j] == '<')// <
			{
				j++;
				while (var->redirection[i][j] == ' ')
					j++;
				var->fd_infile = open(var->redirection[i] + j, O_RDONLY, 0644);
				j += ft_strlen(var->redirection[i] + j);
				break;
			}
		}
		i++;
	}
	
}

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
		if (lst->redirection)
			ft_redirection(lst);
		if (lst->next != NULL)
			printf("pipe a faire\n");
		lst = lst->next;
	}
	ft_free_lst(lst);
	return (0);
}