#include "factory.h"

int exitFds[0];
void sigFunc(int sigNum){
    write(exitFds[1],&sigNum,1);
}

int main(int argc,char* argv[])
{
    if(argc!=5){
        printf("./thread_pool_server IP Port ThreadNum Capacity\n");
        return -1;
    }
    pipe(exitFds);
    signal(SIGUSR1,sigFunc);
    int epfd=epoll_create(1);
    struct epoll_event evs[2];
    while(fork()) {
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("child process exit success\n");
            exit(0);
        }
    }
    Factory_t threadInfo;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&threadInfo,threadNum,capacity);
    factoryStart(&threadInfo);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    epollAdd(epfd,socketFd);
    epollAdd(epfd,exitFds[0]);
    int clientFd;
    pQue_t pq=&threadInfo.que;
    pNode_t pNew;
    int readyFdCcount,i,j;
    while(1){
        readyFdCcount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyFdCcount;i++){

            if(evs[i].data.fd==exitFds[0]) {
                //long threadRet;
                for(j=0;j<threadInfo.threadNum;j++) {
                    pthread_cancel(threadInfo.pthid[j]);
                }
                for(j=0;j<threadInfo.threadNum;j++) {
                    pthread_join(threadInfo.pthid[j],NULL);
                    //printf("threadRet=%ld\n",threadRet);
                }
                destroyQue(pq);
                exit(0);
            }

            if(evs[i].data.fd==socketFd) {
                clientFd=accept(socketFd,NULL,NULL);
                pNew=(pNode_t)calloc(1,sizeof(Node_t));
                pNew->clientFd=clientFd;
                pthread_mutex_lock(&pq->mutex);
                queInsert(pq,pNew);
                pthread_mutex_unlock(&pq->mutex);
                pthread_cond_signal(&threadInfo.cond);
            }

        }
    }
    return 0;
}

