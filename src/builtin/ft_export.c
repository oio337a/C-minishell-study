/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:43 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/20 17:37:15 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	추가할 것  : 인자로 받은 key가 이미 있을 때, 덮어 씌우기
	-> init_envp.c에 insert_envp 시 check_dupkey 조건 추가했어요

	# 예시
	export <변수명>=<값> : export abc=123
	-------------------------------
	# 짜증나는 예시
	export a                            #key값만 생성
	export b=                           #value에 ""
	export c+=world                     #환경변수 뒤에 덧붙이기 (아무것도 없어도 가능)
	export d="oh      my          god"  #echo출력과 export출력 다름. echo는 스페이스 하나로 처리 .. 미친새끼아녀 ?
	export e=elephant f=flower
	export a=b=c                        #a="b=c"
	export a=====b                      #a="====b"
	export a=b c d                      #a=b, c, d
	-------------------------------
	명령어가 export 하나면 (인자 X) -> 환경변수 오름차 순 출력 (형식 : declare -x [KEY=”VALUE”])

	명령어가 export z 와 같은 식으로 인자가 하나면 환경변수에 저장되지 않음.
	=> 저장 됩니다! env로 출력시 안 나오고, export로 출력시 나옴

	명령어가 export key=value 일 때

	이미 존재하는 환경변수면 free 후 새로 dup
	새로운 환경변수면 원래 크기 + 2 짜리 **new 생성
	기존 환경변수 dup 하고
	새 환경변수, NULL 추가
	기존 환경변수 free 해주고 **new로 대체
	파이프 뒤에 있다면 자식프로세스의 export이기 때문에 환경변수 생성 X

	key가 숫자로 시작하면 안 됨.
	스페이스, 특수문자 등은 key, value 모두 안되는데, .랑 -랑 /는 왜 됨 ;;
	작은, 큰 따옴표 제거하고 환경변수 목록에 추가되어야 함.
*/

static void	sort_arr(char **arr)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	len = ft_arrlen(arr);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strcmp(*(arr + i), *(arr + j)) < 0)
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + i);
				*(arr + i) = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	check_argv(char *argv)
{
	char	*key;
	int		i;
	int		plus;
	int		ret;

	i = ft_strchr_int(argv, '=');
	if (i == -1)
		return (validate_key(argv));
	plus = ft_strchr_int(argv, '+');
	if (plus != -1 && plus < i && (plus != i - 1))
		return (0);
	if (plus == i - 1)
		key = ft_substr(argv, 0, plus);
	else
		key = ft_substr(argv, 0, i);
	ret = validate_key(key);
	free(key);
	return (ret);
}

static void	set_key_value(t_envp *head, char *argv, int i, int plus)
{
	char	*key;
	char	*value;

	value = ft_substr(argv, i + 1, ft_strlen(argv) - i + 1);
	if (plus == i - 1)
	{
		key = ft_substr(argv, 0, i - 1);
		append_envp(head, key, value);
	}
	else
	{
		key = ft_substr(argv, 0, i);
		insert_envp(head, key, value);
	}
	free(key);
	free(value);
}

static int	add_envp(char *argv, t_envp *head)
{
	int		i;
	int		plus;

	if (!head || !argv)
		return (0);
	if (!check_argv(argv))
		return (envp_errno(argv, STDOUT_FILENO));
	i = ft_strchr_int(argv, '=');
	plus = ft_strchr_int(argv, '+');
	if (i == -1)
		insert_envp(head, argv, NULL);
	else
		set_key_value(head, argv, i, plus);
	return (1);
}

void	ft_export(t_info *arg, t_envp *head)
{
	t_info	*arg_tmp;
	t_envp	*env_tmp;
	char	**arr;
	int		i;

	arg_tmp = arg;
	env_tmp = head;
	if (arg_tmp->next == NULL)
	{
		arr = dup_envp(head);
		sort_arr(arr);
		i = -1;
		while (arr[++i])
			printf("declare -x %s\n", arr[i]);
		ft_free(arr);
	}
	i = 0;
	arg_tmp = arg_tmp->next;
	while (arg_tmp)
	{
		if (!add_envp(arg_tmp->cmd, head))
			i = 1;
		arg_tmp = arg_tmp->next;
	}
	g_last_exit_code = i;
}
