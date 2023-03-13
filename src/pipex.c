/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:56:14 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/13 14:33:36 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	first_process(char **path, char **argv, char **envp, int fd[])
{
	int		infile_fd;
	int		i;
	char	*limiter;

	if (is_here_doc(argv[1]))
	{
		limiter = ft_strjoin(argv[2], "\n");
		if (!limiter)
			ft_perror("allocated failed");
		here_doc(limiter);
		free(limiter);
		i = 3;
	}
	else
	{
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			ft_perror("open error");
		(dup2(infile_fd, STDIN_FILENO), close(infile_fd));
		i = 2;
	}
	close(fd[0]);
	(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
	execve_path(path, argv[i], envp);
}

static void	last_process(char **path, char **argv, char **envp, int argc)
{
	int		outfile_fd;

	if (is_here_doc(argv[1]))
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		ft_perror("open error");
	(dup2(outfile_fd, STDOUT_FILENO), close(outfile_fd));
	execve_path(path, argv[argc - 2], envp);
}

static void	mid_process(char **path, char *argv, char **envp, int fd[])
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execve_path(path, argv, envp);
}

void	pipex(int argc, char **path, char **argv, char **envp)
{
	pid_t	pid;
	int		i;
	int		status;
	int		fd[2];

	i = 1 + is_here_doc(argv[1]);
	while (++i < argc - 1)
	{
		if (pipe(fd) == -1)
			ft_perror("pipe failed");
		pid = fork();
		if (pid == 0)
		{
			if (i == 2 || (is_here_doc(argv[1]) && i == 3))
				first_process(path, argv, envp, fd);
			if (i == argc - 2)
				last_process(path, argv, envp, argc);
			mid_process(path, argv[i], envp, fd);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	while (wait(&status) == -1)
		return ;
}