/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/09 22:00:05 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_info			*info;
	t_info			*tmp;
	t_envp			*envp_head;
	char			*cmd_path;

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
				// add_history(str);
				// v_str = validate_readline(str); // valid한 라인으로 나와 -> pipe 기준 잘라 -> cmd_path에 넣어
				// pipe_parser(str, info);
				str_tokenize(info, str); // 스페이스바 기준으로 잘린 cmd들이 들어있습니다.
				if (vaildate_quote_line(info))
				{	
					find_dollar(info, envp_head);
					clear_qoute_in_token(info);
				}
				else
					common_errno(info->cmd, 1, NULL); // 나중에 고치는걸로 완벽 X
				tmp = info;
				// while (tmp != NULL)
				// {
				// 	printf("after tokenize! : %s\n", tmp->cmd);
				// 	tmp = tmp->next;
				// }
				/*작동*/
				//parse_command()
				//자르기 -> 쿼터 확인 -> 달러 처리 -> 쿼터 제거 -> 실행
				//실행부 내일 만들어여~~~~~~
				// token -> builtin 검수 후 그대로 실행한다. 
				// builtin의 요소가 아니라면 cmd의 path를 가져와 execve로 넣거나,에러처리
				while (tmp != NULL)
				{
					if (!builtin(tmp, envp_head)) // 추가적인 list 생성이 필요할수도?ㅠ
					{
						cmd_path = get_cmd(tmp->cmd, envp_head);
						execve()
						
						//path 실행
					}
					tmp = tmp->next;
				}
			}
		}
		list_delete(&info);
	}
	return (0);
}
