/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:12:43 by rasamad           #+#    #+#             */
/*   Updated: 2024/06/11 19:18:13 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint_fork(int sig) 
{
	(void)sig;              // Pour éviter les avertissements de variable non utilisée
	printf("\n");
	g_sig = 1;
}

void	handle_sigquit_fork(int sig) 
{
	(void)sig;              // Pour éviter les avertissements de variable non utilisée
	g_sig = 2;
}