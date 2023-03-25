/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_access_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:23:05 by suhwpark          #+#    #+#             */
/*   Updated: 2023/03/24 18:08:20 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	access_builtin(t_info *head, t_envp *env, t_pipe *var)
{
	t_info	*splited_var;

	splited_var = get_token(&head, env, var, 0);
	builtin(splited_var, env, 42);
	dup2(var->stdin_back, STDIN_FILENO);
	dup2(var->stdout_back, STDOUT_FILENO);
	list_delete(&splited_var);
}

t_pipe	*get_pipe_info(t_info *token)
{
	t_pipe	*var;

	var = (t_pipe *)ft_safe_malloc(sizeof(t_pipe));
	var->stdin_back = dup(STDIN_FILENO);
	var->stdout_back = dup(STDOUT_FILENO);
	var->heredoc_pos = list_count_heredoc(token);
	var->heredoc_cnt = get_heredoc_pipe(token, var->heredoc_pos);
	if (var->heredoc_cnt > 0)
		move_heredoc(&token, var->heredoc_cnt);
	var->total_pipe = get_pipe_count(token) - (var->heredoc_cnt) + 1;
	var->flag = 0;
	var->status = 0;
	var->filename = file_name(token);
	return (var);
}

static int	check_in_out_dir(t_info **token, t_envp *envp, t_pipe *var, int i)
{
	if ((*token)->type == REDIR_IN)
		return (type_redir_in(token));
	else if ((*token)->type == HEREDOC_IN)
		return (type_heredoc_in(token, var, envp, i));
	else if ((*token)->type == REDIR_OUT)
		return (type_redir_out(token));
	else if ((*token)->type == HEREDOC_OUT)
		return (type_heredoc_out(token));
	return (42);
}

t_info	*get_token(t_info **token, t_envp *envp, t_pipe *var, int i)
{
	t_info	*new;
	int		dir;

	new = init_list();
	while (*token && (*token)->type != PIPE)
	{
		dir = check_in_out_dir(token, envp, var, i);
		if (!dir)
			continue ;
		else if (dir == 1)
		{
			var->flag = 1;
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
			continue ;
		}
		insert_list(new, (*token)->cmd, (*token)->type);
		(*token) = (*token)->next;
	}
	return (new);
}
