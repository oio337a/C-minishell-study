# C-minishell-study
나만의 작은 minishell 만들기 레포입니다.

## 파싱 방법 (토큰화)
1. 리다이렉션 (<, <<, >>, >) 뒤 : 무조건 파일네임 -> 뒤에 명령어 이어질 수도 있음
2. 파이프 뒤 : 무조건 명령어
3. 명령어 뒤 : 무조건 인자 (옵션도 인자 취급 !)
4. 쿼터 내부 ('', ""): 환경변수만 해석
5. 달러사인 ($) : 환경변수
> readline으로 받아온 줄 전체를 읽으며, 스페이스로 구분된 각각의 단어를 type과 함께 토큰 구조체에 저장
이후, 실행 가능한지 문법 체크하고 빌트인, execve로 나눠서 실행하면 되는데, 일단 여기까지 ~!

일단은 word -> 타입 판별 후 cmd, pipe, ... 등으로 분별시키는거져????ㅋㅋ
방식은 아직 안정했는데 아마도 글자 하나씩 보면서 리디랙션만 캐치하고 다른건 그냥 문자로 인식 해서 담아두는 식인 거같아요!? 허걱~

### 스플릿 방식
1. 보너스 X -> 파이프 기준으로 잘라도 됨
2. 동적할당 하실 때 ft_safe_malloc 쓰세여
3. 2차원 배열 프리하실 때는 ft_free 쓰세여
4. char형 2차원 배열 길이 세는 함수 ft_arrlen 만들었어요 ~!

### GNU readline 설치법 -> 이게 있어야 rl_replace_line 사용 가능
1. https://github.com/kube/42homebrew 에서 클러스터용 brew(패키지 관리자) 설치
2. 쉘에서 brew install readline으로 readline 설치
3. if 용량 부족 시, 슬랙에 cache link 검색 후 나오는 파일 저장 후 실행하여 용량 확보 후 재설치
4. brew info readline으로 설치 및 경로 확인

### 쿼터
> bash 기준
1. 쿼터 안의 같은 타입의쿼터는 해석하지 않음
2. 쿼터 안의 다른 타입의 쿼터는 문자로 해석
3. 쿼터 안의 스페이스 -> 구분자로 변경
4. 쿼터 개수 확인 -> 총 쿼터 개수 -- 홀짝판별 재설정
ex)
 가능한 케이스
 -> 1. "l"s "-a"l ->
	2. "ls" "-a"l
 불가능한 케이스
 -> 1. "ls -al"
	2. "ls -a"l

+) 짝이 맞지 않을 경우, err 처리

3/12
1. ft_cd OLDPWD 추가했습니다.
2. errno 출력 함수 변경
출력만 했었는데 전역변수 변경까지 합니다 return 시 이용하시면 될듯여
3. echo 환경변수 처리 -> 햇습니다 $? write->printf로 변경했습니다
---

1. errno 함수 타면 무조건 뒤에 함수 실행 안하고, newline을 띄우도록

2. pipe를 어떻게 하면 예쁘게 자를 수 있을가요?벅
이부분 명령어 뒤에 더 실행할거 있으면 dup2(fd[1], STDOUT)반복 하고
부모 프로세서에서 마지막에 닫아주면 병렬형 잘 될듯?????

ㅇㅕ ㄹㅓ부ㄴ~~~
최대한 기능 단위로 푸시하면 좋지만 안댔다면 git push 시 commit 메세지에 내역을 써주시면 감사하겟읍니다~~~
ex) delete quote norm 을 맞췄따 -> commit 메세지를 file : delete_quote norm check 이런 식으로요~~~~~~

### norm 처리 해야할 파일들
- heredoc.c
- token_access.c

### warning 뜨는 함수들
- src/err_print.c:90:38: warning: unused parameter 'res' [-Wunused-parameter]
	void    envp_errno(char *err_value, int res)
                                        ^
- src/err_print.c:96:48: warning: unused parameter 'res' [-Wunused-parameter]
	void    exit_errno(int arg_status, char *cmd, int res)
                                                  ^
- src/err_print.c:116:26: warning: unused parameter 'str' [-Wunused-parameter]
	void    badpath_errno(char *str, int res)

- src/syntax.c:37:16: warning: incompatible integer to pointer conversion passing 'int' to parameter of type 'char *' [-Wint-conversion]
                syntax_errno((head->type));
                             ^~~~~~~~~~~~
- src/../includes/minishell.h:136:26: note: passing argument to parameter 'cmd' here
void            syntax_errno(char *cmd);
                                   ^
- src/syntax.c:42:33: warning: '&&' within '||' [-Wlogical-op-parentheses]
                        || (head->type == HEREDOC_IN && ((head->next)->type != WORD) || head->next == NULL))
                            ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~
- src/syntax.c:42:33: note: place parentheses around the '&&' expression to silence this warning
                        || (head->type == HEREDOC_IN && ((head->next)->type != WORD) || head->next == NULL))
                                                     ^
                            (                                                       )
- src/syntax.c:44:17: warning: incompatible integer to pointer conversion passing 'int' to parameter of type 'char *' [-Wint-conversion]
                        syntax_errno((head->next)->type);
                                     ^~~~~~~~~~~~~~~~~~
- src/../includes/minishell.h:136:26: note: passing argument to parameter 'cmd' here
void            syntax_errno(char *cmd);
                                   ^
- src/syntax.c:47:58: warning: comparison between pointer and integer ('int' and 'void *') [-Wpointer-integer-compare]
                else if (head->type == REDIR_IN && ((head->next)->type == NULL || (head->next)->type != WORD))
                                                    ~~~~~~~~~~~~~~~~~~ ^  ~~~~
- src/syntax.c:49:17: warning: incompatible integer to pointer conversion passing 'int' to parameter of type 'char *' [-Wint-conversion]
                        syntax_errno((head->next)->type);
                                     ^~~~~~~~~~~~~~~~~~
- src/../includes/minishell.h:136:26: note: passing argument to parameter 'cmd' here
void            syntax_errno(char *cmd);


### heredoc, pipe
수행 전
STDOUT을 자식 파이프 출력부로 지정해놓는다
!! 마지막 부분이라면
자식 파이프 출력부를 STDOUT으로 되돌려 놓는다

부모 프로세스
STDIN를 부모 파이프 입력부로 지정해둔다


< a > out
자식 프로세스 STIN -> a의 fd로
자식 프로세스의 STDOUT -> out의 fd를 가리키도록 한다.
수행한 후에는 STDOUT, IN을 원래 부모의 값 상태로 되돌려야한다.
---
cat -e | ls -al


### test_case.zip

1. [미니쉘수동테스트](https://yeosong1.github.io/%EB%AF%B8%EB%8B%88%EC%89%98%EC%88%98%EB%8F%99%ED%85%8C%EC%8A%A4%ED%8A%B8)
2. [minishell-평가표-해석](https://velog.io/@hey-chocopie/minishell-%ED%8F%89%EA%B0%80%ED%91%9C-%ED%95%B4%EC%84%9D)
3. [minishell-tester # 1](https://github.com/cacharle/minishell_test)
4. [minishell-tester # 2](https://github.com/mcombeau/minitester-minishell-tester)
5. [minishell-tester # 3](https://github.com/LucasKuhn/minishell_tester)