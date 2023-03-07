/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:43 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/07 22:41:29 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
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

t_info	*ft_export(char **argv, char **envp, t_info *ept_line)
{
	int		i;

	i = 0;
	if (ept_line == NULL)
	{
		init_list(ept_line);
		while(envp[i])
			insert_list(ept_line, ft_strjoin("declare -x ", envp[i++]));
	}
	else
	{
		if (get_argv_count(argv) == 1) // export만 출력하거나 fd로 보냄
			return (ept_line);
		else
		{

		}
	}
}

t_envp	*dup_envp(t_envp *head) //정렬하기 위한 리스트 만들기
{
	t_envp	*tmp;

	tmp = head;
	while (tmp)
	{

	}
}

t_envp	*sort_envp(t_envp *head) //strcmp 사용해서 문자열 정렬 ! 리스트 정렬 vs 내부 인자만 직접 바꾸기
{ //대문자 언더바 소문자 순이네요 .. 그냥 아스키순서 라네요 .. 씨 발 푸시스왑이잖아요
	t_envp	*tmp;

	tmp = head->next;
	while (tmp)
	{
		tmp = tmp->next;

	}
	return(tmp);
}

void	add_envp(t_envp *head, char *argv) // =로 나눠진다는 보장 없음, 스페이스 및 숫자 예외 처리
{
	t_envp	*new;
	char	**arr;
	int		i;

	if (!head || !argv)
		return ;
	i = ft_strchr_int(argv, '='); //없으면 key만
	arr = (char **)ft_safe_malloc(2 * sizeof(char *));
	arr[0] = ft_substr()
	if (!check_argv(argv))
	{
		print_error("minishell: export: '%s' : not a valid identifier\n", argv);
		return ;
	}
	new = init_envp(arr[0], arr[1]);
	insert_envp(head, new);
	free(arr);
}

int	ft_export(t_envp *head, char *argv) += =
{
	t_envp	*sorted;
	t_envp	*tmp;
	char	**arr;

	if (!argv)
	{
		sorted = dup_envp(head);
		sort_envp(sorted);
		tmp = sorted;
		tmp = head;
		while (tmp)
		{
			if (tmp->value == NULL)
				printf("declare -x %s\n", tmp->key);
			else
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		delete_envp_all(&sorted);
	}
	else
		add_envp(head, argv);
	}
	return (1);
}
