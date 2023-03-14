# C-minishell-study
나만의 작은 minishell 만들기 레포입니다.
ㅇㅕ러분~

ㄴㅏ키 : 1. libft/ft_strjoin.c에서 s1이나 s2가 NULL일 때 추가 처리 해줬어요
		2. qoute라고 오타난 것 전부 quote로 바꿨어요
		3. src/tokenize.c:17 is_whitespace2에서 line이 널이 아닌 경우에만 검사하는 조건 추가
		4. src/find_dollar.c:43 check_envp에서 token[j]가 널이 아닌 경우에만 검사하는 조건 추가

		이제 ""나 """" """""" 입력 시에는 세그폴트 안 나는 것 같은데 확인바랍니당 ..

		글고 첨엔 tokenize.c:86, :101 조건에도 *line이 널이 아닌 경우 조건으로 추가했었는데, 이건 일단 없어도 괜찮은 것 같네요 ?? 두 경우에서 원래 if문 안에 들어가는 내용이 다른 건지도 확인 부탁드려요 . . ! !

		마지막으로 ....... 쿼터만 있는 명령어를 입력하는 횟수가 많아질수록 exit하기 위해 ctrl+D를 눌러야 하는 횟수가 많아지는 문제가 있읍니다 ..
		다른 명령어들은 안 그러는데 혹시 쿼터 만들때마다 자식프로세스 만들거나 머 그런게 있나요 ? ㅠㅠ ctrl+D 누를 때마다 (!str) 조건문 들어가지는 건 확인되는데, 그러면 미니쉘 종료하려고 exit을 여러번 하게 된다는 건데 . . . 암튼 그렇습니다

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

### path_utils.c 내부 set_envp 함수 이름 set_path로 바꿨어요 !
환경변수 받아온 거 전부 리스트로 만들어두려 하는데 이름 겹칠 것 같아서 바꿨습니다.
지금 있는 파일들 중에선 set_path 쓰는 거 아직 없는 것 같아요 ! 헤더는 수정완료

### ㅍㅏ시ㅇ

3/9 할일
리스트 순회하면서 환경변수 변경 !

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
- main.c
- heredoc.c
- token_access.c
- tokenize.c -> yongmin_jakup.c

### warning 뜨는 함수들
- src/err_print.c:90:38: warning: unused parameter 'res' [-Wunused-parameter]
	void    envp_errno(char *err_value, int res)
                                        ^
- src/err_print.c:96:48: warning: unused parameter 'res' [-Wunused-parameter]
	void    exit_errno(int arg_status, char *cmd, int res)
                                                  ^
- src/err_print.c:116:26: warning: unused parameter 'str' [-Wunused-parameter]
	void    badpath_errno(char *str, int res)