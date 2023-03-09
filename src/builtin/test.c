#include "../includes/minishell.c"

/*
unset 존재하는 일반 환경변수 -> 그 환경변수만 envp, export에서 제거

unset PATH -> envp 위치 없어져서 env 명령어 터짐, 
나머지 export는 존재
이후 PATH를 사용하는 모든 명령어들 사용(export도) 불가능함
*/