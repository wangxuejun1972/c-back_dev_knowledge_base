#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    FILE *fp;
    fp=fopen(argv[1],"ab+");
    ERROR_CHECK(fp,NULL,"fopen");
    char buf[128]={0};
    fread(buf,sizeof(char),5,fp);
    printf("buf=%s\n",buf);
    const char *p="how are you";
    fwrite(p,sizeof(char),strlen(p),fp);
    fclose(fp);
    return 0;
}

