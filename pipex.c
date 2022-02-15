/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:28:09 by rjaanit           #+#    #+#             */
/*   Updated: 2022/02/12 15:51:14 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static void	free_ft(char **path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

char	*get_path(char **env)
{
	char	*str;

	while (ft_strncmp("PATH", *env, 4))
		env++;
		str = (*env + 5);
	return (str);
}

int	main(int ac, char **av, char **env)
{
	t_pipex		my_pipe;
	int			pid1;
	int			pid2;

	if (ac != 5)
		return (ft_message("EROOR"));
	if (pipe(my_pipe.fd) < 0)
		return (ft_message("Error pipe"));
	my_pipe.path = get_path(env);
	my_pipe.path_sep = ft_split(my_pipe.path, ':');
	pid1 = fork();
	if (pid1 == 0)
		ft_child1(my_pipe, av, env);
	pid2 = fork();
	if (pid2 == 0)
		ft_child2(my_pipe, av, ac, env);
	close_pipe(my_pipe.fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_ft(my_pipe.path_sep);
	return (0);
}
