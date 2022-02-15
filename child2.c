/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:46:53 by rjaanit           #+#    #+#             */
/*   Updated: 2022/02/12 15:43:49 by rjaanit          ###   ########.fr       */
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

void	ft_child2(t_pipex pipe, char **av, int ac, char **env)
{
	int		outfile;
	char	**commande_arg;
	char	*commande;

	outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (outfile < 0)
		ft_error("Error oufile");
	dup2(pipe.fd[0], 0);
	close(pipe.fd[1]);
	dup2(outfile, 1);
	close(outfile);
	commande_arg = ft_split(av[3], ' ');
	commande = get_commande(pipe.path_sep, commande_arg[0]);
	if (commande == NULL)
	{
		ft_free(commande_arg);
		ft_error("command not found");
	}
	execve(commande, commande_arg, env);
}
