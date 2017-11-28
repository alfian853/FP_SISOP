#include "types.h"
#include "user.h"
#include "fcntl.h"


void copy_file(char* dst,char *src){

    int fdr,fdw;

    if ( (fdr=open(src,O_RDONLY)) < 0 ){
        printf(1,"returned read\n");
        return;
    }
    if ( (fdw=open(dst,O_CREATE|O_RDWR)) < 0 ){
        printf(1,"returned write\n");
        return;
    }
    int buff_len;
    char buffer[128];
    while( ( buff_len=read(fdr,buffer,sizeof(buffer)) )> 0  ){
        write(fdw,buffer,buff_len);
    }
    close(fdr);
    close(fdw);
}


int main(int argc,char *argv[]){

    if(argc==1){
        printf(1,"mv: missing file operand\n\
        Try 'mv --help' for more information.\n");
        exit();
    }
    else if(argc==2){
        printf(1,"mv: missing destination file operand after '%s'\n\
        Try 'mv --help' for more information.\n",argv[1]);
        exit();
    }
    copy_file(argv[2],argv[1]);
    unlink(argv[1]);
    exit();
}
