#include <unistd.h>
#include <stdio.h>

int main(){

    char buf[256];
    int pipe_fd[2];
    int pid;

    //파이프 생성
    if(pipe(pipe_fd) == -1){
       perror("pipe");
       exit(1);
    }

    //자식 프로세스 생성
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    //자식 프로세스 수행
    if(pid == 0){
        //자식 프로세스의 읽기 파이프 닫기
        close(pipe_fd[0]);            
        //자식 프로세스에서 쓰기
        sprintf(buf, "hi parent process!\n");
        write(pipe_fd[1], buf, 256);
    }
    else if(pid > 0){
        //부모 프로세스의 쓰기 파이프 닫기
        close(pipe_fd[1]);
        read(pipe_fd[0], buf, 256);
        printf("%s\n", buf);
    }
    else{
        perror("fork");
    }
    return 0;
}