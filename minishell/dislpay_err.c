/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dislpay_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:19:08 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/25 18:55:01 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_cmd(t_lst *var)
{
	ft_putstr_fd("minishell: commande not found: ", 2);
	ft_putstr_fd(var->cmd, 2);
	write(2, "\n", 1);
	free(var->path_cmd);
	ft_free(var);
}

void	display_no_such(t_lst *var)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(var->cmd, 2);
	write(2, "\n", 1);
}

void	ft_free(t_lst *var)
{
	int	i;

	i = 0;
	while (var->split_path[i] != NULL)
		free(var->split_path[i++]);
	free(var->split_path);
	free(var->slash_cmd);
}

void ft_free_lst(t_lst *lst)
{
    t_lst *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;

        // Libérer la mémoire de l'élément
        free(tmp);
    }
}