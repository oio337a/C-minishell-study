/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:37:42 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 17:35:12 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

static char	*find_value(char *dollar, t_envp *envp, int *idx)
{
	t_envp	*head;
	char	*key;
	int		i;

	i = 1;
	while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
		i++;
	key = ft_substr(dollar, 1, i - 1);
	*idx += (ft_strlen(key) + 1);
	free(key);
	head = envp;
	while (head != NULL)
	{
		if (!ft_strcmp(key, head->key))
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup(""));
}

static int	check_edges(char next, char **str, int *i)
{
	char	*pid;

	if (ft_isdigit(next))
		*i += 2;
	else if (next == '$')
	{
		pid = ft_itoa(getpid());
		*str = ft_strjoin_free(*str, pid);
		*i += 2;
		free(pid);
	}
	else if ((!ft_isalnum(next) && next != '_') || next == '\0')
	{
		*str = ft_strjoin_free(*str, "$");
		*i += 1;
	}
	else
		return (0);
	return (1);
}

static int	set_sub(char *str, char **ret)
{
	int		i;
	char	*sub;

	sub = ft_substr((str), 0, is_dollar(str));
	*ret = ft_strjoin_free(*ret, sub);
	i = is_dollar(str);
	free(sub);
	return (i);
}

char	*parse_dollar(char *str, t_envp *head)
{
	char	*ret;
	char	*value;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (check_edges(str[i + 1], &ret, &i))
				continue ;
			value = find_value(str + i, head, &i);
			ret = ft_strjoin_free(ret, value);
			free(value);
		}
		else
			i += set_sub(str + i, &ret);
	}
	return (ret);
}
