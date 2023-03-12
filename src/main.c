/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/12 16:22:13 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	int g_last_exit_code = 0;
	char			*str;
	t_info			*info;
	t_info			*tmp;
	t_envp			*envp_head;
	char			*cmd_path;
	t_info			*after_deleteq;

	envp_head = set_envp(envp); // 환경변수 세팅
	info = NULL;
	// 시그널 처리도 위에서 !
	while (1)
	{
		info = init_list();
		str = readline("Nakishell$: ");
		if (!str) //ctrl+D == NULL
		{
			printf("\033[1A\033[7Cexit");
			exit(0);
		}
		else
		{
			if (*str != '\0')
			{
				add_history(str);
				str_tokenize(info, str); // info 스페이스바 기준으로 잘린 cmd들이 들어있습니다.
				if (vaildate_quote_line(info)) // validate임 ㅅㅂ럼아
				{
					find_dollar(info, envp_head);
					clear_qoute_in_token(info); // 쿼터 제거
				}
				else
				{
					common_errno(info->cmd, 1, NULL); // 나중에 고치는걸로 완벽 X
					continue ;
				}
				tmp = info;
				// after_deleteq = info;
				// token -> builtin 검수 후 그대로 실행한다. 
				// builtin의 요소가 아니라면 cmd의 path를 가져와 execve로 넣거나,에러처리
				while (tmp != NULL)
				{
					// if (!builtin(tmp, envp_head)) // 추가적인 list 생성이 필요할수도?ㅠ
					// {
					// 	cmd_path = get_cmd(tmp->cmd, envp_head);
					// 	execve(cmd_path, 2차원배열, envp);
						
					// 	//path 실행
					// }
					builtin(tmp, envp_head);
					//path 실행 
					tmp = tmp->next;
				}
			}
		}
		list_delete(&info);
	}
	return (0);
}
