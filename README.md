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