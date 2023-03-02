/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:39:39 by yongmipa          #+#    #+#             */
/*   Updated: 2023/03/02 15:14:07 by yongmipa         ###   ########seoul.kr  */
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
	------------------------------
	이거 테스트 해봐야함
	echo
	echo hello
	echo -n hello
	echo hello -n 
	echo -nnn hello
	echo -n-n hello
	echo -nnn hello -n 
	echo -nnn -n hello
	echo -
	echo - -
	echo --
	echo -n -n -nhjk hello
	echo -n -n -n -n -n hello
	echo "hello World"
	echo "hello            World"
	echo \\\"\'''\"
	------------------------------
	option 플래그가 0이면 \n 개행 출력.

	싱글쿼트일 때 환경변수 치환하지않고 그대로 출력.

	/Users/daelee/Desktop/42cursus/minishell $ echo '$PWD'
	> $PWD
	/Users/daelee/Desktop/42cursus/minishell $ echo "$PWD"
	> /Users/daelee/Desktop/42cursus/minishell
	echo $?

	g_exit_status 값 출력.
	echo -nnnnnn hello

	-> echo -n hello 와 동일
	echo hello ; ; 혹은 echo hello | |

	-> syntax error near unexpected token ;'` (258)
*/
void echo(char *str, int option)
{
	
}

/*
	cd, cd ~ 일때

	-> HOME 경로 찾아서 path에 저장 후 이동
	cd $변수 일때

	-> 변수 경로 찾아서 path에 저장 후 이동
	cd ~ 234 (cd ~ 후 인자가 들어왔을 때)

	-> 에러메세지 없이 ~로 이동
	cd $HSIDHSIHD (없는 환경변수일때)

	-> 에러메세지 없이 ~로 이동
*/
void cd()
{
	
}


/*
	envp 에서 pwd 찾고 출력
*/
void pwd(char **envp)
{
	
}

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
void export(char *str)
{
	
}

/*
	# 예시
	-------------------------------
	[root@wiki ~] str="hello world"
	[root@wiki ~] echo $str
	hello world
	[root@wiki ~] unset str
	[root@wiki ~] echo $str

	[root@zetawiki ~]
	-------------------------------
	인자로 들어온 환경변수가 유효한지 검사
	문자/숫자/_로 시작해야함
	이미 존재하는 환경변수인지 검사
	파이프 뒤에 있다면 자식프로세스의 unset이기 때문에 환경변수 삭제 X
*/
void unset(char *str)
{
	
}