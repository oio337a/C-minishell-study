/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:32:43 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/13 14:32:44 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.c"

// int main(int ac, char **av, char **env)
// {
// 	char			*str;
// 	t_info			*info;
// 	t_info			*tmp;
// 	t_envp			*envp_head;

// 	envp_head = set_envp(envp);
// 	info = NULL;
// 	while (1)
// 	{
// 		info = init_list();
// 		str = readline("Nakishell$: ");
// 		if (!str) //ctrl+D == NULL
// 		{
// 			printf("\033[1A\033[7Cexit");
// 			exit(0);
// 		}
// 		else
// 		{
// 			if (*str != '\0')
// 			{
// 				// add_history(str);
// 				// v_str = validate_readline(str); // valid한 라인으로 나와 -> pipe 기준 잘라 -> cmd_path에 넣어
// 				// pipe_parser(str, info);
// 				str_tokenize(info, str);
// 				tmp = info;
// 				while (tmp != NULL)
// 				{
// 					printf("%s\n", tmp->cmd);
// 					tmp = tmp->next;
// 				}
// 			}
// 			free(str);
// 		}
// 	}
// 	list_delete(&info);
// 	delete_envp_all(&envp_head);
// 	return (0);
// }
