/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:09:29 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/28 18:43:37 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_lst *var)
{
	int	i;
	int	j;

	var->fd_infile = -2;
	var->fd_outfile = -2;	
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
				//check si je dois close l'ancien en cas de redirection multiple
				var->fd_outfile = open(var->redirection[i] + j, O_CREAT | O_WRONLY | O_APPEND, 0777);
				if (var->fd_outfile == -1) {
                    perror("Erreur lors de l'ouverture du fichier de sortie (>>)");
                    exit(EXIT_FAILURE);
                }
				break;
			}
			else if (var->redirection[i][j] == '>')// > 
			{
				j++;
				while (var->redirection[i][j] == ' ')
					j++;
				//check si je dois close l'ancien en cas de redirection multiple
				var->fd_outfile = open(var->redirection[i] + j, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				if (var->fd_outfile == -1) {
                    perror("Erreur lors de l'ouverture du fichier de sortie (>)");
                    exit(EXIT_FAILURE);
                }
				break;
			}
			else if (var->redirection[i][j] == '<')// <
			{
				j++;
				while (var->redirection[i][j] == ' ')
					j++;
				var->fd_infile = open(var->redirection[i] + j, O_RDONLY, 0777);
				if (var->fd_infile == -1) {
                    write (2, var->redirection[i] + j, ft_strlen(var->redirection[i] + j));
                    perror(" (<)");
                    exit(EXIT_FAILURE);
                }
				break;
			}
		}
		i++;
	}
}
