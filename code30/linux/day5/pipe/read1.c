#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDONLY);
    printf("read fdr=%d\n",fdr);
    char buf[128]={0};
    read(fdr,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    return 0;
}

