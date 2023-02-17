#include "work_que.h"

void queInit(pQue_t pq, int capacity)
{
    bzero(pq,sizeof(Que_t));
    pq->queCapacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
    return ;
}

void queInsert(pQue_t pq,pNode_t pNew){
    if(pq->queHead==NULL) {
        pq->queHead=pNew;
        pq->queTail=pNew;
    }else{
        pq->queTail->pNext=pNew;
        pq->queTail=pNew;
    }
    pq->queSize++;
}

int queGet(pQue_t pq,pNode_t *pDel) {
    if(pq->queHead==NULL) {
        return -1;
    }
    *pDel=pq->queHead;
    pq->queHead=pq->queHead->pNext;
    if(pq->queHead==NULL){
        pq->queTail=NULL;
    }
    pq->queSize--;
    return 0;
}
