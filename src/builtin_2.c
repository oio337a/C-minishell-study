/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:39:39 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 15:17:15 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
	echo (-n)
	cd (절대/상대경로)
	pwd
	export
	unset
	env (인자 유무 O)
	exit
*/

/*
	전역 변수 설정 및 조회
*/
void env()
{
	
}

/*
	exit 만 입력 받았다면 exit 출력 후 EXIT_SUCCESS 넘기며 종료

	exit 뒤에 인자가 있다면 그 인자를 부모에게 상태값으로 전달 (ex exit 127), exit 출력하지 않고 종료

	exit 뒤의 숫자 인자가 2개 이상이라면 "exit\n" "bash: exit: too many arguments" 두 줄 출력 후 쉘 종료 X

	exit 뒤의 인자가 숫자가 아니라면 "bash: exit: 첫 번째 인자: numeric argument required" 출력 후 쉘 종료
*/
void exit(char *str)
{
	
}
