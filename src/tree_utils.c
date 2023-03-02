/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:37:21 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 15:05:49 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*insert_cmd(t_info *root, char **cmd, int token)
{
	if (!root)
	{
		root = (t_info *)malloc(sizeof(t_info));
		root->left = NULL;
		root->right = NULL;
		root->cmd = cmd;
		root->token = token;
	}
	else
	{
		if (root->token == CMD)
		{
			if (token == SIMCMD)
				insert_cmd(root->right, cmd, token);
			if (token == RIDIR)
				insert_cmd(root->left, cmd, token);
		}
		if (root->token == RIDIR)
		{
			if (!root->left)
				insert_cmd(root->left, cmd, token);
			if (!root->right)
				insert_cmd(root->right, cmd, token);
		}
		if (root->token == PIPE)
		{
			if (token == CMD)
				insert_cmd(root->left, cmd, token);
			if (token == PIPE)
				insert_cmd(root->right, cmd, token);
		}
	}
}