#include "process_poll.h"

int makeChild(process_data_t *p,int processNum)
{
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<processNum;i++) {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(pid==0) {
            close(fds[0]);
            childHandle(fds[1]);
        }
        close(fds[1]);
        p[i].pid=pid;//子进程的pid
        p[i].pipeFd=fds[0];//每个子进程的管道对端
        p[i].busy=0;
    }
    return 0;
}

int childHandle(int pipeFd) {
    int clientFd;
    int finishFlag;
    char childExitFlag;
    while(1){
        recvFd(pipeFd,&clientFd,&childExitFlag);//接收父进程发来的clientFd，没有任务时，子进程会睡觉
        if(childExitFlag) {
            exit(0);
        }
        transFile(clientFd);
        printf("File is send\n");
        close(clientFd);
        write(pipeFd,&finishFlag,1);//子进程通知父进程发送完成
    }
}

