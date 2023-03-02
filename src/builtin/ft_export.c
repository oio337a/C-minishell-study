/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:29:43 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 21:50:28 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	# 예시
	export <변수명>=<값> : export JAVA_HOME=/user/lib/java-7-openjdk-amd64/
	-------------------------------
	# 짜증나는 예시
	export a                            #key값만 생성
	export b=                           #value에 아무 값 없음
	export c=hello          
	export c+=world                     #환경변수 뒤에 덧붙이기
	export d="oh      my          god"  #echo출력과 export출력 다름
	export e=elephant f=flower
	-------------------------------
	명령어가 export 하나면 print_export(g_envp)

	명령어가 export z 와 같은 식으로 인자가 하나면 환경변수에 저장되지 않음.

	명령어가 export key=value 일 때

	이미 존재하는 환경변수면 free 후 새로 dup
	새로운 환경변수면 원래 크기 + 2 짜리 **new 생성
	기존 환경변수 dup 하고
	새 환경변수, NULL 추가
	기존 환경변수 free 해주고 **new로 대체
	파이프 뒤에 있다면 자식프로세스의 export이기 때문에 환경변수 생성 X

	key가 숫자만 있으면 안 됨.

	value에는 숫자가 들어가도 됨.
	작은, 큰 따옴표 제거하고 환경변수 목록에 추가되어야 함.
*/
static int	get_argv_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

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
