# C-minishell-study
나만의 작은 minishell 만들기 레포입니다.

ㅇㅕ러분~

### 스플릿 방식
1. 보너스 X -> 파이프 기준으로 잘라도 됨
2. 동적할당 하실 때 ft_safe_malloc 쓰세여
3. 2차원 배열 프리하실 때는 ft_free 쓰세여

## GNU readline 설치법 -> 이게 있어야 rl_replace_line 사용 가능
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