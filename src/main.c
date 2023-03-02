/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 14:50:24 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 프롬프트 열어서 하나의 완전한 커맨드를 readline으로 받아야됨

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("Nakishell $: ");
		if (!str)
			break ;
		if (*str != '\0')
		{
			add_history(str); // 이전 기록 왔다갔다할수잇슴
			//작동 코드
		}
		free(str);
	}
	return (0);
}
