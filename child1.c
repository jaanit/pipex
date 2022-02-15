/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:34:39 by rjaanit           #+#    #+#             */
/*   Updated: 2022/02/12 15:44:05 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

static char	*get_commande(char **paths, char *commande_arg)
{
	char	*path_join;
	char	*commande;

	while (*paths != NULL)
	{
		path_join = ft_strjoin(*paths, "/");
		commande = ft_strjoin(path_join, commande_arg);
		free(path_join);
		if (!access(commande, X_OK))
			break ;
		free(commande);
		paths++;
	}
	if (*paths == NULL)
		commande = NULL;
	return (commande);
}

void	ft_child1(t_pipex pipe, char **av, char **env)
{
	int		infile;
	char	**commande_arg;
	char	*commande;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile < 0)
		ft_error("Error infile");
	dup2(infile, 0);
	close(infile);
	dup2(pipe.fd[1], 1);
	close(pipe.fd[0]);
	commande_arg = ft_split(av[2], ' ');
	commande = get_commande(pipe.path_sep, commande_arg[0]);
	if (commande == NULL)
	{
		ft_free(commande_arg);
		ft_error("command not found");
	}
	execve(commande, commande_arg, env);
}
