#include <func.h>
int sendFd(int pipeFd,int fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int *)CMSG_DATA(cmsg)=fd;//要把传递的描述符告诉内核
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=sendmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int pipeFd,int *fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    struct iovec iov[2];
    char buf1[10]="hello";
    iov[0].iov_base=buf1;
    iov[0].iov_len=5;
    char buf2[10]="world";
    iov[1].iov_base=buf2;
    iov[1].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int cmsgLen=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,cmsgLen);
    cmsg->cmsg_len=cmsgLen;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=cmsgLen;
    int ret;
    ret=recvmsg(pipeFd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}
int main(int argc,char* argv[])
{
    int fds[2];
    int ret;
    ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//全双工的管道
    ERROR_CHECK(ret,-1,"socketpair");
    if(!fork())
    {
        close(fds[1]);
        int fd;
        recvFd(fds[0],&fd);
        printf("I am child,%d\n",fd);
        char buf[128]={0};
        read(fd,buf,5);
        printf("I am child,buf=%s\n",buf);
    }else{
        close(fds[0]);
        int fd=open("file",O_RDWR);
        printf("I am parent,fd=%d\n",fd);
        sendFd(fds[1],fd);
        wait(NULL);
        char buf[128]={0};
        read(fd,buf,5);
        printf("I am parent,buf=%s\n",buf);
    }
    return 0;
}

