#include <func.h>
int shmid;
char *p;
void sigFunc(int signum) {
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    printf("clean success,exit\n");
    exit(0);
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);//1号管道
    int fdw=open(argv[2],O_WRONLY);//2号管道
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");

    char buf[256]={0};
    fd_set rdset;
    int ret;
    signal(SIGINT,sigFunc);
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);//rdset是传入传出参数
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret)
            {
                printf("byebye\n");
                sigFunc(0);
                break;
            }
            write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            if(0==ret)
            {
                printf("byebye\n");
                sigFunc(0);
                break;
            }
            strcpy(p,buf);
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}

