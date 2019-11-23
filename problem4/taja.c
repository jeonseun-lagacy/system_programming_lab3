#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t start_time, finish_time, spent_time;
    int fd;
    int nread, cnt = 0, errcnt = 0;
    char ch, text[] ="The magic thing is that you can change it.";

    struct termios init_attr, new_attr;

    fd = open(ttyname(fileno(stdin)), O_RDWR);
    tcgetattr(fd, &init_attr);
    new_attr = init_attr;
    new_attr.c_lflag = ~ICANON;
    new_attr.c_lflag = ~ECHO;
    new_attr.c_cc[VMIN] = 1;
    new_attr.c_cc[VTIME] = 0;
    if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
        fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
    }

    start_time = time(NULL);
    printf("다음 문장을 그대로 입력하세요.\n%s\n", text);

    while (((nread=read(fd, &ch, 1)) > 0) && (ch != '\n')){        
        if (ch == text[cnt++]){
            write(fd, &ch, 1);
        }
        else {
            write(fd, "*", 1);
            errcnt++;
        }
        
    }

    finish_time = time(NULL);
    spent_time = finish_time - start_time;
    printf("\n소요시간 약%d초\n", spent_time);
    printf("오타율 %.2f%%\n", (float)errcnt/strlen(text) * 100.0);
    tcsetattr(fd, TCSANOW, &init_attr);
    close(fd);
}