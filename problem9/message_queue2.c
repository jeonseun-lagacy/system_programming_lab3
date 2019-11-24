#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 256

int main(){
    char *msg[BUFFER];
    mqd_t msg_queue;
    struct mq_attr q_attr;
    q_attr.mq_maxmsg = 10;
    q_attr.mq_msgsize = BUFFER;

    if((msg_queue = mq_open("/msg_queue", O_CREAT | O_RDWR, 0666, &q_attr)) == -1){
        perror("mq_open");
        exit(1);
    }
    
    while(1){
        if(mq_receive(msg_queue, msg, BUFFER, NULL)== -1){
            perror("mq_receive");
            exit(1);
        }
        printf("receive : %s\n", msg);
        if(!strcmp(msg, "end")){break;}
        memset(msg, 0, 256);
    }
    return 0;
}