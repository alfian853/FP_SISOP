/*#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
*/

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"



int recursively=0;

char source_path[256],destination_path[256];

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


//
//    FILE *fsrc=fopen(src,"rb");
//    FILE *fdst=fopen(dst,"wb");
//
////    if(fsrc==NULL || fdst==NULL){
////        if(fsrc==NULL)printf("source error");
////        if(fdst==NULL)printf("dst error");
////
////        printf("file access error!\n");
////        return;
////    }
//
//    long long fSize;
//    fseek(fsrc,0,SEEK_END);
//    fSize = ftell(fsrc);
//    rewind(fsrc);
//
//    char *buffer;
//    buffer =  (char*) malloc (sizeof(char)*fSize);
//
//    if(fread (buffer,1,fSize,fsrc)!=fSize){
////        printf(1,"reading error!\n");
//        return;
//    }
//    fwrite(buffer,1,fSize,fdst);
//    fclose(fsrc);
//    fclose(fdst);
//
//

}

//void _strcat(char *dst,char *src){
//    int j=strlen(dst);
//    for(int i=0;i<strlen(src);++i,j++){
//        dst[j]=src[i];
//    }
//    dst[j]='\0';
//return;
//}
//
//void traverse_file(char path[256]){
//    struct dirent* pdir;
//    int fd;
//
//
//
//   /* if(   ){
//        char new_path[256];
//        new_path[0]='\0';
//        _strcat(new_path,destination_path);
//        _strcat(new_path,"/");
//        _strcat(new_path,path);
//
//        copy_file(new_path,path);
//        return;
//    }*/
//
//    while ((pdir = readdir(dir) )){
//
//        if(pdir->d_type == DT_DIR && recursively){
//           // printf("tes %s\n",pdir->d_name);
//            if ( !strcmp(pdir->d_name, "..") )continue;
//            if(!strcmp(pdir->d_name, ".") ){
//                char new_path[256];
//                new_path[0]='\0';
//                _strcat(new_path,destination_path);
//                _strcat(new_path,"/");
//                _strcat(new_path,source_path);
//
//                mkdir(new_path);//,0777);
//                continue;
//            }
//            char new_path[256];
//            new_path[0]='\0';
//
//            //sprintf(new_path,"%s/%s/%s",destination_path,path,pdir->d_name);
//            _strcat(new_path,destination_path);
//            _strcat(new_path,"/");
//            _strcat(new_path,path);
//            _strcat(new_path,"/");
//            _strcat(new_path,pdir->d_name);
//
//            mkdir(new_path);
//            new_path[0]='\0';
//            _strcat(new_path,path);
//            _strcat(new_path,"/");
//            _strcat(new_path,pdir->d_name);
//
////            sprintf(new_path,"%s/%s",path,pdir->d_name);
//            traverse_file(new_path);
//        }
//        else{
//            char new_src[256];
//            new_src[0]='\0';
//            char new_dst[256];
//            new_dst[0]='\0';
//            _strcat(new_src,path);
//
//            _strcat(new_src,"/");
//            _strcat(new_src,pdir->d_name);
//
//            _strcat(new_dst,destination_path);
//            _strcat(new_dst,"/");
//            _strcat(new_dst,new_src);
//
//            //printf(1,"masuk3 %s %s\n",new_dst,new_src);
//            copy_file(new_dst,new_src);
//        }
//    }
//}
//


int main(int argc, char *argv[]){

    if(argc==1){
        printf(1,"cp: missing file operand\n\
        Try 'cp --help' for more information.\n");
        exit();
    }
    else if(argc==2){
        printf(1,"cp: missing destination file operand after '%s'\n\
        Try 'cp --help' for more information.\n",argv[1]);
        exit();
    }
/*    recursively=1;
    for(int i=1;i<argc;++i){
        if(!strcmp(argv[i],"-R")){
            recursively=1;
            break;
        }
        else if( strlen(source_path)==0 ){
            strcpy(source_path,argv[i]);
        }
        else{
            strcpy(destination_path,argv[i]);
        }
    }


    traverse_file(source_path);
*/
copy_file(argv[2],argv[1]);

}


